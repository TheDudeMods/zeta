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

/* ---------- prototypes */

qword fields_print(char *address, s_struct_definition *definition);
qword field_get_size(e_field_type type, void const *definition);

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

	fields_print(address, definition);
	puts("");

	return true;
}

/* ---------- private code */

qword fields_print(char *address, s_struct_definition *definition)
{
	qword offset = 0;

	if (definition->parent)
		offset = fields_print(address, definition->parent);

	for (auto field = &definition->fields[0];
		field->type != _field_terminator;
		offset += field_get_size(field->type, field->definition), field++)
	{
		char tag_string[5];

		switch (field->type)
		{
		case _field_tag:
			printf("%s: tag = %s\n", field->name, tag_to_string(*(tag *)(address + offset), tag_string));
			break;

		case _field_short_string:
			printf("%s: short_string = %s\n", field->name, ((short_string *)(address + offset))->ascii);
			break;

		case _field_long_string:
			printf("%s: long_string = %s\n", field->name, ((long_string *)(address + offset))->ascii);
			break;

		case _field_string_id:
			printf("%s: string_id = 0x%08lX\n", field->name, *(string_id *)(address + offset));
			break;

		case _field_char_integer:
			printf("%s: char = %i\n", field->name, *(char *)(address + offset));
			break;

		case _field_short_integer:
			printf("%s: short = %i\n", field->name, *(short *)(address + offset));
			break;

		case _field_long_integer:
			printf("%s: long = %i\n", field->name, *(long *)(address + offset));
			break;

		case _field_int64_integer:
			printf("%s: long long = %ll\n", field->name, *(long long *)(address + offset));
			break;

		case _field_byte_integer:
			printf("%s: byte = %i\n", field->name, *(byte *)(address + offset));
			break;

		case _field_word_integer:
			printf("%s: word = %i\n", field->name, *(word *)(address + offset));
			break;

		case _field_dword_integer:
			printf("%s: dword = %i\n", field->name, *(dword *)(address + offset));
			break;

		case _field_qword_integer:
			printf("%s: qword = %llu\n", field->name, *(qword *)(address + offset));
			break;

		case _field_char_enum:
		{
			auto value = *(char *)(address + offset);
			auto enum_def = (s_enum_definition *)field->definition;
			for (auto i = 0; i < enum_def->option_count; i++)
			{
				if (value == enum_def->options[i].value)
				{
					printf("%s: char_enum = %s\n", field->name, enum_def->options[i].name);
					break;
				}
			}
			break;
		}

		case _field_short_enum:
		{
			auto value = *(short *)(address + offset);
			auto enum_def = (s_enum_definition *)field->definition;
			for (auto i = 0; i < enum_def->option_count; i++)
			{
				if (value == enum_def->options[i].value)
				{
					printf("%s: short_enum = %s\n", field->name, enum_def->options[i].name);
					break;
				}
			}
			break;
		}

		case _field_long_enum:
		{
			auto value = *(long *)(address + offset);
			auto enum_def = (s_enum_definition *)field->definition;
			for (auto i = 0; i < enum_def->option_count; i++)
			{
				if (value == enum_def->options[i].value)
				{
					printf("%s: long_enum = %s\n", field->name, enum_def->options[i].name);
					break;
				}
			}
			break;
		}

		case _field_byte_flags:
		{
			auto value = *(byte *)(address + offset);
			auto enum_def = (s_enum_definition *)field->definition;
			printf("%s: byte_flags = %s", field->name, value ? "" : "none");
			for (auto i = 0; i < enum_def->option_count; i++)
				if (TEST_FLAG(value, enum_def->options[i].value))
					printf("%s%s", enum_def->options[i].name, i < (enum_def->option_count - 1) ? ", " : " ");
			puts("");
			break;
		}

		case _field_word_flags:
		{
			auto value = *(word *)(address + offset);
			auto enum_def = (s_enum_definition *)field->definition;
			printf("%s: word_flags = %s", field->name, value ? "" : "none");
			for (auto i = 0; i < enum_def->option_count; i++)
				if (TEST_FLAG(value, enum_def->options[i].value))
					printf("%s%s", enum_def->options[i].name, i < (enum_def->option_count - 1) ? ", " : " ");
			puts("");
			break;
		}

		case _field_long_flags:
		{
			auto value = *(long *)(address + offset);
			auto enum_def = (s_enum_definition *)field->definition;
			printf("%s: long_flags = %s", field->name, value ? "" : "none");
			for (auto i = 0; i < enum_def->option_count; i++)
				if (TEST_FLAG(value, enum_def->options[i].value))
					printf("%s%s", enum_def->options[i].name, i < (enum_def->option_count - 1) ? ", " : " ");
			puts("");
			break;
		}

		case _field_point2d:
		{
			auto point = (point2d *)(address + offset);
			printf("%s: point2d = { x: %i, y: %i }\n", field->name, point->x, point->y);
			break;
		}

		case _field_rectangle2d:
		{
			auto rectangle = (rectangle2d *)(address + offset);
			printf("%s: rectangle2d = { top: %i, left: %i, bottom: %i, right: %i }\n",
				field->name, rectangle->top, rectangle->left, rectangle->bottom, rectangle->right);
			break;
		}

		case _field_rgb_color:
			printf("%s: rgb_color = 0x%08lX\n", field->name, *(rgb_color *)(address + offset));
			break;

		case _field_argb_color:
			printf("%s: argb_color = 0x%08lX\n", field->name, *(argb_color *)(address + offset));
			break;

		case _field_angle:
			printf("%s: angle = %f\n", field->name, *(angle *)(address + offset));
			break;

		case _field_real:
			printf("%s: real = %f\n", field->name, *(real *)(address + offset));
			break;

		case _field_real_fraction:
			printf("%s: real_fraction = %f\n", field->name, *(real_fraction *)(address + offset));
			break;

		case _field_real_point2d:
		{
			auto point = (real_point2d *)(address + offset);
			printf("%s: real_point2d = { x: %f, y: %f }\n", field->name, point->x, point->y);
			break;
		}

		case _field_real_point3d:
		{
			auto point = (real_point3d *)(address + offset);
			printf("%s: real_point3d = { x: %f, y: %f, z: %f }\n",
				field->name, point->x, point->y, point->z);
			break;
		}

		case _field_real_vector2d:
		{
			auto vector = (real_vector2d *)(address + offset);
			printf("%s: real_vector2d = { i: %f, j: %f }\n",
				field->name, vector->i, vector->j);
			break;
		}

		case _field_real_vector3d:
		{
			auto vector = (real_vector3d *)(address + offset);
			printf("%s: real_vector3d = { i: %f, j: %f, k: %f }\n",
				field->name, vector->i, vector->j, vector->k);
			break;
		}

		case _field_real_quaternion:
		{
			auto vector = (real_quaternion *)(address + offset);
			printf("%s: real_quaternion = { i: %f, j: %f, k: %f, w: %f }\n",
				field->name, vector->i, vector->j, vector->k, vector->w);
			break;
		}

		case _field_real_euler_angles2d:
		{
			auto euler_angles = (real_euler_angles2d *)(address + offset);
			printf("%s: real_euler_angles2d = { yaw: %f, pitch: %f }\n",
				field->name, euler_angles->yaw, euler_angles->pitch);
			break;
		}

		case _field_real_euler_angles3d:
		{
			auto euler_angles = (real_euler_angles3d *)(address + offset);
			printf("%s: real_euler_angles3d = { yaw: %f, pitch: %f, roll: %f }\n",
				field->name, euler_angles->yaw, euler_angles->pitch, euler_angles->roll);
			break;
		}

		case _field_real_plane2d:
		{
			auto plane = (real_plane2d *)(address + offset);
			printf("%s: real_plane2d = { i: %f, j: %f, d: %f }\n",
				field->name, plane->i, plane->j, plane->d);
			break;
		}

		case _field_real_plane3d:
		{
			auto plane = (real_plane3d *)(address + offset);
			printf("%s: real_plane3d = { i: %f, j: %f, k: %f, d: %f }\n",
				field->name, plane->i, plane->j, plane->k, plane->d);
			break;
		}

		case _field_real_matrix4x3:
			break;

		case _field_real_rgb_color:
		{
			auto rgb_color = (real_rgb_color *)(address + offset);
			printf("%s: real_rgb_color = { red: %f, green: %f, blue: %f }\n",
				field->name, rgb_color->red, rgb_color->green, rgb_color->blue);
			break;
		}

		case _field_real_argb_color:
		{
			auto color = (real_argb_color *)(address + offset);
			printf("%s: real_argb_color = { alpha: %f, red: %f, green: %f, blue: %f }\n",
				field->name, color->alpha, color->red, color->green, color->blue);
			break;
		}

		case _field_real_hsv_color:
		{
			auto color = (real_hsv_color *)(address + offset);
			printf("%s: real_hsv_color = { hue: %f, saturation: %f, value: %f }\n",
				field->name, color->hue, color->saturation, color->value);
			break;
		}

		case _field_real_ahsv_color:
		{
			auto color = (real_ahsv_color *)(address + offset);
			printf("%s: real_ahsv_color = { alpha: %f, hue: %f, saturation: %f, value: %f }\n",
				field->name, color->alpha, color->hue, color->saturation, color->value);
			break;
		}

		case _field_short_bounds:
		{
			auto bounds = (short_bounds *)(address + offset);
			printf("%s: short_bounds = { lower: %i, upper: %i }\n",
				field->name, bounds->lower, bounds->upper);
			break;
		}

		case _field_angle_bounds:
		{
			auto bounds = (angle_bounds *)(address + offset);
			printf("%s: angle_bounds = { lower: %f, upper: %f }\n",
				field->name, bounds->lower, bounds->upper);
			break;
		}

		case _field_real_bounds:
		{
			auto bounds = (real_bounds *)(address + offset);
			printf("%s: real_bounds = { lower: %f, upper: %f }\n",
				field->name, bounds->lower, bounds->upper);
			break;
		}

		case _field_fraction_bounds:
		{
			auto bounds = (real_fraction_bounds *)(address + offset);
			printf("%s: real_fraction_bounds = { lower: %f, upper: %f }\n",
				field->name, bounds->lower, bounds->upper);
			break;
		}

		case _field_tag_reference:
		{
			char tag_string[5];
			auto reference = (s_tag_reference *)(address + offset);
			printf("%s: tag_reference = { group_tag: %s, index: 0x%04lX }\n",
				field->name, tag_to_string(reference->group_tag, tag_string), reference->index & k_word_maximum);
			break;
		}

		case _field_block:
		{
			auto block = (s_tag_block *)(address + offset);
			printf("%s: tag_block = { count: %i, address: 0x%08lX }\n", field->name, block->count, block->address);
			break;
		}

		case _field_char_block_index:
			break;
		case _field_short_block_index:
			break;
		case _field_long_block_index:
			break;
		case _field_byte_block_flags:
			break;
		case _field_word_block_flags:
			break;
		case _field_long_block_flags:
			break;
		case _field_data:
			break;

		case _field_struct:
			break;
		}
	}

	return offset;
}

