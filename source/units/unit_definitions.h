#pragma once

#include <ai/ai.h>
#include <cseries/cseries.h>
#include <game/campaign_metagame.h>
#include <game/game_allegiance.h>
#include <math/real_math.h>
#include <objects/object_definitions.h>

/* ---------- constants */

enum
{
    k_unit_group_tag = 'unit',
    k_maximum_number_of_unit_screen_effect_references = 4,
    k_maximum_number_of_unit_camera_track_references = 4,
    k_maximum_number_of_unit_camera_acceleration_displacements = 1,
    k_maximum_number_of_unit_camera_gamepad_stick_functions = 1,
    k_maximum_number_of_unit_camera_gamepad_stick_overrides = 1,
};

/* ---------- enumerators */

enum e_unit_definition_flags
{
    _unit_definition_circular_aiming_bit,
    _unit_definition_destroyed_after_dying_bit,
    _unit_definition_half_speed_interpolation_bit,
    _unit_definition_fires_from_camera_bit,
    _unit_definition_entrance_inside_bounding_sphere_bit,
    _unit_definition_doesnt_show_readied_weapon_bit,
    _unit_definition_causes_passenger_dialogue_bit,
    _unit_definition_resists_pings_bit,
    _unit_definition_melee_attack_is_fatal_bit,
    _unit_definition_dont_reface_during_pings_bit,
    _unit_definition_has_no_aiming_bit,
    _unit_definition_simple_creature_bit,
    _unit_definition_impact_melee_attaches_to_unit_bit,
    _unit_definition_impact_melee_dies_on_shield_bit,
    _unit_definition_cannot_open_doors_automatically_bit,
    _unit_definition_melee_attackers_cannot_attach_bit,
    _unit_definition_not_instantly_killed_by_melee_bit,
    _unit_definition_shield_sapping_bit,
    _unit_definition_runs_around_flaming_bit,
    _unit_definition_inconsequential_bit,
    _unit_definition_special_cinematic_unit_bit,
    _unit_definition_ignored_by_autoaiming_bit,
    _unit_definition_shields_fry_infection_forms_bit,
    _unit_definition_can_dual_wield_bit,
    _unit_definition_acts_as_gunner_for_parent_bit,
    _unit_definition_controlled_by_parent_gunner_bit,
    _unit_definition_parents_primary_weapon_bit,
    _unit_definition_parents_secondary_weapon_bit,
    _unit_definition_unit_has_boost_bit,
    k_number_of_unit_definition_flags
};

enum e_unit_camera_flags
{
    _unit_camera_pitch_bounds_absolute_space_bit,
    _unit_camera_only_collides_with_environment_bit,
    _unit_camera_hides_player_unit_from_camera_bit,
    _unit_camera_use_aiming_vector_instead_of_marker_forward_bit,
    k_number_of_unit_camera_flags
};

enum e_unit_camera_acceleration_input_variable
{
    _unit_camera_acceleration_input_variable_linear_velocity,
    _unit_camera_acceleration_input_variable_linear_acceleration,
    _unit_camera_acceleration_input_variable_yaw,
    _unit_camera_acceleration_input_variable_pitch,
    _unit_camera_acceleration_input_variable_roll,
    k_number_of_unit_camera_acceleration_input_variables
};

enum e_unit_camera_gamepad_input_shape
{
    _unit_camera_gamepad_input_shape_none,
    _unit_camera_gamepad_input_shape_unit_circle,
    _unit_camera_gamepad_input_shape_unit_square,
    k_number_of_unit_camera_gamepad_input_shapes
};

/* ---------- structures */

struct s_unit_screen_effect_reference
{
    s_tag_reference type;
};
static_assert(sizeof(s_unit_screen_effect_reference) == 0x10);

struct s_unit_camera_track_reference
{
    s_tag_reference track;
    s_tag_reference screen_effect;
};
static_assert(sizeof(s_unit_camera_track_reference) == 0x20);

struct s_unit_camera_obstruction
{
    real_fraction cylinder_fraction;
    angle obstruction_test_angle;
    real obstruction_max_inward_accel;
    real obstruction_max_outward_accel;
    real obstruction_max_velocity;
    real obstruction_return_delay;
};
static_assert(sizeof(s_unit_camera_obstruction) == 0x18);

struct s_unit_camera_acceleration_function
{
    c_enum<e_unit_camera_acceleration_input_variable, char> input_variable;
    char : 8;
    short : 16;
    s_tag_data data;
    real maximum_value;
    real camera_scale_axial;
    real camera_scale_perpendicular;
};
static_assert(sizeof(s_unit_camera_acceleration_function) == 0x24);

struct s_unit_camera_acceleration_displacement
{
    real maximum_camera_velocity;
    s_unit_camera_acceleration_function forward_back;
    s_unit_camera_acceleration_function left_right;
    s_unit_camera_acceleration_function up_down;
};
static_assert(sizeof(s_unit_camera_acceleration_displacement) == 0x70);

struct s_unit_camera_gamepad_stick_function
{
    s_tag_data data;
};
static_assert(sizeof(s_unit_camera_gamepad_stick_function) == 0x14);

struct s_unit_camera_gamepad_stick_info
{
    c_enum<e_unit_camera_gamepad_input_shape, char> input_shape;
    char : 8;
    short : 16;
    real_fraction peg_threshold;
    real_point2d pegged_time;
    real_point2d pegged_scale;
    angle peg_max_angular_velocity;
    c_tag_block<s_unit_camera_gamepad_stick_function> input_mapping_function;
};
static_assert(sizeof(s_unit_camera_gamepad_stick_info) == 0x28);

struct s_unit_camera
{
    c_flags<e_unit_camera_flags, word> flags;
    short : 16;
    string_id camera_marker_name;
    angle pitch_auto_level;
    angle_bounds pitch_range;
    c_tag_block<s_unit_camera_track_reference> camera_tracks;
    angle pitch_minimum_spring;
    angle pitch_maximum_spring;
    angle spring_velocity;
    angle look_acceleration;
    angle look_deceleration;
    real_fraction look_acceleration_smoothing_fraction;
    angle override_fov;
    s_unit_camera_obstruction camera_obstruction;
    c_tag_block<s_unit_camera_acceleration_displacement> camera_acceleration;
    c_tag_block<s_unit_camera_gamepad_stick_info> move_stick_overrides;
    c_tag_block<s_unit_camera_gamepad_stick_info> look_stick_overrides;
};
static_assert(sizeof(s_unit_camera) == 0x78);

struct s_unit_definition : s_object_definition
{
    c_flags<e_unit_definition_flags, long> unit_flags;
    c_enum<e_campaign_team, short> default_team;
    c_enum<e_ai_sound_volume, short> constant_sound_volume;
    s_tag_reference hologram_unit;
    c_tag_block<s_campaign_metagame_bucket> campaign_metagame_bucket;
    c_tag_block<s_unit_screen_effect_reference> screen_effects;
    real camera_stiffness;
    s_unit_camera unit_camera;
    s_unit_camera sync_action_camera;
    //
    // TODO: finish
    //
};
