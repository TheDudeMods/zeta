#pragma once

#include <cseries/cseries.h>
#include <cache/cache_files.h>
#include <commands/commands.h>

/* ---------- prototypes/TAG_COMMANDS.CPP */

void tag_commands_initialize(c_command_context *context, c_cache_file *cache_file);
void tag_commands_dispose();