qword field_get_size(e_field_type type, void const *definition)
{
	switch (type)
	{
	case _field_tag:
		return sizeof(tag);
	case _field_short_string:
		return sizeof(short_string);
	case _field_long_string:
		return sizeof(long_string);
	case _field_string_id:
		return sizeof(string_id);
	case _field_char_integer:
		return sizeof(char);
	case _field_short_integer:
		return sizeof(short);
	case _field_long_integer:
		return sizeof(long);
	case _field_int64_integer:
		return sizeof(long long);
	case _field_byte_integer:
		return sizeof(byte);
	case _field_word_integer:
		return sizeof(word);
	case _field_dword_integer:
		return sizeof(dword);
	case _field_qword_integer:
		return sizeof(qword);
	case _field_char_enum:
		return sizeof(char);
	case _field_short_enum:
		return sizeof(short);
	case _field_long_enum:
		return sizeof(long);
	case _field_byte_flags:
		return sizeof(byte);
	case _field_word_flags:
		return sizeof(word);
	case _field_long_flags:
		return sizeof(long);
	case _field_point2d:
		return sizeof(point2d);
	case _field_rectangle2d:
		return sizeof(rectangle2d);
	case _field_rgb_color:
		return sizeof(rgb_color);
	case _field_argb_color:
		return sizeof(argb_color);
	case _field_angle:
		return sizeof(angle);
	case _field_real:
		return sizeof(real);
	case _field_real_fraction:
		return sizeof(real_fraction);
	case _field_real_point2d:
		return sizeof(real_point2d);
	case _field_real_point3d:
		return sizeof(real_point3d);
	case _field_real_vector2d:
		return sizeof(real_vector2d);
	case _field_real_vector3d:
		return sizeof(real_vector3d);
	case _field_real_quaternion:
		return sizeof(real_quaternion);
	case _field_real_euler_angles2d:
		return sizeof(real_euler_angles2d);
	case _field_real_euler_angles3d:
		return sizeof(real_euler_angles3d);
	case _field_real_plane2d:
		return sizeof(real_plane2d);
	case _field_real_plane3d:
		return sizeof(real_plane3d);
	case _field_real_matrix4x3:
		return sizeof(real_matrix4x3);
	case _field_real_rgb_color:
		return sizeof(real_rgb_color);
	case _field_real_argb_color:
		return sizeof(real_argb_color);
	case _field_real_hsv_color:
		return sizeof(real_hsv_color);
	case _field_real_ahsv_color:
		return sizeof(real_ahsv_color);
	case _field_short_bounds:
		return sizeof(short_bounds);
	case _field_angle_bounds:
		return sizeof(angle_bounds);
	case _field_real_bounds:
		return sizeof(real_bounds);
	case _field_fraction_bounds:
		return sizeof(real_fraction_bounds);
	case _field_tag_reference:
		return sizeof(s_tag_reference);
	case _field_block:
		return sizeof(s_tag_block);
	case _field_char_block_index:
		return sizeof(char);
	case _field_short_block_index:
		return sizeof(short);
	case _field_long_block_index:
		return sizeof(long);
	case _field_byte_block_flags:
		return sizeof(byte);
	case _field_word_block_flags:
		return sizeof(word);
	case _field_long_block_flags:
		return sizeof(long);
	case _field_data:
		return sizeof(s_tag_data);
	case _field_struct:
		return ((s_struct_definition *)definition)->size;
	case _field_array:
	{
		auto array = (s_array_definition *)definition;
		return array->count * field_get_size(array->type, array->definition);
	}
	case _field_padding:
	{
		auto padding = (s_padding_definition *)definition;
		return padding->length * field_get_size(padding->type, padding->definition);
	}
	}
	return 0;
}
