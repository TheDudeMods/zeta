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
		c_cache_file_reach *file,
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

/* ---------- constants */

extern __declspec(selectany)
s_command const k_editing_commands[] =
{
	{
		"list_fields",
		"list_fields [filter]",
		"Lists all fields in the current structure whose names match the specified filter (if any).",
		true,
		list_fields_execute
	},
	{
		"set_field",
		"set_field <field_name> <field_value>",
		"Sets the value of field_name in the current structure to field_value.",
		true,
		set_field_execute
	},
	{
		"edit_block",
		"edit_block <field_name> [element_index]",
		"Opens the specified block/structure for editing.",
		true,
		edit_block_execute
	}
};

extern __declspec(selectany) s_command_set const k_editing_command_sets[] =
{
	{ NUMBEROF(k_editing_commands), k_editing_commands }
};
