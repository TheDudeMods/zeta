#include <commands/tags/tag_commands.h>

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
