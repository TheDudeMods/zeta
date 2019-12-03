#pragma once

#include <cseries/cseries.h>
#include <cache/cache_files.h>
#include <commands/commands.h>

/* ---------- constants */

enum
{
	k_number_of_tag_commands = 5
};

/* ---------- globals */

extern s_command g_tag_commands[k_number_of_tag_commands];

/* ---------- prototypes/TAG_COMMANDS.CPP */

c_command_context *create_tag_command_context(c_cache_file_reach *file, c_command_context *parent = nullptr);

bool list_tags_execute(long arg_count, char const **arg_values);
bool edit_tag_execute(long arg_count, char const **arg_values);
bool file_offset_execute(long arg_count, char const **arg_values);
bool list_local_resource_tags_execute(long arg_count, char const **arg_values);
bool list_resource_tag_metrics_execute(long arg_count, char const **arg_values);