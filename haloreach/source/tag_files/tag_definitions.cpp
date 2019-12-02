#include <tag_files/tag_definitions.h>
#include <math/integer_math.h>
#include <bitmaps/bitmaps.h>
#include <cache/cache_files.h>
#include <cache/cache_file_tag_resources.h>
#include <camera/camera_track.h>
#include <datatypes/data_array.h>
#include <models/render_model_definitions.h>
#include <objects/object_definitions.h>
#include <objects/scenery.h>
#include <objects/crates.h>
#include <devices/devices.h>
#include <devices/device_controls.h>
#include <devices/device_machines.h>
#include <items/item_definitions.h>
#include <items/projectile_definitions.h>
#include <units/unit_definitions.h>
#include <rasterizer/rasterizer_shader_definitions.h>
#include <render_methods/render_method_definitions.h>

#include <cstdio>
#include <cstdlib>

/* ---------- globals */

extern s_tag_group_definition bitmap_group;
extern s_tag_group_definition cache_file_resource_gestalt_group;
extern s_tag_group_definition cache_file_resource_layout_table_group;
extern s_tag_group_definition camera_track_group;
extern s_tag_group_definition control_group;
extern s_tag_group_definition crate_group;
extern s_tag_group_definition device_group;
extern s_tag_group_definition item_group;
extern s_tag_group_definition machine_group;
extern s_tag_group_definition object_group;
extern s_tag_group_definition pixel_shader_group;
extern s_tag_group_definition projectile_group;
extern s_tag_group_definition render_method_group;
extern s_tag_group_definition render_method_shader_group;
extern s_tag_group_definition render_model_group;
extern s_tag_group_definition scenery_group;
extern s_tag_group_definition unit_group;
extern s_tag_group_definition vertex_shader_group;

static struct tag_definition
{
	tag group_tag;
	s_tag_group_definition *definition;
} g_tag_group_definitions[] =
{
	{ k_bitmap_group_tag, &bitmap_group },
	{ k_cache_file_resource_gestalt_group_tag, &cache_file_resource_gestalt_group },
	{ k_cache_file_resource_layout_table_group_tag, &cache_file_resource_layout_table_group },
	{ k_camera_track_group_tag, &camera_track_group },
	{ k_control_group_tag, &control_group },
	{ k_crate_group_tag, &crate_group },
	{ k_device_group_tag, &device_group },
	{ k_item_group_tag, &item_group },
	{ k_machine_group_tag, &machine_group },
	{ k_object_group_tag, &object_group },
	{ k_pixel_shader_group_tag, &pixel_shader_group },
	{ k_projectile_group_tag, &projectile_group },
	{ k_render_method_group_tag, &render_method_group },
	{ k_render_method_shader_group_tag, &render_method_shader_group },
	{ k_render_model_group_tag, &render_model_group },
	{ k_scenery_group_tag, &scenery_group },
	{ k_unit_group_tag, &unit_group },
	{ k_vertex_shader_group_tag, &vertex_shader_group },
	{ static_cast<tag>(NONE) }
};

/* ---------- code */

ulonglong field_get_size(
	e_field_type type,
	void *definition)
{
	switch (type)
	{
	case _field_tag:
		return sizeof(tag);
	case _field_short_string:
		return sizeof(c_static_string<32>);
	case _field_long_string:
		return sizeof(c_static_string<256>);
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
		return sizeof(uchar);
	case _field_word_integer:
		return sizeof(ushort);
	case _field_dword_integer:
		return sizeof(ulong);
	case _field_qword_integer:
		return sizeof(ulonglong);
	case _field_char_enum:
		return sizeof(char);
	case _field_short_enum:
		return sizeof(short);
	case _field_long_enum:
		return sizeof(long);
	case _field_byte_flags:
		return sizeof(uchar);
	case _field_word_flags:
		return sizeof(ushort);
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
		return sizeof(uchar);
	case _field_word_block_flags:
		return sizeof(ushort);
	case _field_long_block_flags:
		return sizeof(long);
	case _field_data:
		return sizeof(s_tag_data);
	case _field_datum_index:
		return sizeof(long);
	case _field_struct:
		return ((s_struct_definition *)definition)->size;
	case _field_array:
	{
		auto array = (s_array_definition *)definition;
		return array->length * field_get_size(array->type, array->definition);
	}
	case _field_padding:
	{
		auto padding = (s_padding_definition *)definition;
		return padding->length * field_get_size(padding->type, padding->definition);
	}
	}
	return 0;
}

