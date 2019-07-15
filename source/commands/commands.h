#pragma once

#include <cseries/cseries.h>

/* ---------- classes */

class c_command
{
protected:
	char const *m_name;
	char const *m_usage;
	char const *m_description;
	bool m_inherited;

public:
	c_command(char const *name, char const *usage, char const *description = "", bool inherited = true);

	virtual bool execute(long arg_count, char const **args) = 0;

	inline char const *get_name() const { return m_name; }
	inline char const *get_usage() const { return m_usage; }
	inline char const *get_description() const { return m_description; }
};

class c_command_context
{
private:
	char const *m_name;
	long m_command_count;
	c_command **m_commands;
	c_command_context *m_parent;

public:
	c_command_context(char const *name, c_command_context *parent = nullptr);
	~c_command_context();

	inline long get_command_count() const { return m_command_count; }
	inline c_command_context *get_parent() const { return m_parent; }

	void add_command(c_command *command);
	c_command *get_command(char const *name);
	char *get_name(char *buffer) const;
};
