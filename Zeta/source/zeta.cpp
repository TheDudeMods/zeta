/*
MAIN.CPP
TODO: Refactor all of this crap, it's test code
*/

#include <cseries/cseries.h>
#include <cache/cache_files_reach.h>
#include <tag_files/tag_groups_reach.h>

int main()
{
	long_string cache_file_path;
	FILE *cache_file_stream;
	char *cache_file_buffer;

	struct
	{
		tag header_signature;
		long file_version;
		long file_length;
	} cache_file_info;

	puts("Zeta v0.0.1");

	while (true)
	{
		puts("");
		puts("Enter the path to a Halo cache file:");
		printf("> ");

		gets_s(cache_file_path.ascii);

		if (strlen(cache_file_path.ascii) == 0)
			continue;

		if (cache_file_stream = fopen(cache_file_path.ascii, "rb+"))
		{
			fseek(cache_file_stream, 0, SEEK_SET);
			fread(&cache_file_info, sizeof(cache_file_info), 1, cache_file_stream);

			if (cache_file_info.header_signature != k_cache_header_signature &&
				_byteswap_ulong(cache_file_info.header_signature) != k_cache_header_signature)
			{
				puts("ERROR: Invalid cache file!");
				continue;
			}
			else
			{
				cache_file_buffer = new char[cache_file_info.file_length];

				fseek(cache_file_stream, 0, SEEK_SET);
				fread(cache_file_buffer, cache_file_info.file_length, 1, cache_file_stream);
				fclose(cache_file_stream);

				puts("");
				break;
			}
		}
	}

	auto header = (s_cache_file_header_reach *)cache_file_buffer;
	auto magic = (qword)header->memory_buffer_offset - header->virtual_base_address.value;
	auto tag_index = (s_cache_tag_index_header_reach *)(cache_file_buffer + header->tag_index_address.value + magic);
	auto tag_groups = (s_tag_group_v2 *)(cache_file_buffer + tag_index->groups_address.value + magic);
	auto tag_instances = (s_cache_tag_instance_reach *)(cache_file_buffer + tag_index->tags_address.value + magic);
	auto important_groups = (s_tag_group_v2 *)(cache_file_buffer + tag_index->important_groups_address.value + magic);
	auto tag_interop = cache_file_buffer + tag_index->tag_interop_table_address.value + magic;
	auto tag_name_offsets = (long *)(cache_file_buffer + header->tag_name_indices_offset);

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
			cache_file_buffer + header->tag_names_buffer_offset + tag_name_offsets[i],
			tag_to_string(tag_groups[tag_instance->group_index].tags[0], &tag_string[0]));
	}

	delete[] cache_file_buffer;

	return EXIT_SUCCESS;
}