void field_print_integer(
	e_field_type type,
	char const *name,
	void *address)
{
	char const *type_name = "integer";
	long long value = NONE;

	switch (type)
	{
	case _field_char_integer:
		type_name = "char_integer";
		value = *(char *)address;
		break;

	case _field_short_integer:
		type_name = "short_integer";
		value = *(short *)address;
		break;

	case _field_long_integer:
		type_name = "long_integer";
		value = *(long *)address;
		break;

	case _field_int64_integer:
		type_name = "int64_integer";
		value = *(long long *)address;
		break;

	case _field_byte_integer:
		type_name = "uchar_integer";
		value = *(uchar *)address;
		break;

	case _field_word_integer:
		type_name = "ushort_integer";
		value = *(ushort *)address;
		break;

	case _field_dword_integer:
		type_name = "ulong_integer";
		value = *(ulong *)address;
		break;

	case _field_qword_integer:
		type_name = "ulonglong_integer";
		value = *(ulonglong *)address;
		break;
	}

	printf("%s: %s = %lli\n", name, type_name, value);
}

void field_print_enum(
	e_field_type type,
	char const *name,
	void *definition,
	void *address)
{
	char const *type_name = "enum";
	long value = NONE;

	switch (type)
	{
	case _field_char_enum:
		type_name = "char_enum";
		value = *(char *)address;
		break;

	case _field_short_enum:
		type_name = "short_enum";
		value = *(short *)address;
		break;

	case _field_long_enum:
		type_name = "long_enum";
		value = *(long *)address;
		break;
	}

	auto enum_definition = (s_enum_definition *)definition;

	for (auto i = 0; i < enum_definition->option_count; i++)
	{
		if (value == enum_definition->options[i].value)
		{
			printf("%s: %s = %s\n", name, type_name, enum_definition->options[i].name);
			return;
		}
	}
}

void field_print_flags(
	e_field_type type,
	char const *name,
	void *definition,
	void *address)
{
	char const *type_name = "flags";
	long value = NONE;

	switch (type)
	{
	case _field_byte_flags:
		type_name = "uchar_flags";
		value = *(uchar *)address;
		break;

	case _field_word_flags:
		type_name = "ushort_flags";
		value = *(ushort *)address;
		break;

	case _field_long_flags:
		type_name = "long_flags";
		value = *(long *)address;
		break;
	}

	auto enum_definition = (s_enum_definition *)definition;

	printf("%s: %s = %s", name, type_name, value ? "" : "none");

	for (auto i = 0, count = 0; i < enum_definition->option_count; i++)
		if (TEST_BIT(value, enum_definition->options[i].value))
			printf("%s%s", count++ > 0 ? ", " : "", enum_definition->options[i].name);

	puts("");
}

