#include <cache/cache_file_tag_resources.h>
#include <datatypes/data_array.h>
#include <files/file_synchronous_io.h>
#include <tag_files/tag_files.h>
#include <zlib/zlib.h>

/* ---------- code */

bool c_cache_file_reach::tag_resource_definition_try_and_get(
	long resource_index,
	void **out_address)
{
	if (out_address) *out_address = nullptr;

	if (resource_index == NONE)
		return false;

	auto resource_gestalt_index = c_tag_iterator<k_cache_file_resource_gestalt_group_tag>(this).next();
	if (resource_gestalt_index == NONE)
		return false;

	auto resource_gestalt = get_tag_definition<s_cache_file_resource_gestalt>(resource_gestalt_index);

	auto resource_absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(resource_index);
	auto resource_identifier = DATUM_INDEX_TO_IDENTIFIER(resource_index);

	if (resource_absolute_index < 0 || resource_absolute_index >= resource_gestalt->tag_resources.count)
		return false;

	s_cache_file_tag_resource *tag_resource = nullptr;
	if (!resource_gestalt->tag_resources.try_get_element(this, resource_absolute_index, &tag_resource))
		return false;

	if ((tag_resource->identifier != (ushort)NONE) && resource_identifier != tag_resource->identifier)
		return false;

	auto gestalt_definition_data = get_tags_section_pointer_from_page_offset<char>(
		resource_gestalt->definition_data.address);

	auto definition_data = &gestalt_definition_data[tag_resource->definition_data_offset];

	auto fixups = get_tags_section_pointer_from_page_offset<s_cache_file_tag_resource_fixup>(
		tag_resource->resource_fixups.address);

	auto definition_fixups = get_tags_section_pointer_from_page_offset<s_cache_file_tag_resource_fixup>(
		tag_resource->resource_definition_fixups.address);

	auto definition_offset = tag_resource->definition_address & 0x1FFFFFFF;

	for (auto i = 0; i < tag_resource->resource_fixups.count; i++)
	{
		auto address = fixups[i].address;
		auto type = (long)((address >> 28) & 0xF);
		auto offset = (long)(address & 0xFFFFFFF);

		if (type != 4)
		{
			offset -= (long)definition_offset;
			address = (ulong)((type << 28) | (((offset < 0) ? ((-offset & 0x7FFFFFF) | (1 << 27)) : (offset & 0x7FFFFFF))));
		}

		*(ulong *)&definition_data[fixups[i].block_offset] = address;
	}

	for (auto i = 0; i < tag_resource->resource_definition_fixups.count; i++)
	{
		auto block_offset = definition_fixups[i].block_offset;
		auto address = definition_fixups[i].address;
	}

	if (out_address)
		*out_address = &definition_data[definition_offset];

	return true;
}

bool c_cache_file_reach::tag_resource_try_and_get(
	long resource_index,
	long *out_length,
	void **out_address)
{
	if (out_length) *out_length = 0;
	if (out_address) *out_address = nullptr;

	if (resource_index == NONE)
		return false;

	auto resource_identifier = DATUM_INDEX_TO_IDENTIFIER(resource_index);
	auto resource_absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(resource_index);

	auto zone_index = c_tag_iterator<k_cache_file_resource_gestalt_group_tag>(this).next();
	if (zone_index == NONE)
		return false;

	auto definition = get_tag_definition<s_cache_file_resource_gestalt>(zone_index);

	auto play_index = c_tag_iterator<k_cache_file_resource_layout_table_group_tag>(this).next();
	if (play_index != NONE)
	{
		auto play_definition = get_tag_definition<s_cache_file_resource_layout_table>(play_index);
		csmemcpy(&definition->layout_table, play_definition, sizeof(s_cache_file_resource_layout_table));
	}

	s_cache_file_tag_resource *resource = nullptr;
	if (!definition->tag_resources.try_get_element(this, resource_absolute_index, &resource))
		return false;

	if (!resource->segment_index)
		return false;

	s_cache_file_resource_segment *segment = nullptr;
	if (!resource->segment_index.try_resolve(this, &definition->layout_table.segments, &segment))
		return false;

	if (!segment->primary_page || segment->primary_segment_offset == NONE)
		return false;

	auto segment_offset = (segment->secondary_segment_offset != NONE) ?
		segment->secondary_segment_offset :
		segment->primary_segment_offset;

	if (segment_offset == NONE)
		return false;

	s_cache_file_resource_page *primary_page = nullptr;
	if (segment->primary_page.try_resolve(this, &definition->layout_table.pages, &primary_page))
		if (primary_page->block_offset == NONE)
			primary_page = nullptr;

	s_cache_file_resource_page *secondary_page = nullptr;
	if (segment->secondary_page.try_resolve(this, &definition->layout_table.pages, &secondary_page))
		if (secondary_page->block_offset == NONE)
			secondary_page = nullptr;

	auto page = secondary_page ? secondary_page : primary_page;
	if (!page)
		return false;

	s_cache_file_resource_physical_location *location = nullptr;
	if (page->shared_cache_file && !page->shared_cache_file.try_resolve(this, &definition->layout_table.physical_locations, &location))
		return false;

	auto data = get_resource_page_data(location, page);
	if (!data)
		return false;

	if (out_length) *out_length = page->uncompressed_block_size;
	if (out_address) *out_address = data;

	return true;
}

