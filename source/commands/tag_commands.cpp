#include <commands/editing_commands.h>
#include <commands/tag_commands.h>

/* ---------- constants */

enum
{
	k_number_of_tag_commands = 2
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
	},
	{
		"edit_tag",
		"edit_tag <tag_index>",
		"Opens the specified tag instance for editing.",
		false,
		edit_tag_execute
	}
};

/* ---------- code */

c_command_context *create_tag_command_context(
	c_command_context *parent)
{
	 return new c_command_context("tags", k_number_of_tag_commands, g_tag_commands, parent);
}

bool list_tags_execute(
	long arg_count,
	char const **arg_values)
{
	if (arg_count != 1)
		return false;

	// TODO: add verification to group tag parsing
	auto group_tag = string_to_tag(arg_values[0]);

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
				cache_file_header->memory_buffer_offset + g_cache_file->get_page_offset(instance->address),
				g_cache_file->get_tag_name(i),
				g_cache_file->get_string(group->name));
	}

	return true;
}

bool edit_tag_execute(
	long arg_count,
	char const **arg_values)
{
	if (arg_count != 1)
		return false;

	// TODO: verifiy index format
	auto index = strtoul(arg_values[0], nullptr, 0);

	auto instance = g_cache_file->get_tag_instance(index);

	if (!instance || !instance->address || instance->group_index == NONE)
	{
		printf("ERROR: tag instance 0x%04lX is null!", index);
		return true;
	}

	auto group = g_cache_file->get_tag_group(instance->group_index);

	if (!group)
	{
		printf("ERROR: failed to get tag group of tag instance 0x%04lX!", index);
		return true;
	}

	auto group_definition = tag_group_definition_get(group->tags[0]);

	if (!group_definition)
	{
		char tag_string[5];
		printf("ERROR: tag group definition not found for group tag '%s'!\n", tag_to_string(group->tags[0], tag_string));
		return true;
	}

	g_command_context = new c_editing_command_context(
		g_cache_file->get_tag_name(index),
		g_cache_file->get_tag_definition<void>(index),
		group_definition,
		g_command_context);

	return true;
}