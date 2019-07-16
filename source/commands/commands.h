#pragma once

#include <cseries/cseries.h>

/* ---------- structures */

struct s_command
{
	char const *name;
	char const *usage;
	char const *description;
	bool inherited;
	bool(*execute)(long arg_count, char const **arg_values);
};

/* ---------- classes */

class c_command_context
{
private:
	char const *m_name;
	long m_command_count;
	s_command *m_commands;
	c_command_context *m_parent;

public:
	c_command_context(char const *name, long command_count, s_command *commands, c_command_context *parent = nullptr);

	inline long get_command_count() const { return m_command_count; }
	inline c_command_context *get_parent() const { return m_parent; }

	s_command *get_command(char const *name);
	char *get_name(char *buffer) const;
};
