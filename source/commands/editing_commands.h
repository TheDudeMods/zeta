#pragma once

#include <cseries/cseries.h>
#include <commands/commands.h>
#include <tag_files/tag_definitions.h>

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
