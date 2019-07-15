#pragma once

#include <cseries/cseries.h>
#include <cache/cache_files.h>
#include <commands/commands.h>

/* ---------- classes */

class c_list_tags_command : public c_command
{
public:
	c_list_tags_command(c_cache_file *cache_file);

	bool execute(long arg_count, char const **args) override;

private:
	c_cache_file *m_cache_file;
};
