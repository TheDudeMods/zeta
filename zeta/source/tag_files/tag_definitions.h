#pragma once

/* ---------- enumerators */

enum e_field_type
{
	_field_tag,
	_field_short_string,
	_field_long_string,
	_field_string_id,
	_field_char_integer,
	_field_short_integer,
	_field_long_integer,
	_field_int64_integer,
	_field_byte_integer,
	_field_word_integer,
	_field_dword_integer,
	_field_qword_integer,
	_field_char_enum,
	_field_short_enum,
	_field_long_enum,
	_field_byte_flags,
	_field_word_flags,
	_field_long_flags,
	_field_point2d,
	_field_rectangle2d,
	_field_rgb_color,
	_field_argb_color,
	_field_angle,
	_field_real,
	_field_real_fraction,
	_field_real_point2d,
	_field_real_point3d,
	_field_real_vector2d,
	_field_real_vector3d,
	_field_real_quaternion,
	_field_real_euler_angles2d,
	_field_real_euler_angles3d,
	_field_real_plane2d,
	_field_real_plane3d,
	_field_real_orientation3d,
	_field_real_matrix4x3,
	_field_short_bounds,
	_field_angle_bounds,
	_field_real_bounds,
	_field_fraction_bounds,
	_field_tag_reference,
	_field_block,
	_field_char_block_index,
	_field_short_block_index,
	_field_long_block_index,
	_field_byte_block_flags,
	_field_word_block_flags,
	_field_long_block_flags,
	_field_data,
	_field_struct,
	_field_array,
	_field_pointer,
	_field_padding,
	_field_skip,
	_field_explanation,
	_field_terminator,
	k_number_of_field_types
};

/* ---------- structures */

struct s_field_definition
{
	e_field_type type;
	char const *name;
	void const *definition;
};

struct s_enum_option
{
	char const *name;
	long value;
};

struct s_enum_definition
{
	char const *name;
	long option_count;
	s_enum_option *options;
};

struct s_struct_definition
{
	char const *name;
	long size;
	s_field_definition *fields;
};

struct s_array_definition
{
	e_field_type type;
	char const *name;
	long count;
	void const *definition;
};

/* ---------- prototypes/TAG_DEFINITIONS.CPP */

void byteswap(s_field_definition const *definition, void *address);
void byteswap(s_enum_definition const *definition, void *address);
void byteswap(s_struct_definition const *definition, void *address);
void byteswap(s_array_definition const *definition, void *address);