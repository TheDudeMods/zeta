#include <cache/cache_file_tag_resources.h>
#include <zlib/zlib.h>

/* ---------- prototypes */

void *c_cache_file::get_resource_page_data(
	s_cache_file_resource_physical_location *location,
	s_cache_file_resource_page *page)
{
	static s_cache_file_header resource_cache_header;
	static char resource_cache_file_path[1024];

	memset(resource_cache_file_path, 0, 1024);

	if (location)
	{
		memcpy(resource_cache_file_path, g_cache_file_path, strrchr(g_cache_file_path, '\\') - g_cache_file_path);

		auto file_path = strrchr(location->path.ascii, '\\');
		memcpy(resource_cache_file_path + strlen(resource_cache_file_path), file_path, strlen(file_path));
	}
	else
	{
		memcpy(resource_cache_file_path, g_cache_file_path, strlen(g_cache_file_path));
	}

	s_cache_file_header *cache_header = nullptr;

	auto stream = fopen(resource_cache_file_path, "rb+");

	if (location)
	{
		cache_header = &resource_cache_header;
		fseek(stream, 0, SEEK_SET);
		fread(cache_header, sizeof(s_cache_file_header), 1, stream);
	}
	else
	{
		cache_header = &m_header;
	}

	fseek(stream, page->block_offset, SEEK_SET);

	auto uncompressed_data = new byte[page->uncompressed_block_size];
	memset(uncompressed_data, 0, page->uncompressed_block_size);

	if (!page->compression_codec)
	{
		fread(uncompressed_data, page->uncompressed_block_size, 1, stream);
	}
	else
	{
		auto compressed_data = new byte[page->compressed_block_size];
		memset(compressed_data, 0, page->compressed_block_size);

		fread(compressed_data, page->compressed_block_size, 1, stream);

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

	fclose(stream);

	return uncompressed_data;
}

/* ---------- code */

bool c_cache_file::tag_resource_try_and_get(
	long resource_index,
	long *out_length,
	void **out_address)
{
	if (out_length) *out_length = 0;
	if (out_address) *out_address = nullptr;

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

		if (!page_index.try_resolve(&definition->layout_table.pages, &page))
			return false;
	}

	auto location = page->shared_cache_file.resolve(&definition->layout_table.physical_locations);
	auto page_data = get_resource_page_data(location, page);

	if (!page_data)
		return false;

	auto length = page->compressed_block_size - segment_offset;
	auto data = new byte[length];
	memcpy(data, (char *)page_data + segment_offset, length);

	if (out_length) *out_length = length;
	if (out_address) *out_address = data;

	if (page_data) delete[] page_data;

	return true;
}
