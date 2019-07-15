#include <commands/tags/list_tags.h>

/* ---------- code */

c_list_tags_command::c_list_tags_command(c_cache_file *cache_file) :
	c_command(
		"list_tags",
		"list_tags <group_tag>",
		"Lists tag instances within the specified group.",
		true),
	m_cache_file(cache_file)
{
}

bool c_list_tags_command::execute(long arg_count, char const **args)
{
	if (arg_count != 1)
		return false;

	auto group_tag = string_to_tag(args[0]);
	auto tags_header = m_cache_file->get_tags_header();

	for (auto i = 0; i < tags_header->tag_count; i++)
	{
		auto instance = m_cache_file->get_tag_instance(i);

		if (!instance || !instance->address || instance->group_index == NONE)
			continue;

		auto group = m_cache_file->get_tag_group(instance->group_index);

		if (group->is_in_group(group_tag))
			printf("[0x%04lX] %s.%s\n", i,
				m_cache_file->get_tag_name(i),
				m_cache_file->get_string(group->name));
	}

	return true;
}
