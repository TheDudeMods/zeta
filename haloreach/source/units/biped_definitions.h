#pragma once

#include <cseries/cseries.h>
#include <math/real_math.h>
#include <tag_files/tag_groups.h>
#include <units/unit_definitions.h>

/* ---------- constants */

enum
{
    k_biped_group_tag = 'bipd'
};

/* ---------- types */

enum e_biped_definition_flags
{
	_biped_definition_turns_without_animating_bit,
	_biped_definition_has_physical_rigid_bodies_when_alive_bit,
	_biped_definition_immune_to_falling_damage_bit,
	_biped_definition_has_animated_jetpack_bit,
	_biped_definition_unused4_bit,
	_biped_definition_unused5_bit,
	_biped_definition_random_speed_increase_bit,
	_biped_definition_unused7_bit,
	_biped_definition_spawn_death_children_on_destroy_bit,
	_biped_definition_stunned_by_emp_damage_bit,
	_biped_definition_dead_physics_when_stunned_bit,
	_biped_definition_always_ragdoll_when_dead_bit,
	_biped_definition_snaps_turns_bit,
	_biped_definition_sync_action_always_projects_on_ground_bit,
	k_number_of_biped_definition_flags
};

struct s_biped_camera_height
{
	string_id weapon_class;
	real standing_height;
	real crouching_height;
};
static_assert(sizeof(s_biped_camera_height) == 0xC);

struct s_biped_movement_gate
{
	real period;
	real z_offset;
	real constant_z_offset;
	real y_offset;
	real speed_threshold;
	s_tag_data default_function;
};
static_assert(sizeof(s_biped_movement_gate) == 0x28);

struct s_biped_definition : s_unit_definition
{
	real moving_turning_speed;
	c_flags<e_biped_definition_flags, ulong> flags;
	angle stationary_turning_speed;
	s_tag_reference death_program_selector;
	string_id ragdoll_region_name;
	string_id assassination_chud_text;
	
	/* ------ jumping */

	real jump_velocity;
	c_tag_block<s_unit_trick_definition> tricks;
	real maximum_soft_landing_time;
	real maximum_hard_landing_time;
	real minimum_soft_landing_velocity;
	real minimum_hard_landing_velocity;
	real maximum_hard_landing_velocity;
	real stun_duration;

	/* ------ camera, collision, and autoaim */

	real standing_camera_height;
	real running_camera_height;
	real crouching_camera_height;
	real crouch_walking_camera_height;
	real crouch_transition_time;
	real crouch_unknown1;
	real crouch_unknown2;
	real crouch_unknown3;
	s_tag_data camera_height_velocity_function;
	c_tag_block<s_biped_camera_height> camera_heights;
	angle camera_interpolation_start;
	angle camera_interpolation_end;
	real_vector3d camera_offset;
	real root_offset_camera_scale;
	real root_offset_camera_dampening;
	real autoaim_width;
	short physics_control_node;
	short : 16;
	real runtime_cosine_stationary_turning_threshold;
	real runtime_crouch_transition_velocity;
	real runtime_camera_height_velocity;
	short pelvis_node;
	short head_node;
	s_tag_block unknown1;
	s_tag_reference area_damage_effect;
	s_tag_reference health_station_recharge_effect;
	c_tag_block<s_biped_movement_gate> movement_gates;
	c_tag_block<s_biped_movement_gate> movement_gates_crouching;

	// TODO: finish
};
