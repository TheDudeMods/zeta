#pragma once

#include <cseries/cseries.h>

/* ---------- classes */

class c_command
{
public:
	virtual bool execute(long arg_count, char const **args) = 0;
};

class c_command_context
{
public:
	virtual c_command *get_command(char const *name) = 0;
};
