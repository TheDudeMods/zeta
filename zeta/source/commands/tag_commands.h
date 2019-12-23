#pragma once

#include <cseries/cseries.h>
#include <cache/cache_files.h>
#include <commands/commands.h>

/* ---------- prototypes/TAG_COMMANDS.CPP */

c_command_context *create_tag_command_context(c_cache_file_reach *file, c_command_context *parent = nullptr);

bool list_tags_execute(long arg_count, char const **arg_values);
bool edit_tag_execute(long arg_count, char const **arg_values);
bool file_offset_execute(long arg_count, char const **arg_values);
bool list_local_resource_tags_execute(long arg_count, char const **arg_values);
bool list_resource_tag_metrics_execute(long arg_count, char const **arg_values);
bool save_cache_file_execute(long arg_count, char const **arg_values);

/* ---------- constants */

extern __declspec(selectany)
s_command const k_tag_commands[] =
{
	{
		"list_tags",
		"list_tags [group_tag] [filter]",
		"Lists all tags instances of the specified group.",
		true,
		list_tags_execute
	},
	{
		"edit_tag",
		"edit_tag <tag_handle>",
		"Opens the specified tag instance for editing.",
		false,
		edit_tag_execute
	},
	{
		"file_offset",
		"file_offset <page_address>",
		"Lists the file offset for a page address.",
		true,
		file_offset_execute
	},
	{
		"list_local_resource_tags",
		"list_local_resource_tags <group_tag>",
		"Lists all resource-owning tags instances of the specified group within the current cache file.",
		true,
		list_local_resource_tags_execute
	},
	{
		"list_resource_tag_metrics",
		"list_resource_tag_metrics <filename>",
		"Lists all tags that reference a resource within the given cache file.",
		true,
		list_resource_tag_metrics_execute
	},
	{
		"save_cache_file",
		"save_cache_file",
		"Saves the changes to the current cache file.",
		true,
		save_cache_file_execute
	}
};

extern __declspec(selectany)
s_command_set const k_tag_command_sets[] =
{
	{ NUMBEROF(k_tag_commands), k_tag_commands }
};