void field_print(
	c_cache_file_reach *file,
	e_field_type type,
	char const *name,
	void *definition,
	void *address)
{
	char tag_string[5];
	c_static_string<256> temp_string;

	//
	// TODO: finish reimplementing
	//

	switch (type)
	{
	case _field_tag:
		printf("%s: tag = %s\n", name, tag_to_string(*(tag *)address, tag_string));
		break;

	case _field_short_string:
		printf("%s: c_static_string<32> = %s\n", name, ((c_static_string<32> *)address)->get_buffer());
		break;

	case _field_long_string:
		printf("%s: c_static_string<256> = %s\n", name, ((c_static_string<256> *)address)->get_buffer());
		break;

	case _field_string_id:
		printf("%s: string_id = %s\n", name, file->get_string(*(string_id *)address));
		break;

	case _field_char_integer:
	case _field_short_integer:
	case _field_long_integer:
	case _field_int64_integer:
	case _field_byte_integer:
	case _field_word_integer:
	case _field_dword_integer:
	case _field_qword_integer:
		field_print_integer(type, name, address);
		break;

	case _field_char_enum:
	case _field_short_enum:
	case _field_long_enum:
		field_print_enum(type, name, definition, address);
		break;

	case _field_byte_flags:
	case _field_word_flags:
	case _field_long_flags:
		field_print_flags(type, name, definition, address);
		break;

	case _field_point2d:
	{
		auto point = (point2d *)address;
		printf("%s: point2d = { x: %i, y: %i }\n", name, point->x, point->y);
		break;
	}

	case _field_rectangle2d:
	{
		auto rectangle = (rectangle2d *)address;
		printf("%s: rectangle2d = { top: %i, left: %i, bottom: %i, right: %i }\n",
			name, rectangle->top, rectangle->left, rectangle->bottom, rectangle->right);
		break;
	}

	case _field_rgb_color:
		printf("%s: rgb_color = 0x%08lX\n", name, *(rgb_color *)address);
		break;

	case _field_argb_color:
		printf("%s: argb_color = 0x%08lX\n", name, *(argb_color *)address);
		break;

	case _field_angle:
		printf("%s: angle = %f\n", name, *(angle *)address);
		break;

	case _field_real:
		printf("%s: real = %f\n", name, *(real *)address);
		break;

	case _field_real_fraction:
		printf("%s: real_fraction = %f\n", name, *(real_fraction *)address);
		break;

	case _field_real_point2d:
	{
		auto point = (real_point2d *)address;
		printf("%s: real_point2d = { x: %f, y: %f }\n", name, point->x, point->y);
		break;
	}

	case _field_real_point3d:
	{
		auto point = (real_point3d *)address;
		printf("%s: real_point3d = { x: %f, y: %f, z: %f }\n",
			name, point->x, point->y, point->z);
		break;
	}

	case _field_real_vector2d:
	{
		auto vector = (real_vector2d *)address;
		printf("%s: real_vector2d = { i: %f, j: %f }\n",
			name, vector->i, vector->j);
		break;
	}

	case _field_real_vector3d:
	{
		auto vector = (real_vector3d *)address;
		printf("%s: real_vector3d = { i: %f, j: %f, k: %f }\n",
			name, vector->i, vector->j, vector->k);
		break;
	}

	case _field_real_quaternion:
	{
		auto vector = (real_quaternion *)address;
		printf("%s: real_quaternion = { i: %f, j: %f, k: %f, w: %f }\n",
			name, vector->i, vector->j, vector->k, vector->w);
		break;
	}

	case _field_real_euler_angles2d:
	{
		auto euler_angles = (real_euler_angles2d *)address;
		printf("%s: real_euler_angles2d = { yaw: %f, pitch: %f }\n",
			name, euler_angles->yaw, euler_angles->pitch);
		break;
	}

	case _field_real_euler_angles3d:
	{
		auto euler_angles = (real_euler_angles3d *)address;
		printf("%s: real_euler_angles3d = { yaw: %f, pitch: %f, roll: %f }\n",
			name, euler_angles->yaw, euler_angles->pitch, euler_angles->roll);
		break;
	}

	case _field_real_plane2d:
	{
		auto plane = (real_plane2d *)address;
		printf("%s: real_plane2d = { i: %f, j: %f, d: %f }\n",
			name, plane->i, plane->j, plane->d);
		break;
	}

	case _field_real_plane3d:
	{
		auto plane = (real_plane3d *)address;
		printf("%s: real_plane3d = { i: %f, j: %f, k: %f, d: %f }\n",
			name, plane->i, plane->j, plane->k, plane->d);
		break;
	}

	case _field_real_matrix4x3:
		break;

	case _field_real_rgb_color:
	{
		auto rgb_color = (real_rgb_color *)address;
		printf("%s: real_rgb_color = { red: %f, green: %f, blue: %f }\n",
			name, rgb_color->red, rgb_color->green, rgb_color->blue);
		break;
	}

	case _field_real_argb_color:
	{
		auto color = (real_argb_color *)address;
		printf("%s: real_argb_color = { alpha: %f, red: %f, green: %f, blue: %f }\n",
			name, color->alpha, color->red, color->green, color->blue);
		break;
	}

	case _field_real_hsv_color:
	{
		auto color = (real_hsv_color *)address;
		printf("%s: real_hsv_color = { hue: %f, saturation: %f, value: %f }\n",
			name, color->hue, color->saturation, color->value);
		break;
	}

	case _field_real_ahsv_color:
	{
		auto color = (real_ahsv_color *)address;
		printf("%s: real_ahsv_color = { alpha: %f, hue: %f, saturation: %f, value: %f }\n",
			name, color->alpha, color->hue, color->saturation, color->value);
		break;
	}

	case _field_short_bounds:
	{
		auto bounds = (short_bounds *)address;
		printf("%s: short_bounds = { lower: %i, upper: %i }\n",
			name, bounds->lower, bounds->upper);
		break;
	}

	case _field_angle_bounds:
	{
		auto bounds = (angle_bounds *)address;
		printf("%s: angle_bounds = { lower: %f, upper: %f }\n",
			name, bounds->lower, bounds->upper);
		break;
	}

	case _field_real_bounds:
	{
		auto bounds = (real_bounds *)address;
		printf("%s: real_bounds = { lower: %f, upper: %f }\n",
			name, bounds->lower, bounds->upper);
		break;
	}

	case _field_fraction_bounds:
	{
		auto bounds = (real_fraction_bounds *)address;
		printf("%s: real_fraction_bounds = { lower: %f, upper: %f }\n",
			name, bounds->lower, bounds->upper);
		break;
	}

	case _field_tag_reference:
	{
		auto reference = (s_tag_reference *)address;
		auto instance = file->get_tag_instance(reference->index & k_uint16_max);

		if (reference->index == NONE || !instance || (instance && instance->group_index == NONE))
		{
			printf("%s: tag_reference = none\n", name);
		}
		else
		{
			auto tag_name = file->get_tag_name(reference->index & k_uint16_max);
			auto group = file->get_tag_group(instance->group_index);
			char group_string[5];

			printf("%s: tag_reference = (0x%04lX) %s.%s\n",
				name,
				reference->index & k_uint16_max,
				tag_name,
				tag_to_string(group->group_tags[0], group_string));
		}
		break;
	}

	case _field_block:
	{
		auto block = (s_tag_block *)address;
		printf("%s: tag_block = { count: %i, address: 0x%08lX }\n",
			name, block->count, block->address);
		break;
	}

	/* ---------- TODO: implement */
	case _field_char_block_index:
		field_print_integer(_field_char_integer, name, address);
		break;
	case _field_short_block_index:
		field_print_integer(_field_short_integer, name, address);
		break;
	case _field_long_block_index:
		field_print_integer(_field_long_integer, name, address);
		break;
	case _field_byte_block_flags:
		field_print_integer(_field_byte_integer, name, address);
		break;
	case _field_word_block_flags:
		field_print_integer(_field_word_integer, name, address);
		break;
	case _field_long_block_flags:
		field_print_integer(_field_long_integer, name, address);
		break;
	/* ---------- END TODO */

	case _field_data:
	{
		auto data = (s_tag_data *)address;
		printf("%s: tag_data = { size: %i, address: 0x%08lX }\n",
			name, data->size, data->address);
		break;
	}

	case _field_datum_index:
	{
		auto datum_index = *(long *)address;
		printf("%s: datum_index = { identifier: 0x%04X, index: %i }\n",
			name,
			DATUM_INDEX_TO_IDENTIFIER(datum_index),
			DATUM_INDEX_TO_ABSOLUTE_INDEX(datum_index));
		break;
	}

	case _field_struct:
	{
		auto struct_definition = (s_struct_definition *)definition;
		printf("%s: %s\n", name, struct_definition->name);
		break;
	}

	case _field_array:
	{
		auto array_definition = (s_array_definition *)definition;
		auto element_size = field_get_size(array_definition->type, array_definition->definition);

		for (auto i = 0; i < array_definition->length; i++)
		{
			printf("%s[%li]", name, i);
			field_print(file, array_definition->type, "", definition, (char *)address + (i * element_size));
		}
		break;
	}

	case _field_explanation:
	{
		printf("%s\n", name);
		break;
	}

	}
}

