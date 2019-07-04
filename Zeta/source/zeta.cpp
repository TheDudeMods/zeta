/*
MAIN.CPP
TODO: Refactor all of this crap, it's test code
*/

#include <cache/cache_files_reach.h>
#include <tag_files/tag_groups_reach.h>

int main()
{
	struct
	{
		tag header_signature;
		long file_version;
		long file_length;
	} header_base;

	char *buffer = nullptr;

	auto stream = fopen("C:\\Halo\\Maps\\ReachPC\\m35.map", "rb+");
	fread(&header_base, sizeof(header_base), 1, stream);

	if (header_base.header_signature != 'head' || header_base.file_version != 12)
		return EXIT_FAILURE;

	buffer = new char[header_base.file_length];

	fseek(stream, 0, SEEK_SET);
	fread(buffer, header_base.file_length, 1, stream);
	fclose(stream);

	auto header = (s_cache_file_header_reach *)buffer;
	auto magic = (qword)header->memory_buffer_offset - header->virtual_base_address.value;
	auto tag_index = (s_cache_tag_index_header_reach *)(buffer + header->tag_index_address.value + magic);
	auto tag_groups = (s_tag_group_v2 *)(buffer + tag_index->groups_address.value + magic);
	auto tag_instances = (s_cache_tag_instance_reach *)(buffer + tag_index->tags_address.value + magic);
	auto important_groups = (s_tag_group_v2 *)(buffer + tag_index->important_groups_address.value + magic);
	auto tag_interop = buffer + tag_index->tag_interop_table_address.value + magic;
	auto tag_name_offsets = (long *)(buffer + header->tag_name_indices_offset);

	char tag_string[5] = { 0, 0, 0, 0, 0 };

	qword address_mask = header->virtual_base_address.value - (qword)header->memory_buffer_offset - 0x10000000;

	for (long i = 0; i < tag_index->tag_count; i++)
	{
		auto tag_instance = &tag_instances[i];

		if (tag_instance->group_index == NONE || tag_instance->identifier == NONE)
			continue;

		qword tag_offset = tag_instance->address.value == 0 ? 0 :
			((qword)tag_instance->address.value * 4) - address_mask;

		printf("[Index: 0x%lX, Offset: 0x%zX] %s.%s\n",
			i,
			tag_offset,
			buffer + header->tag_names_buffer_offset + tag_name_offsets[i],
			tag_to_string(tag_groups[tag_instance->group_index].tags[0], &tag_string[0]));
	}

	delete[] buffer;

	return EXIT_SUCCESS;
}
