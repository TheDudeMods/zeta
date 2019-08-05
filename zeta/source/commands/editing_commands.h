#pragma once

#include <cseries/cseries.h>
#include <commands/commands.h>
#include <tag_files/tag_definitions.h>

/* ---------- constants */

enum
{
	k_number_of_editing_commands = 3
};

/* ---------- globals */

extern s_command g_editing_commands[k_number_of_editing_commands];

/* ---------- classes */

class c_editing_command_context : public c_command_context
{
public:
	c_editing_command_context(
		char const *name,
		void *address,
		s_struct_definition *definition,
		c_command_context *parent = nullptr);

	void *get_address();
	s_struct_definition *get_definition();

protected:
	void *m_address;
	s_struct_definition *m_definition;
};

/* ---------- prototypes/EDITING_COMMANDS.CPP */

bool list_fields_execute(long arg_count, char const **arg_values);
bool set_field_execute(long arg_count, char const **arg_values);
bool edit_block_execute(long arg_count, char const **arg_values);