void field_next(
	s_field_definition **out_field,
	void **out_address)
{
	*out_address = ((char *)*out_address) + field_get_size((*out_field)->type, (*out_field)->definition);
	(*out_field)++;
}

bool field_parse_enum(
	e_field_type type,
	char const *name,
	void *definition,
	void *address,
	long arg_count,
	char const **arg_values)
{
	if (arg_count != 1)
		return false;

	auto option_name = arg_values[0];
	auto enum_definition = (s_enum_definition *)definition;

	for (auto i = 0; i < enum_definition->option_count; i++)
	{
		if (csstrcmp(option_name, enum_definition->options[i].name) != 0)
			continue;

		switch (type)
		{
		case _field_char_enum:
			*(long *)address = enum_definition->options[i].value;
			return true;

		case _field_short_enum:
			*(long *)address = enum_definition->options[i].value;
			return true;

		case _field_long_enum:
			*(long *)address = enum_definition->options[i].value;
			return true;
		}
	}

	return false;
}

bool field_parse_flags(
	e_field_type type,
	char const *name,
	void *definition,
	void *address,
	long arg_count,
	char const **arg_values)
{
	auto enum_definition = (s_enum_definition *)definition;

	if (arg_count < 1 || arg_count > enum_definition->option_count)
		return false;

	for (auto arg_index = 0;
		arg_index < arg_count;
		arg_index++)
	{
		auto found = false;

		for (auto option_index = 0;
			option_index < enum_definition->option_count;
			option_index++)
		{
			auto option_name = arg_values[arg_index];
			auto option = &enum_definition->options[option_index];
			auto set_bit = true;

			if (option_name[0] == '!')
			{
				option_name = &option_name[1];
				set_bit = false;
			}

			if (csstrcmp(option_name, option->name) == 0)
			{
				found = true;

				switch (type)
				{
				case _field_byte_flags:
					SET_FLAG(*(uchar *)address, option->value, set_bit);
					break;

				case _field_word_flags:
					SET_FLAG(*(ushort *)address, option->value, set_bit);
					break;

				case _field_long_flags:
					SET_FLAG(*(long *)address, option->value, set_bit);
					break;
				}

				break;
			}
		}

		if (!found)
		{
			auto option_name = arg_values[arg_index];

			if (csstrcmp(option_name, "none") == 0 ||
				csstrcmp(option_name, "0") == 0)
			{
				switch (type)
				{
				case _field_byte_flags:
					*(uchar *)address = 0;
					break;

				case _field_word_flags:
					*(ushort *)address = 0;
					break;

				case _field_long_flags:
					*(long *)address = 0;
					break;
				}
			}
			else
			{
				printf("ERROR: no option named '%s' found in '%s' enum!\n", arg_values[arg_index], enum_definition->name);
				return false;
			}
		}
	}

	return true;
}