void *c_cache_file_reach::get_resource_page_data(
	s_cache_file_resource_physical_location *location,
	s_cache_file_resource_page *page)
{
	static s_cache_file_header resource_cache_header;
	static char resource_cache_file_path[1024] = { 0 };

	csmemset(resource_cache_file_path, 0, 1024);

	if (location)
	{
		csmemcpy(resource_cache_file_path, m_filename, csstrrchr((char *)m_filename, '\\') - m_filename);

		auto file_path = csstrrchr(location->path.get_buffer(), '\\');
		csmemcpy(resource_cache_file_path + csstrlen(resource_cache_file_path), file_path, csstrlen(file_path));
	}
	else
	{
		csmemcpy(resource_cache_file_path, m_filename, csstrlen(m_filename));
	}

	s_cache_file_header *cache_header = nullptr;

	c_file_path path;
	path.set_file_path(_file_location_application_relative, resource_cache_file_path);

	s_file_accessor file;
	file_open(&path, FLAG(_file_open_read_bit), _file_error_mode_none, &file);

	if (location)
	{
		cache_header = &resource_cache_header;
		file_set_position(&file, 0, _file_error_mode_none);
		file_read(&file, sizeof(s_cache_file_header), _file_error_mode_none, cache_header);
	}
	else
	{
		cache_header = &m_header;
	}

	auto resource_buffer_offset =
		cache_header->section_offsets[_cache_file_section_resource] +
		cache_header->section_bounds[_cache_file_section_resource].offset;

	file_set_position(&file, resource_buffer_offset + page->block_offset, _file_error_mode_none);

	if (location)
		file_set_position_relative(&file, location->block_offset, _file_error_mode_none);

	auto uncompressed_data = new uchar[page->uncompressed_block_size];
	csmemset(uncompressed_data, 0, page->uncompressed_block_size);

	if (!page->compression_codec)
	{
		file_read(&file, page->uncompressed_block_size, _file_error_mode_none, uncompressed_data);
	}
	else
	{
		auto compressed_data = new uchar[page->compressed_block_size];
		csmemset(compressed_data, 0, page->compressed_block_size);

		file_read(&file, page->compressed_block_size, _file_error_mode_none, compressed_data);

		z_stream inflate_stream;
		inflate_stream.zalloc = Z_NULL;
		inflate_stream.zfree = Z_NULL;
		inflate_stream.opaque = Z_NULL;

		inflate_stream.total_in = inflate_stream.avail_in = page->compressed_block_size;
		inflate_stream.total_out = inflate_stream.avail_out = page->uncompressed_block_size;
		inflate_stream.next_in = compressed_data;
		inflate_stream.next_out = uncompressed_data;

		inflateInit2(&inflate_stream, -15);
		inflate(&inflate_stream, Z_FINISH);
		inflateEnd(&inflate_stream);

		delete[] compressed_data;
	}

	file_close(&file);

	return uncompressed_data;
}
