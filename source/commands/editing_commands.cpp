#include <commands/editing_commands.h>
#include <math/integer_math.h>
#include <math/real_math.h>
#include <tag_files/tag_groups.h>

/* ---------- constants */

enum
{
	k_number_of_editing_commands = 1
};

/* ---------- globals */

static s_command g_editing_commands[k_number_of_editing_commands] =
{
	{
		"list_fields",
		"list_fields [filter]",
		"Lists all fields in the current structure whose names match the specified filter (if any).",
		false,
		list_fields_execute
	}
};

/* ---------- code */

c_editing_command_context::c_editing_command_context(
	char const *name,
	void *address,
	s_struct_definition *definition,
	c_command_context *parent) :
	c_command_context(
		name,
		k_number_of_editing_commands,
		g_editing_commands,
		parent),
	m_address(address),
	m_definition(definition)
{
}

char *c_editing_command_context::get_address()
{
	return (char *)m_address;
}

s_struct_definition *c_editing_command_context::get_definition()
{
	return m_definition;
}

bool list_fields_execute(
	long arg_count,
	char const **arg_values)
{
	if (arg_count > 1)
		return false;

	auto editing_context = (c_editing_command_context *)g_command_context;
	
	auto address = editing_context->get_address();
	auto definition = editing_context->get_definition();

	struct_definition_print(definition, address);
	puts("");

	return true;
}
