#include <devices/device_machines.h>

extern s_tag_group device_group;

/* ---------- definitions */

TAG_ENUM(
	machine_type_enum,
	k_number_of_machine_types)
{
	{ "door", _machine_type_door },
	{ "platform", _machine_type_platform },
	{ "gear", _machine_type_gear },
};

TAG_ENUM(
	machine_flags_enum,
	k_number_of_machine_flags)
{
	{ "pathfinding_obstacle", _machine_pathfinding_obstacle_bit },
	{ "pathfinding_obstacle_unless_open", _machine_pathfinding_obstacle_unless_open_bit },
	{ "elevator", _machine_elevator_bit },
	{ "is_portal_blocker", _machine_is_portal_blocker_bit },
	{ "is_not_pathfinding_mobile", _machine_is_not_pathfinding_mobile_bit },
	{ "uses_default_occlusion_bounds", _machine_uses_default_occlusion_bounds_bit },
	{ "gears_repeat_motion_instead_of_loop", _machine_gears_repeat_motion_instead_of_loop_bit },
	{ "is_vehicle_bay", _machine_is_vehicle_bay_bit },
	{ "always_check_children_collision", _machine_always_check_children_collision_bit },
};

TAG_ENUM(
	machine_collision_response_enum,
	k_number_of_machine_collision_responses)
{
	{ "pause_until_crushed", _machine_collision_response_pause_until_crushed },
	{ "reverse_directions", _machine_collision_response_reverse_directions },
	{ "discs", _machine_collision_response_discs },
};

TAG_ENUM(
	machine_pathfinding_policy_enum,
	k_number_of_machine_pathfinding_policies)
{
	{ "discs", _machine_pathfinding_policy_discs },
	{ "sectors", _machine_pathfinding_policy_sectors },
	{ "cut_out", _machine_pathfinding_policy_cut_out },
	{ "none", _machine_pathfinding_policy_none },
};

TAG_PAD(
	_field_short_integer,
	machine_post_pathfinding_policy_padding,
	1);

TAG_GROUP(
	machine_group,
	k_machine_group_tag,
	sizeof(s_machine_definition) - sizeof(s_device_definition),
	&device_group)
{
	{ _field_short_enum, "machine_type", &machine_type_enum },
	{ _field_word_flags, "machine_flags", &machine_flags_enum },
	{ _field_real, "door_open_time" },
	{ _field_fraction_bounds, "door_occlusion_bounds" },
	{ _field_short_enum, "collision_response", &machine_collision_response_enum },
	{ _field_short_integer, "elevator_node" },
	{ _field_short_enum, "pathfinding_policy", &machine_pathfinding_policy_enum },
	{ _field_padding, "post_pathfinding_policy_padding", &machine_post_pathfinding_policy_padding },
	{ _field_string_id, "shield_name" },
	{ _field_string_id, "shield_function" },
	{ _field_terminator }
};
