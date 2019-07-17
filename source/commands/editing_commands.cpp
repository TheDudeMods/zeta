#include <commands/editing_commands.h>
#include <math/integer_math.h>
#include <math/real_math.h>
#include <tag_files/tag_groups.h>

/* ---------- constants */

enum
{
	k_number_of_editing_commands = 2
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
	},
	{
		"set_field",
		"set_field <field_name> <field_value>",
		"Sets the value of field_name in the current structure to field_value.",
		false,
		set_field_execute
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

void *c_editing_command_context::get_address()
{
	return m_address;
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

	struct_print(definition, address, arg_count == 1 ? arg_values[0] : nullptr);
	puts("");

	return true;
}

bool set_field_execute(
	long arg_count,
	char const **arg_values)
{
	if (arg_count < 2)
		return false;

	auto field_name = arg_values[0];

	auto editing_context = (c_editing_command_context *)g_command_context;

	auto address = editing_context->get_address();
	auto definition = editing_context->get_definition();

	auto field = struct_get_field(definition, field_name, &address);

	if (!field)
	{
		printf("ERROR: no field named '%s' found in '%s' struct!\n", field_name, definition->name);
		return true;
	}

	if (!field_parse(field->type, field->name, field->definition, address, arg_count - 1, &arg_values[1]))
	{
		printf("ERROR: failed to parse '%s' field value!\n", field->name);
		return false;
	}

	field_print(field->type, field->name, field->definition, address);

	return true;
}
