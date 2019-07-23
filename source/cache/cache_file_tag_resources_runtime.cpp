#include <cache/cache_file_tag_resources.h>
#include <zlib/zlib.h>

/* ---------- code */

bool c_cache_file::tag_resource_try_and_get(
	long resource_index,
	long *out_length,
	void **out_address)
{
	if (out_length)
		*out_length = 0;
	
	if (out_address)
		*out_address = nullptr;

	if (resource_index == NONE)
		return false;

	long zone_index = NONE;
	long tag_count = get_tags_header()->tag_count;

	for (auto i = 0; i < tag_count; i++)
	{
		auto instance = get_tag_instance(i);

		if (!instance || !instance->address || instance->group_index == NONE)
			continue;

		auto group = get_tag_group(instance->group_index);
		if (!group) continue;

		if (group->is_in_group(k_cache_file_resource_gestalt_group_tag))
		{
			zone_index = i;
			break;
		}
	}

	if (zone_index == NONE)
		return false;

	auto definition = get_tag_definition<s_cache_file_resource_gestalt>(zone_index);
	auto resource = &definition->tag_resources[resource_index & k_word_maximum];

	if (!resource->segment_index)
		return false;

	s_cache_file_resource_segment *segment = nullptr;
	if (!resource->segment_index.try_resolve(&definition->layout_table.segments, &segment))
		return false;

	if (!segment->primary_page || segment->primary_segment_offset == NONE)
		return false;

	auto page_index = (segment->secondary_page) ?
		segment->secondary_page :
		segment->primary_page;

	auto segment_offset = (segment->secondary_segment_offset != NONE) ?
		segment->secondary_segment_offset :
		segment->primary_segment_offset;

	if (!page_index || segment_offset == NONE)
		return false;

	s_cache_file_resource_page *page = nullptr;
	if (!page_index.try_resolve(&definition->layout_table.pages, &page))
		return false;

	if (page->block_offset == NONE)
	{
		page_index = segment->primary_page;
		segment_offset = segment->primary_segment_offset;
	}

	char resource_cache_file_path[1024];
	memset(resource_cache_file_path, 0, 1024);

	if (page->shared_cache_file)
	{
		memcpy(resource_cache_file_path, g_cache_file_path, strrchr(g_cache_file_path, '\\') - g_cache_file_path);

		s_cache_file_resource_physical_location *entry = nullptr;
		if (!page->shared_cache_file.try_resolve(&definition->layout_table.physical_locations, &entry))
			return false;

		auto file_path = strrchr(entry->path.ascii, '\\');
		memcpy(resource_cache_file_path + strlen(resource_cache_file_path), file_path, strlen(file_path));
	}
	else
	{
		memcpy(resource_cache_file_path, g_cache_file_path, strlen(g_cache_file_path));
	}

	auto uncompressed_length = page->uncompressed_block_size - segment_offset;
	auto uncompressed_data = new byte[uncompressed_length];

	if (out_length)
		*out_length = uncompressed_length;

	if (out_address)
		*out_address = uncompressed_data;

	FILE *stream = fopen(resource_cache_file_path, "rb+");
	fseek(stream, page->block_offset + m_header.interop.debug_section_size, SEEK_SET);

	if (!page->compression_codec)
	{
		fread(uncompressed_data, uncompressed_length, 1, stream);
	}
	else
	{
		auto compressed_data = new byte[page->compressed_block_size];
		fread(compressed_data, page->compressed_block_size, 1, stream);

		z_stream infstream;
		infstream.zalloc = Z_NULL;
		infstream.zfree = Z_NULL;
		infstream.opaque = Z_NULL;
		infstream.avail_in = page->compressed_block_size;
		infstream.next_in = compressed_data;
		infstream.avail_out = uncompressed_length;
		infstream.next_out = uncompressed_data;

		inflateInit(&infstream);
		inflate(&infstream, Z_NO_FLUSH);
		inflateEnd(&infstream);

		delete[] compressed_data;
	}

	fclose(stream);

	return true;
}
