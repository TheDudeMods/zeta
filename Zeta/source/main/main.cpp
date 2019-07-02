/*
MAIN.CPP
*/

#include <cache/cache_files.h>

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

	auto header = (s_cache_file_header *)buffer;
	
	auto magic = (qword)header->memory_buffer_offset - header->virtual_base_address;

	for (long i = 0; i < k_number_of_cache_file_partitions; i++)
	{
		header->partitions[i].base_address += magic;
		header->partitions[i].size = header->partitions[i].size & 0xffffffff;
	}

	auto tag_index = header->tag_index =
		(s_cache_tag_index_header *)(buffer + (qword)header->tag_index + magic);

	tag_index->groups = (s_tag_group *)(buffer + (qword)tag_index->groups + magic);
	tag_index->tags = (s_cache_tag_instance *)(buffer + (qword)tag_index->tags + magic);
	tag_index->important_groups = (s_tag_group *)(buffer + (qword)tag_index->important_groups + magic);
	tag_index->tag_interop_table_address += magic;

	long *tag_name_offsets = (long *)(buffer + header->tag_name_indices_offset);

	char tag_string[5] = { 0, 0, 0, 0, 0 };

	qword address_mask = header->virtual_base_address - (qword)header->memory_buffer_offset - 0x10000000;

	for (long i = 0; i < tag_index->tag_count; i++)
	{
		auto tag_instance = &tag_index->tags[i];

		if (tag_instance->group_index == NONE || tag_instance->identifier == NONE)
			continue;

		qword tag_offset = tag_instance->page_address == 0 ? 0 :
			((qword)tag_instance->page_address * 4) - address_mask;

		printf("[Index: 0x%lX, Offset: 0x%zX] %s.%s\n",
			i,
			tag_offset,
			buffer + header->tag_names_buffer_offset + tag_name_offsets[i],
			tag_to_string(tag_index->groups[tag_instance->group_index].tags[0], &tag_string[0]));
	}

	delete[] buffer;

	return EXIT_SUCCESS;
}
