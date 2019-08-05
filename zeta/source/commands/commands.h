#pragma once

#include <cseries/cseries.h>
#include <datatypes/static_string.h>

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
	s_command *commands;
};

/* ---------- classes */

class c_command_context
{
protected:
	long_string m_name;
	long m_command_set_count;
	s_command_set *m_command_sets;
	c_command_context *m_parent;

public:
	c_command_context(char const *name, long command_set_count, s_command_set *command_sets, c_command_context *parent = nullptr);

	char *get_name(char *buffer) const;
	long get_command_count() const;
	s_command *get_command(char const *name);
	c_command_context *get_parent() const;
};

/* ---------- globals/COMMANDS.CPP */

extern c_command_context *g_command_context;

/* ---------- prototypes/COMMANDS.CPP */

void command_loop_execute();
