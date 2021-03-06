#pragma once

#include <cseries/cseries.h>
#include <datatypes/static_string.h>
#include <cache/cache_files.h>

/* ---------- structures */

struct s_command
{
	char const *name;
	char const *usage;
	char const *description;
	bool inherited;
	bool(*execute)(long arg_count, char const **arg_values);
};

struct s_command_set
{
	long command_count;
	s_command const *commands;
};

/* ---------- classes */

class c_command_context
{
protected:
	c_static_string<256> m_name;
	long m_command_set_count;
	s_command_set const *m_command_sets;
	c_command_context *m_parent;
	c_cache_file_reach *m_file;

public:
	c_command_context(char const *name, long command_set_count, s_command_set const *command_sets, c_cache_file_reach *file, c_command_context *parent = nullptr);

	virtual char *get_name(char *buffer) const;
	virtual long get_command_count() const;
	virtual s_command const *get_command(char const *name);
	virtual c_command_context *get_parent() const;
	virtual c_cache_file_reach *get_file() const;

	template <typename t_command_context>
	t_command_context *get_context()
	{
		t_command_context *result = nullptr;

		for (auto current = this;
			current != nullptr;
			current = current->m_parent)
		{
			result = dynamic_cast<t_command_context *>(current);
			if (result) break;
		}

		return result;
	}
};

/* ---------- globals/COMMANDS.CPP */

extern c_command_context *g_command_context;

/* ---------- prototypes/COMMANDS.CPP */

void command_loop_execute(c_cache_file_reach *file);
