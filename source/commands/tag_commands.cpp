#include <commands/tag_commands.h>

/* ---------- constants */

enum
{
	k_number_of_tag_commands = 1
};

/* ---------- globals */

static s_command g_tag_commands[k_number_of_tag_commands] =
{
	{
		"list_tags",
		"list_tags <group_tag>",
		"Lists all tags instances of the specified group.",
		true,
		list_tags_execute
	}
};

/* ---------- code */

c_command_context *create_tag_command_context(
	c_command_context *parent)
{
	 return new c_command_context("tags", k_number_of_tag_commands, g_tag_commands, parent);
}

void list_tags(tag group_tag)
{
	auto tags_header = g_cache_file->get_tags_header();

	for (auto i = 0; i < tags_header->tag_count; i++)
	{
		auto instance = g_cache_file->get_tag_instance(i);

		if (!instance || !instance->address || instance->group_index == NONE)
			continue;

		auto group = g_cache_file->get_tag_group(instance->group_index);

		if (group->is_in_group(group_tag))
			printf("[0x%04lX] %s.%s\n", i,
				g_cache_file->get_tag_name(i),
				g_cache_file->get_string(group->name));
	}
}

bool list_tags_execute(long arg_count, char const **arg_values)
{
	if (arg_count != 1)
		return false;

	// TODO: add verification to group tag parsing
	auto group_tag = string_to_tag(arg_values[0]);

	list_tags(group_tag);

	return true;
}
