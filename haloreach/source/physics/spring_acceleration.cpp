#include <physics/spring_acceleration.h>

/* ---------- definitions */

extern s_struct_definition tag_function_struct;

TAG_BLOCK(
	spring_linear_acceleration_block,
	k_maximum_number_of_spring_linear_accelerations,
	sizeof(s_spring_linear_acceleration))
{
	{ _field_real, "acceleration_range" },
	{ _field_real, "inverse_acceleration_range" },
	{ _field_real, "world_acceleration_scale" },
	{ _field_struct, "spring_damping", &tag_function_struct },
	{ _field_real, "velocity_domain" },
	{ _field_struct, "spring_acceleration", &tag_function_struct },
	{ _field_terminator }
};

TAG_PAD(
	_field_short_integer,
	spring_acceleration_post_z_axis_pad,
	1);

TAG_GROUP(
	spring_acceleration_group,
	k_spring_acceleration_group_tag,
	sizeof(s_spring_acceleration_definition))
{
	{ _field_block, "linear_accelerations", &spring_linear_acceleration_block },
	{ _field_short_block_index, "x_axis", &spring_linear_acceleration_block },
	{ _field_short_block_index, "y_axis", &spring_linear_acceleration_block },
	{ _field_short_block_index, "z_axis", &spring_linear_acceleration_block },
	{ _field_pad, "", &spring_acceleration_post_z_axis_pad },
	{ _field_terminator }
};
