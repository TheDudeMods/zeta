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

	struct_print(definition, address);
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

	auto field_definition = struct_get_field(definition, field_name, &address);

	if (!field_definition)
	{
		printf("ERROR: no field named '%s' found in '%s' struct!\n", field_name, definition->name);
		return true;
	}

	switch (field_definition->type)
	{
	case _field_tag:
	{
		auto field_address = (tag *)address;
		// TODO: parse here
		break;
	}

	case _field_short_string:
	{
		auto field_address = (short_string *)address;
		// TODO: parse here
		break;
	}

	case _field_long_string:
	{
		auto field_address = (long_string *)address;
		// TODO: parse here
		break;
	}

	case _field_string_id:
	{
		auto field_address = (string_id *)address;
		// TODO: parse here
		break;
	}

	case _field_char_integer:
	{
		auto field_address = (char *)address;
		// TODO: parse here
		break;
	}

	case _field_short_integer:
	{
		auto field_address = (short *)address;
		// TODO: parse here
		break;
	}

	case _field_long_integer:
	{
		auto field_address = (long *)address;
		// TODO: parse here
		break;
	}

	case _field_int64_integer:
	{
		auto field_address = (long long *)address;
		// TODO: parse here
		break;
	}

	case _field_byte_integer:
	{
		auto field_address = (byte *)address;
		// TODO: parse here
		break;
	}

	case _field_word_integer:
	{
		auto field_address = (word *)address;
		// TODO: parse here
		break;
	}

	case _field_dword_integer:
	{
		auto field_address = (dword *)address;
		// TODO: parse here
		break;
	}

	case _field_qword_integer:
	{
		auto field_address = (qword *)address;
		// TODO: parse here
		break;
	}

	case _field_char_enum:
	{
		auto field_address = (char *)address;
		// TODO: parse here
		break;
	}

	case _field_short_enum:
	{
		auto field_address = (short *)address;
		// TODO: parse here
		break;
	}

	case _field_long_enum:
	{
		auto field_address = (long *)address;
		// TODO: parse here
		break;
	}

	case _field_byte_flags:
	{
		auto field_address = (byte *)address;
		// TODO: parse here
		break;
	}

	case _field_word_flags:
	{
		auto field_address = (word *)address;
		// TODO: parse here
		break;
	}

	case _field_long_flags:
	{
		auto field_address = (long *)address;
		// TODO: parse here
		break;
	}

	case _field_point2d:
	{
		auto field_address = (point2d *)address;
		// TODO: parse here
		break;
	}

	case _field_rectangle2d:
	{
		auto field_address = (rectangle2d *)address;
		// TODO: parse here
		break;
	}

	case _field_rgb_color:
	{
		auto field_address = (rgb_color *)address;
		// TODO: parse here
		break;
	}

	case _field_argb_color:
	{
		auto field_address = (argb_color *)address;
		// TODO: parse here
		break;
	}

	case _field_angle:
	{
		auto field_address = (angle *)address;
		// TODO: parse here
		break;
	}

	case _field_real:
	{
		*(real *)address = strtof(arg_values[1], nullptr);
		break;
	}

	case _field_real_fraction:
	{
		auto field_address = (real_fraction *)address;
		// TODO: parse here
		break;
	}

	case _field_real_point2d:
	{
		auto field_address = (real_point2d *)address;
		// TODO: parse here
		break;
	}

	case _field_real_point3d:
	{
		auto field_address = (real_point3d *)address;
		// TODO: parse here
		break;
	}

	case _field_real_vector2d:
	{
		auto field_address = (real_vector2d *)address;
		// TODO: parse here
		break;
	}

	case _field_real_vector3d:
	{
		auto field_address = (real_vector3d *)address;
		// TODO: parse here
		break;
	}

	case _field_real_quaternion:
	{
		auto field_address = (real_quaternion *)address;
		// TODO: parse here
		break;
	}

	case _field_real_euler_angles2d:
	{
		auto field_address = (real_euler_angles2d *)address;
		// TODO: parse here
		break;
	}

	case _field_real_euler_angles3d:
	{
		auto field_address = (real_euler_angles3d *)address;
		// TODO: parse here
		break;
	}

	case _field_real_plane2d:
	{
		auto field_address = (real_plane2d *)address;
		// TODO: parse here
		break;
	}

	case _field_real_plane3d:
	{
		auto field_address = (real_plane3d *)address;
		// TODO: parse here
		break;
	}

	case _field_real_matrix4x3:
	{
		auto field_address = (real_matrix4x3 *)address;
		// TODO: parse here
		break;
	}

	case _field_real_rgb_color:
	{
		auto field_address = (real_rgb_color *)address;
		// TODO: parse here
		break;
	}

	case _field_real_argb_color:
	{
		auto field_address = (real_argb_color *)address;
		// TODO: parse here
		break;
	}

	case _field_real_hsv_color:
	{
		auto field_address = (real_hsv_color *)address;
		// TODO: parse here
		break;
	}

	case _field_real_ahsv_color:
	{
		auto field_address = (real_ahsv_color *)address;
		// TODO: parse here
		break;
	}

	case _field_short_bounds:
	{
		auto field_address = (short_bounds *)address;
		// TODO: parse here
		break;
	}

	case _field_angle_bounds:
	{
		auto field_address = (angle_bounds *)address;
		// TODO: parse here
		break;
	}

	case _field_real_bounds:
	{
		auto field_address = (real_bounds *)address;
		// TODO: parse here
		break;
	}

	case _field_fraction_bounds:
	{
		auto field_address = (real_fraction_bounds *)address;
		// TODO: parse here
		break;
	}

	}

	field_print(field_definition->type, field_definition->name, field_definition->definition, address);

	return true;
}
