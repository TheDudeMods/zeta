#pragma once

#include <cseries/cseries.h>
#include <cache/cache_files.h>
#include <commands/commands.h>

/* ---------- prototypes/TAG_COMMANDS.CPP */

c_command_context *create_tag_command_context(c_command_context *parent = nullptr);

void list_tags(tag group_tag);
bool list_tags_execute(long arg_count, char const **arg_values);

void edit_tag(long index);
bool edit_tag_execute(long arg_count, char const **arg_values);