bool field_parse_tag_reference(
	c_cache_file_reach *file,
	char const *name,
	s_tag_reference_definition *definition,
	void *address,
	long arg_count,
	char const **arg_values)
{
	if (arg_count != 1)
		return false;

	auto tags_header = file->get_tags_header();

	auto reference = (s_tag_reference *)address;

	c_static_string<256> reference_string(arg_values[0]);
	char tag_string[5];

	auto tag_name = reference_string.get_buffer();
	auto group_name = csstrrchr(reference_string.get_buffer(), '.');

	if (group_name)
	{
		*group_name = '\0';
		group_name++;

		auto tag_name_is_wildcard = csstrcmp(tag_name, "*") == 0;

		for (auto i = 0; i < tags_header->instances.count; i++)
		{
			auto current_instance = file->get_tag_instance(i);

			if (!current_instance || current_instance->group_index == NONE || !current_instance->address)
				continue;

			auto group = file->get_tag_group(current_instance->group_index);
			if (!group) continue;

			if (//csstrcmp(group_name, file->get_string(group->name)) == 0 ||
				csstrcmp(group_name, tag_to_string(group->group_tags[0], tag_string)) == 0)
			{
				if (tag_name_is_wildcard || csstrcmp(tag_name, file->get_tag_name(i)) == 0)
				{
					reference->group_tag = group->group_tags[0];
					reference->index = i;
					return true;
				}
			}
		}
	}
	else if (csstrstr(tag_name, "0x") == tag_name)
	{
		reference->index = strtol(tag_name, nullptr, 0);
		auto instance = file->get_tag_instance(reference->index);
		auto group = file->get_tag_group(instance->group_index);
		reference->group_tag = group->group_tags[0];
		return true;
	}
	else if (csstrcmp(tag_name, "*") == 0)
	{
		long last_index = NONE;

		for (auto i = 0; i < tags_header->instances.count; i++)
		{
			auto current_instance = file->get_tag_instance(i);

			if (current_instance && current_instance->group_index != NONE && current_instance->address)
				last_index = i;
		}

		if (last_index != NONE)
		{
			auto instance = file->get_tag_instance(last_index);
			auto group = file->get_tag_group(instance->group_index);
			reference->group_tag = group->group_tags[0];
			reference->index = last_index;
			return true;
		}
	}
	else if (csstrcmp(tag_name, "none") == 0)
	{
		reference->group_tag = NONE;
		reference->index = NONE;
		return true;
	}

	printf("ERROR: invalid tag specifier: %s\n", arg_values[0]);
	return false;
}

