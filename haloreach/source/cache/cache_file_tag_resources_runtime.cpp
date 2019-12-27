#include <cache/cache_file_tag_resources.h>
#include <datatypes/data_array.h>
#include <files/file_synchronous_io.h>
#include <tag_files/tag_files.h>

#include <zlib/zlib.h>

#include <algorithm>

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

	s_cache_file_tag_resource *tag_resource = nullptr;
	if (!resource_gestalt->tag_resources.try_get_element(this, resource_absolute_index, &tag_resource))
		return false;

	if ((tag_resource->identifier != (ushort)NONE) && resource_identifier != tag_resource->identifier)
		return false;

	auto gestalt_definition_data = get_tags_section_pointer_from_page_offset<uchar>(
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

static int compare_page_offsets(const void *a, const void *b)
{
	return *(long *)a - *(long *)b;
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

	auto resource_gestalt_index = c_tag_iterator<k_cache_file_resource_gestalt_group_tag>(this).next();
	if (resource_gestalt_index == NONE)
		return false;

	auto resource_gestalt = get_tag_definition<s_cache_file_resource_gestalt>(resource_gestalt_index);

	auto layout_table_index = c_tag_iterator<k_cache_file_resource_layout_table_group_tag>(this).next();
	if (layout_table_index == NONE)
		return false;

	auto layout_table = get_tag_definition<s_cache_file_resource_layout_table>(layout_table_index);

	s_cache_file_tag_resource *resource = nullptr;
	if (!resource_gestalt->tag_resources.try_get_element(this, resource_absolute_index, &resource))
		return false;

	if (!resource->section)
		return false;

	s_cache_file_resource_section *section = nullptr;
	if (!resource->section.try_resolve(this, &layout_table->sections, &section))
		return false;

	if (!section->primary_page || section->primary_section_offset == NONE)
		return false;

	s_cache_file_resource_page *primary_page = nullptr;
	if (section->primary_page.try_resolve(this, &layout_table->pages, &primary_page))
		if (primary_page->block_offset == NONE)
			primary_page = nullptr;

	s_cache_file_resource_page *secondary_page = nullptr;
	if (section->secondary_page.try_resolve(this, &layout_table->pages, &secondary_page))
		if (secondary_page->block_offset == NONE)
			secondary_page = nullptr;

	auto page = secondary_page ? secondary_page : primary_page;
	if (!page)
		return false;

	s_cache_file_resource_shared_file *shared_file = nullptr;
	if (page->shared_file && !page->shared_file.try_resolve(this, &layout_table->shared_files, &shared_file))
		return false;

	auto page_data = (uchar *)get_resource_page_data(shared_file, page);

	if (!page_data)
		return false;

	auto page_section_offset = (section->secondary_section_offset != NONE) ?
		section->secondary_section_offset :
		section->primary_section_offset;

	if (page_section_offset == NONE)
		return false;

	auto page_section_count = page->section_count;
	auto page_section_offsets = new long[page_section_count];
	auto current_section_offset = (long *)page_section_offsets;

	for (auto i = 0; i < layout_table->sections.count; i++)
	{
		s_cache_file_resource_section *current_section = nullptr;

		if (!resource->section.try_resolve(this, &layout_table->sections, &current_section))
			continue;

		if (!current_section->primary_page || current_section->primary_section_offset == NONE)
			continue;

		s_cache_file_resource_page *current_primary_page = nullptr;

		if (current_section->primary_page.try_resolve(this, &layout_table->pages, &current_primary_page))
			if (primary_page->block_offset == NONE)
				primary_page = nullptr;

		s_cache_file_resource_page *current_secondary_page = nullptr;

		if (current_section->secondary_page.try_resolve(this, &layout_table->pages, &current_secondary_page))
			if (current_secondary_page->block_offset == NONE)
				current_secondary_page = nullptr;

		auto current_page = current_secondary_page ?
			current_secondary_page :
			current_primary_page;
		
		if (current_page != page || current_section_offset >= page_section_offsets + page_section_count)
			break;

		*current_section_offset = (current_section->secondary_section_offset != NONE) ?
			current_section->secondary_section_offset :
			current_section->primary_section_offset;

		current_section_offset++;
	}

	std::sort(page_section_offsets, page_section_offsets + page_section_count);

	auto page_segment_length = (long)NONE;

	for (auto i = 0; i < page_section_count; i++)
	{
		if (page_section_offsets[i] == page_section_offset)
		{
			while (page_section_offsets[i] == page_section_offset)
				i++;

			page_segment_length = (i >= page_section_count) ?
				(page->uncompressed_block_size - page_section_offset) :
				(page_section_offsets[i] - page_section_offset);

			break;
		}
	}

	if (page_segment_length <= 0)
		return false;

	auto segment_data = new uchar[page_segment_length];
	csmemcpy(segment_data, page_data + page_section_offset, page_segment_length);

	delete[] page_section_offsets;
	delete[] page_data;

	if (out_length) *out_length = page_segment_length;
	if (out_address) *out_address = segment_data;

	return true;
}

void *c_cache_file_reach::get_resource_page_data(
	s_cache_file_resource_shared_file *shared_file,
	s_cache_file_resource_page *page)
{
	static s_cache_file_header resource_cache_header;
	static char resource_cache_file_path[1024] = { 0 };

	csmemset(resource_cache_file_path, 0, 1024);

	if (shared_file)
	{
		auto last_separator = csstrrchr((char *)m_filename, '\\');

		if (!last_separator)
			last_separator = csstrrchr((char *)m_filename, '/');

		if (!last_separator) {
			csmemcpy(resource_cache_file_path, m_filename, csstrlen(m_filename));
		}
		else {
			csmemcpy(resource_cache_file_path, m_filename, last_separator - m_filename);
		}

		auto file_path = csstrrchr(shared_file->path.get_buffer(), '\\');

		if (!file_path)
			file_path = csstrrchr(shared_file->path.get_buffer(), '/');

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

	if (shared_file)
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

	if (shared_file)
		file_set_position_relative(&file, shared_file->block_offset, _file_error_mode_none);

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
