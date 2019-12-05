#include <units/biped_definitions.h>

extern s_tag_block_definition unit_trick_block;
extern s_tag_group unit_group;

/* ---------- definitions */

TAG_ENUM(
	biped_definition_flags_enum,
	k_number_of_biped_definition_flags)
{
	{ "turns_without_animating", _biped_definition_turns_without_animating_bit },
	{ "has_physical_rigid_bodies_when_alive", _biped_definition_has_physical_rigid_bodies_when_alive_bit },
	{ "immune_to_falling_damage", _biped_definition_immune_to_falling_damage_bit },
	{ "has_animated_jetpack", _biped_definition_has_animated_jetpack_bit },
	{ "unused4", _biped_definition_unused4_bit },
	{ "unused5", _biped_definition_unused5_bit },
	{ "random_speed_increase", _biped_definition_random_speed_increase_bit },
	{ "unused7", _biped_definition_unused7_bit },
	{ "spawn_death_children_on_destroy", _biped_definition_spawn_death_children_on_destroy_bit },
	{ "stunned_by_emp_damage", _biped_definition_stunned_by_emp_damage_bit },
	{ "dead_physics_when_stunned", _biped_definition_dead_physics_when_stunned_bit },
	{ "always_ragdoll_when_dead", _biped_definition_always_ragdoll_when_dead_bit },
	{ "snaps_turns", _biped_definition_snaps_turns_bit },
	{ "sync_action_always_projects_on_ground", _biped_definition_sync_action_always_projects_on_ground_bit },
};

TAG_BLOCK(
	biped_camera_height_block,
	sizeof(s_biped_camera_height),
	NONE)
{
	{ _field_string_id, "weapon_class" },
	{ _field_real, "standing_height" },
	{ _field_real, "crouching_height" },
	{ _field_terminator }
};

TAG_BLOCK(
	biped_movement_gate_block,
	sizeof(s_biped_movement_gate),
	NONE)
{
	{ _field_real, "period" },
	{ _field_real, "z_offset" },
	{ _field_real, "constant_z_offset" },
	{ _field_real, "y_offset" },
	{ _field_real, "speed_threshold" },
	{ _field_data, "default_function" },
	{ _field_terminator }
};

TAG_PAD(
	_field_short_integer,
	biped_post_physics_control_node_pad,
	1);

TAG_GROUP(
	biped_group,
	k_biped_group_tag,
	sizeof(s_biped_definition) - sizeof(s_unit_definition),
	&unit_group)
{
	{ _field_real, "moving_turning_speed" },
	{ _field_long_flags, "flags", &biped_definition_flags_enum },
	{ _field_angle, "stationary_turning_speed" },
	{ _field_tag_reference, "death_program_selector" },
	{ _field_string_id, "ragdoll_region_name" },
	{ _field_string_id, "assassination_chud_text" },
	{ _field_real, "jump_velocity" },
	{ _field_block, "tricks", &unit_trick_block },
	{ _field_real, "maximum_soft_landing_time" },
	{ _field_real, "maximum_hard_landing_time" },
	{ _field_real, "minimum_soft_landing_velocity" },
	{ _field_real, "minimum_hard_landing_velocity" },
	{ _field_real, "maximum_hard_landing_velocity" },
	{ _field_real, "stun_duration" },
	{ _field_real, "standing_camera_height" },
	{ _field_real, "running_camera_height" },
	{ _field_real, "crouching_camera_height" },
	{ _field_real, "crouch_walking_camera_height" },
	{ _field_real, "crouch_transition_time" },
	{ _field_real, "crouch_unknown1" },
	{ _field_real, "crouch_unknown2" },
	{ _field_real, "crouch_unknown3" },
	{ _field_data, "camera_height_velocity_function" },
	{ _field_block, "camera_heights", &biped_camera_height_block },
	{ _field_angle, "camera_interpolation_start" },
	{ _field_angle, "camera_interpolation_end" },
	{ _field_real_vector3d, "camera_offset" },
	{ _field_real, "root_offset_camera_scale" },
	{ _field_real, "root_offset_camera_dampening" },
	{ _field_real, "autoaim_width" },
	{ _field_short_integer, "physics_control_node" }, // <--- TODO: block index
	{ _field_pad, "", &biped_post_physics_control_node_pad },
	{ _field_real, "runtime_cosine_stationary_turning_threshold" },
	{ _field_real, "runtime_crouch_transition_velocity" },
	{ _field_real, "runtime_camera_height_velocity" },
	{ _field_short_integer, "pelvis_node" }, // <--- TODO: block index
	{ _field_short_integer, "head_node" }, // <--- TODO: block index
	{ _field_block, "unknown1" },
	{ _field_tag_reference, "area_damage_effect" },
	{ _field_tag_reference, "health_station_recharge_effect" },
	{ _field_block, "movement_gates", &biped_movement_gate_block },
	{ _field_block, "movement_gates_crouching", &biped_movement_gate_block },
		// TODO: finish
	{ _field_terminator }
};