bool field_parse(
	c_cache_file_reach *file,
	e_field_type type,
	char const *name,
	void *definition,
	void *address,
	long arg_count,
	char const **arg_values)
{
	auto tags_header = file->get_tags_header();

	switch (type)
	{
	case _field_tag:
		if (arg_count != 1)
			return false;
		for (auto i = 0; i < tags_header->groups.count; i++)
		{
			auto group = file->get_tag_group(i);

			if (!group || group->group_tags[0] == NONE)
				continue;

			/*auto group_name = file->get_string(group->name);

			if (group_name && csstrcmp(group_name, arg_values[0]) == 0)
			{
				*(tag *)address = group->group_tags[0];
				return true;
			}*/
		}
		*(tag *)address = string_to_tag(arg_values[0]);
		return true;

	case _field_short_string:
		if (arg_count != 1 || csstrlen(arg_values[0]) > 32)
			return false;
		csmemcpy(((c_static_string<32> *)address)->get_buffer(), arg_values[0], csstrlen(arg_values[0]));
		return true;

	case _field_long_string:
		if (arg_count != 1 || csstrlen(arg_values[0]) > 32)
			return false;
		csmemcpy(((c_static_string<256> *)address)->get_buffer(), arg_values[0], csstrlen(arg_values[0]));
		return true;

	case _field_string_id:
		if (arg_count != 1)
			return false;
		*(string_id *)address = (string_id)strtoul(arg_values[0], nullptr, 0);
		return true;

	case _field_char_integer:
	case _field_char_block_index:
		if (arg_count != 1)
			return false;
		*(char *)address = (char)strtol(arg_values[0], nullptr, 0);
		return true;

	case _field_short_integer:
	case _field_short_block_index:
		if (arg_count != 1)
			return false;
		*(short *)address = (short)strtol(arg_values[0], nullptr, 0);
		return true;

	case _field_long_integer:
	case _field_long_block_index:
	case _field_datum_index:
		if (arg_count != 1)
			return false;
		*(long *)address = (long)strtol(arg_values[0], nullptr, 0);
		return true;

	case _field_int64_integer:
		if (arg_count != 1)
			return false;
		*(long long *)address = (long long)strtoll(arg_values[0], nullptr, 0);
		return true;

	case _field_byte_integer:
		if (arg_count != 1)
			return false;
		*(uchar *)address = (uchar)strtoul(arg_values[0], nullptr, 0);
		return true;

	case _field_word_integer:
		if (arg_count != 1)
			return false;
		*(ushort *)address = (ushort)strtoul(arg_values[0], nullptr, 0);
		return true;

	case _field_dword_integer:
		if (arg_count != 1)
			return false;
		*(ulong *)address = (ulong)strtoul(arg_values[0], nullptr, 0);
		return true;

	case _field_qword_integer:
		if (arg_count != 1)
			return false;
		*(ulonglong *)address = (ulonglong)strtoul(arg_values[0], nullptr, 0);
		return true;

	case _field_char_enum:
	case _field_short_enum:
	case _field_long_enum:
		return field_parse_enum(type, name, definition, address, arg_count, arg_values);

	case _field_byte_flags:
	case _field_word_flags:
	case _field_long_flags:
		return field_parse_flags(type, name, definition, address, arg_count, arg_values);
	
	case _field_point2d:
		return arg_count == 2
			&& field_parse(file, _field_short_integer, "x", nullptr, (char *)address + 0, 1, &arg_values[0])
			&& field_parse(file, _field_short_integer, "y", nullptr, (char *)address + 2, 1, &arg_values[1]);

	case _field_rectangle2d:
		return arg_count == 4
			&& field_parse(file, _field_short_integer, "top", nullptr, (char *)address + 0, 1, &arg_values[0])
			&& field_parse(file, _field_short_integer, "left", nullptr, (char *)address + 2, 1, &arg_values[1])
			&& field_parse(file, _field_short_integer, "bottom", nullptr, (char *)address + 4, 1, &arg_values[2])
			&& field_parse(file, _field_short_integer, "right", nullptr, (char *)address + 6, 1, &arg_values[3]);

	case _field_rgb_color:
		if (arg_count != 1)
			return false;
		*(long *)address = 0xFF000000 | (strtol(arg_values[0], nullptr, 0) & 0xFFFFFF);
		return true;

	case _field_argb_color:
		if (arg_count != 1)
			return false;
		*(long *)address = strtol(arg_values[0], nullptr, 0);
		return true;

	case _field_angle:
		if (arg_count != 1)
			return false;
		*(angle *)address = strtof(arg_values[0], nullptr);
		return true;

	case _field_real:
		if (arg_count != 1)
			return false;
		*(real *)address = strtof(arg_values[0], nullptr);
		return true;

	case _field_real_fraction:
		if (arg_count != 1)
			return false;
		*(real_fraction *)address = strtof(arg_values[0], nullptr);
		return true;

	case _field_real_point2d:
		return arg_count == 2
			&& field_parse(file, _field_real, "x", nullptr, (char *)address + 0, 1, &arg_values[0])
			&& field_parse(file, _field_real, "y", nullptr, (char *)address + 4, 1, &arg_values[1]);

	case _field_real_point3d:
		return arg_count == 3
			&& field_parse(file, _field_real, "x", nullptr, (char *)address + 0, 1, &arg_values[0])
			&& field_parse(file, _field_real, "y", nullptr, (char *)address + 4, 1, &arg_values[1])
			&& field_parse(file, _field_real, "z", nullptr, (char *)address + 8, 1, &arg_values[2]);

	case _field_real_vector2d:
		return arg_count == 2
			&& field_parse(file, _field_real, "i", nullptr, (char *)address + 0, 1, &arg_values[0])
			&& field_parse(file, _field_real, "j", nullptr, (char *)address + 4, 1, &arg_values[1]);

	case _field_real_vector3d:
		return arg_count == 3
			&& field_parse(file, _field_real, "i", nullptr, (char *)address + 0, 1, &arg_values[0])
			&& field_parse(file, _field_real, "j", nullptr, (char *)address + 4, 1, &arg_values[1])
			&& field_parse(file, _field_real, "k", nullptr, (char *)address + 8, 1, &arg_values[2]);

	case _field_real_quaternion:
		return arg_count == 4
			&& field_parse(file, _field_real, "i", nullptr, (char *)address + 0, 1, &arg_values[0])
			&& field_parse(file, _field_real, "j", nullptr, (char *)address + 4, 1, &arg_values[1])
			&& field_parse(file, _field_real, "k", nullptr, (char *)address + 8, 1, &arg_values[2])
			&& field_parse(file, _field_real, "w", nullptr, (char *)address + 12, 1, &arg_values[3]);

	case _field_real_euler_angles2d:
		return arg_count == 2
			&& field_parse(file, _field_angle, "yaw", nullptr, (char *)address + 0, 1, &arg_values[0])
			&& field_parse(file, _field_angle, "pitch", nullptr, (char *)address + 4, 1, &arg_values[1]);

	case _field_real_euler_angles3d:
		return arg_count == 3
			&& field_parse(file, _field_angle, "yaw", nullptr, (char *)address + 0, 1, &arg_values[0])
			&& field_parse(file, _field_angle, "pitch", nullptr, (char *)address + 4, 1, &arg_values[1])
			&& field_parse(file, _field_angle, "roll", nullptr, (char *)address + 8, 1, &arg_values[2]);

	case _field_real_plane2d:
		return arg_count == 3
			&& field_parse(file, _field_real, "i", nullptr, (char *)address + 0, 1, &arg_values[0])
			&& field_parse(file, _field_real, "j", nullptr, (char *)address + 4, 1, &arg_values[1])
			&& field_parse(file, _field_real, "d", nullptr, (char *)address + 8, 1, &arg_values[2]);

	case _field_real_plane3d:
		return arg_count == 4
			&& field_parse(file, _field_real, "i", nullptr, (char *)address + 0, 1, &arg_values[0])
			&& field_parse(file, _field_real, "j", nullptr, (char *)address + 4, 1, &arg_values[1])
			&& field_parse(file, _field_real, "k", nullptr, (char *)address + 8, 1, &arg_values[2])
			&& field_parse(file, _field_real, "d", nullptr, (char *)address + 12, 1, &arg_values[3]);

	case _field_real_matrix4x3:
		return arg_count == 13
			&& field_parse(file, _field_real, "scale", nullptr, (char *)address + 0, 1, &arg_values[0])
			&& field_parse(file, _field_real_vector3d, "forward", nullptr, (char *)address + 4, 3, &arg_values[1])
			&& field_parse(file, _field_real_vector3d, "left", nullptr, (char *)address + 16, 3, &arg_values[4])
			&& field_parse(file, _field_real_vector3d, "up", nullptr, (char *)address + 28, 3, &arg_values[7])
			&& field_parse(file, _field_real_point3d, "position", nullptr, (char *)address + 40, 3, &arg_values[10]);

	case _field_real_rgb_color:
		return arg_count == 3
			&& field_parse(file, _field_real, "red", nullptr, (char *)address + 0, 1, &arg_values[0])
			&& field_parse(file, _field_real, "green", nullptr, (char *)address + 4, 1, &arg_values[1])
			&& field_parse(file, _field_real, "blue", nullptr, (char *)address + 8, 1, &arg_values[2]);

	case _field_real_argb_color:
		return arg_count == 4
			&& field_parse(file, _field_real, "alpha", nullptr, (char *)address + 0, 1, &arg_values[0])
			&& field_parse(file, _field_real, "red", nullptr, (char *)address + 4, 1, &arg_values[0])
			&& field_parse(file, _field_real, "green", nullptr, (char *)address + 8, 1, &arg_values[1])
			&& field_parse(file, _field_real, "blue", nullptr, (char *)address + 12, 1, &arg_values[2]);

	case _field_real_hsv_color:
		return arg_count == 3
			&& field_parse(file, _field_real, "hue", nullptr, (char *)address + 0, 1, &arg_values[0])
			&& field_parse(file, _field_real, "saturation", nullptr, (char *)address + 4, 1, &arg_values[1])
			&& field_parse(file, _field_real, "value", nullptr, (char *)address + 8, 1, &arg_values[2]);

	case _field_real_ahsv_color:
		return arg_count == 4
			&& field_parse(file, _field_real, "alpha", nullptr, (char *)address + 0, 1, &arg_values[0])
			&& field_parse(file, _field_real, "hue", nullptr, (char *)address + 4, 1, &arg_values[0])
			&& field_parse(file, _field_real, "saturation", nullptr, (char *)address + 8, 1, &arg_values[1])
			&& field_parse(file, _field_real, "value", nullptr, (char *)address + 12, 1, &arg_values[2]);

	case _field_short_bounds:
		return arg_count == 2
			&& field_parse(file, _field_short_integer, "lower", nullptr, (char *)address + 0, 1, &arg_values[0])
			&& field_parse(file, _field_short_integer, "upper", nullptr, (char *)address + 2, 1, &arg_values[1]);

	case _field_angle_bounds:
		return arg_count == 2
			&& field_parse(file, _field_angle, "lower", nullptr, (char *)address + 0, 1, &arg_values[0])
			&& field_parse(file, _field_angle, "upper", nullptr, (char *)address + 4, 1, &arg_values[1]);

	case _field_real_bounds:
		return arg_count == 2
			&& field_parse(file, _field_real, "lower", nullptr, (char *)address + 0, 1, &arg_values[0])
			&& field_parse(file, _field_real, "upper", nullptr, (char *)address + 4, 1, &arg_values[1]);

	case _field_fraction_bounds:
		return arg_count == 2
			&& field_parse(file, _field_real_fraction, "lower", nullptr, (char *)address + 0, 1, &arg_values[0])
			&& field_parse(file, _field_real_fraction, "upper", nullptr, (char *)address + 4, 1, &arg_values[1]);

	case _field_tag_reference:
		return field_parse_tag_reference(file, name, (s_tag_reference_definition *)definition, address, arg_count, arg_values);
	}

	return false;
}

