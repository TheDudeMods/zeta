#include <commands/tags/tag_commands.h>

void list_tags(
	tag group_tag)
{
	auto tags_header = g_cache_file->get_tags_header();

	for (auto i = 0; i < tags_header->tag_count; i++)
	{
		auto instance = g_cache_file->get_tag_instance(i);

		if (!instance || !instance->address || instance->group_index == NONE)
			continue;

		auto group = g_cache_file->get_tag_group(instance->group_index);
		auto cache_file_header = g_cache_file->get_header();

		if (group->is_in_group(group_tag))
			printf("[Index: 0x%04lX, Offset: 0x%llX] %s.%s\n",
				i,
				cache_file_header->memory_buffer_offset + ((qword)instance->address * 4) - (cache_file_header->virtual_base_address - 0x10000000),
				g_cache_file->get_tag_name(i),
				g_cache_file->get_string(group->name));
	}
}

bool list_tags_execute(
	long arg_count,
	char const **arg_values)
{
	if (arg_count != 1)
		return false;

	// TODO: add verification to group tag parsing
	auto group_tag = string_to_tag(arg_values[0]);

	list_tags(group_tag);

	return true;
}
