#pragma once

#include <cseries/cseries.h>
#include <cache/cache_files.h>
#include <commands/commands.h>

/* ---------- prototypes/TAG_COMMANDS.CPP */

c_command_context *create_tag_command_context(c_command_context *parent = nullptr);

bool list_tags(long arg_count, char const **arg_values);