void *struct_print(
	c_cache_file_reach *file,
	s_struct_definition *definition,
	void *address,
	char const *filter)
{
	if (definition->parent)
		address = struct_print(file, definition->parent, address, filter);

	for (auto field = &definition->fields[0];
		field->type != _field_terminator;
		field_next(&field, &address))
	{
		if (filter && !csstrstr((char *)field->name, filter))
			continue;

		field_print(file, field->type, field->name, field->definition, address);
	}

	return address;
}

s_field_definition *struct_get_field(
	s_struct_definition *definition,
	char const *name,
	void **out_address)
{
	if (definition->parent)
	{
		auto parent_field = struct_get_field(definition->parent, name, out_address);
		if (parent_field) return parent_field;
	}

	for (auto field = &definition->fields[0];
		field->type != _field_terminator;
		field_next(&field, out_address))
	{
		if (csstrcmp(name, field->name) == 0)
			return field;
	}

	return nullptr;
}

s_tag_group_definition *tag_group_definition_get(
	tag group_tag)
{
	auto definition = g_tag_group_definitions;

	for (auto i = 0; definition->group_tag != NONE; definition++, i++)
		if (group_tag == g_tag_group_definitions[i].group_tag)
			return g_tag_group_definitions[i].definition;

	return nullptr;
}
