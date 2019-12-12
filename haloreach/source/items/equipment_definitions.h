#pragma once

#include <cseries/cseries.h>
#include <datatypes/enum.h>
#include <datatypes/flags.h>
#include <math/real_math.h>
#include <tag_files/tag_groups.h>
#include <items/item_definitions.h>
#include <units/unit_definitions.h>
#include <ai/ai_traits.h>
#include <game/game_engine_player_traits.h>
#include <game/game_powerups.h>

/* ---------- constants */

enum
{
	k_equipment_group_tag = 'eqip'
};

/* ---------- types */

enum e_equipment_flags
{
	_equipment_flags_unknown0_bit,
	_equipment_flags_unknown1_bit,
	_equipment_flags_unknown2_bit,
	_equipment_flags_unknown3_bit,
	_equipment_3rd_person_camera_while_active_bit,
	_equipment_3rd_person_camera_during_activation_animation_bit,
	_equipment_hide_reticule_while_active_bit,
	_equipment_cannot_be_active_while_airborne_bit,
	_equipment_cannot_activate_while_airborne_bit,
	_equipment_cannot_activate_while_standing_on_biped_bit,
	_equipment_cannot_be_active_in_vehicle_bit,
	_equipment_suppresses_weapons_while_active_bit,
	_equipment_suppresses_melee_while_active_bit,
	_equipment_suppresses_grenades_while_active_bit,
	_equipment_suppresses_device_interaction_while_active_bit,
	_equipment_suppresses_sprint_while_active_bit,
	_equipment_suppresses_entering_vehicle_bit,
	_equipment_duck_sound_while_active_bit,
	_equipment_blocks_tracking_while_active_bit,
	_equipment_readies_weapon_on_deactivation_bit,
	_equipment_drops_support_weapons_on_activation_bit,
	_equipment_hides_weapon_on_activation_bit,
	_equipment_cannot_activate_in_vehicle_bit,
	_equipment_flags_unknown23_bit,
	_equipment_flags_unknown24_bit,
	_equipment_flags_unknown25_bit,
	_equipment_flags_unknown26_bit,
	_equipment_flags_unknown27_bit,
	_equipment_flags_unknown28_bit,
	_equipment_flags_unknown29_bit,
	_equipment_flags_unknown30_bit,
	_equipment_flags_unknown31_bit,
	k_number_of_equipment_flags
};

enum e_equipment_pickup_behavior
{
	_equipment_pickup_behavior_none = NONE,
	_equipment_pickup_behavior_automatic_if_empty, // picks it up automatically, if you have no equipment in your inventory, otherwise, press RB to swap
	_equipment_pickup_behavior_always_automatic, // always picks it up, whether or not you have another piece of equipment
	_equipment_pickup_behavior_manual, // press RB to pickup or swap this equipment
	_equipment_pickup_behavior_activate_on_ground, // Never pickup, press RB to activate it in-place
	k_number_of_equipment_pickup_behaviors
};

enum e_equipment_activation_source
{
	_equipment_activation_source_toggle, // toggles state when X is pressed
	_equipment_activation_source_hold, // activates when X is pressed and deactivates when X is released
	_equipment_activation_source_double_tap, // activates when X is pressed twice in quick succession
	_equipment_activation_source_shield_fail, // activates when player shield fails
	_equipment_activation_source_death, // activates when player dies
	k_number_of_equipment_activation_sources
};

struct s_equipment_ability_type_multiplayer_powerup
{
	c_enum<e_multiplayer_powerup_flavor, long> flavor;
};
static_assert(sizeof(s_equipment_ability_type_multiplayer_powerup) == 0x4);

enum e_equipment_spawner_type
{
	_equipment_spawner_type_along_aiming_vector,
	_equipment_spawner_type_camera_pos_z_plane,
	_equipment_spawner_type_foot_pos_z_plane,
	k_number_of_equipment_spawner_types
};

struct s_equipment_ability_type_spawner
{
	s_tag_reference spawned_object;
	s_tag_reference spawned_effect;
	real spawn_radius; // distance from players eyeball on the z-plane that this effect spawns
	real spawn_z_offset; // z-offset of effect spawn
	real spawn_area_radius; // need a sphere of radius r's free space in order to spawn, otherwise we pick a new spawn location
	real spawn_velocity;
	c_enum<e_equipment_spawner_type, short> type;
	short : 16;
};
static_assert(sizeof(s_equipment_ability_type_spawner) == 0x34);

struct s_equipment_ability_type_proximity_mine
{
	s_tag_reference explosion_effect;
	s_tag_reference explosion_damage_effect;
	real arm_time; // time before it becomes a proximity mine
	real self_destruct_time; // seconds after it is created that it must self destruct. 0 means never destroy
	real trigger_time; // seconds object moving at trigger velocity takes to trigger explosion. This will smooth out sensitivity to velocity noise
	real trigger_velocity; // world units per second at which we trigger explosion
};
static_assert(sizeof(s_equipment_ability_type_proximity_mine) == 0x30);

struct s_equipment_ability_type_motion_tracker_noise
{
	real arm_time; // time before it starts making noise
	real noise_radius; // radius in WU that the noise extends to
	long noise_count; // number of noise points that are generated
	real flash_radius; // radius in WU that the damage flash noise extends to
};
static_assert(sizeof(s_equipment_ability_type_motion_tracker_noise) == 0x10);

struct s_equipment_effect_with_threshold
{
	real threshold_energy_burned; // how much energy you have to burn to play this effect
	real energy_adjustment; // how much energy to add when playing this effect
	s_tag_reference effect;
};
static_assert(sizeof(s_equipment_effect_with_threshold) == 0x18);

struct s_equipment_ability_type_invincibility
{
	string_id invincibility_material;
	short invincibility_material_type;
	short : 16;
	real shield_recharge_rate; // while active, shields recharge at this fraction per second
	real shield_max_recharge_level; // highest level shield can recharge to (can be up to 4)
	s_tag_reference override_collision_damage;
	s_tag_reference ai_melee_reflect_damage;
	s_tag_reference player_melee_reflect_damage;
	string_id loop_invincibility_shield_name; // active while the equipment is in use (used for shield rendering effects)
	string_id post_invincibility_shield_name; // active once the equipment is no longer in use
	s_tag_function post_invincibility_time_to_shield_level_function;
	real maximum_vertical_velocity; // we use this to specify the domain of the active vertical velocity funtion
	s_tag_function active_vertical_velocity_damping;
	c_tag_block<s_equipment_effect_with_threshold> threshold_effects;
};
static_assert(sizeof(s_equipment_ability_type_invincibility) == 0x80);

enum e_equipment_tree_of_life_flags
{
	_equipment_tree_of_life_unstuns_shields_bit,
	_equipment_tree_of_life_unstuns_body_bit,
	k_number_of_equipment_tree_of_life_flags
};

struct s_equipment_ability_type_tree_of_life
{
	c_flags<e_equipment_tree_of_life_flags, ulong> flags;
	string_id origin_marker;
	real radius;
};
static_assert(sizeof(s_equipment_ability_type_tree_of_life) == 0xC);

struct s_equipment_ability_type_shapeshifter
{
	string_id region_name;
	string_id inactive_permutation_name;
	string_id active_permutation_name;
};
static_assert(sizeof(s_equipment_ability_type_shapeshifter) == 0xC);

struct s_equipment_ability_type_player_trait_field
{
	real radius; // unused
	c_tag_block<s_game_engine_player_traits> active_player_traits;
	c_tag_block<s_game_engine_player_traits> inactive_player_traits;
};
static_assert(sizeof(s_equipment_ability_type_player_trait_field) == 0x1C);

struct s_equipment_ability_type_ai_trait_field
{
	c_tag_block<s_ai_equipment_traits> active_ai_equipment_traits;
	c_tag_block<s_ai_equipment_traits> inactive_ai_equipment_traits;
};
static_assert(sizeof(s_equipment_ability_type_ai_trait_field) == 0x18);

enum e_equipment_repulsor_field_flags
{
	_equipment_repulsor_field_affects_projectiles_bit,
	_equipment_repulsor_field_affects_vehicles_bit,
	_equipment_repulsor_field_affects_bipeds_bit,
	k_number_of_equipment_repulsor_field_flags
};

struct s_equipment_ability_type_repulsor_field
{
	c_flags<e_equipment_repulsor_field_flags, ulong> flags;
	real radius;
	real power;
};
static_assert(sizeof(s_equipment_ability_type_repulsor_field) == 0xC);

enum e_equipment_stasis_field_flags
{
	_equipment_stasis_field_affects_projectiles_bit,
	_equipment_stasis_field_affects_vehicles_bit,
	_equipment_stasis_field_affects_bipeds_bit,
	k_number_of_equipment_stasis_field_flags
};

struct s_equipment_ability_type_stasis_field
{
	c_flags<e_equipment_stasis_field_flags, ulong> flags;
	real radius;
	
	/* ------ time dilation:
		the effective rate at which time passes for objects in the field
		values below 0.45 screw up jumping
	*/

	real time_dilation_player_characters;
	real time_dilation_projectiles;
	real time_dilation_vehicles;
	real time_dilation_other;

	real max_biped_turning_rate;

	real gravity_multiplier; // negative values will invert gravity
};
static_assert(sizeof(s_equipment_ability_type_stasis_field) == 0x20);

struct s_equipment_definition : s_item_definition
{
	/* ------ timers */

	real duration; // use negative numbers for infinite duration
	real warmup_time; // time before the equipment truly becomes active
	real cooldown_time; // for equipment that suppresses combat actions, these actions remain suppressed for this long after the equipment deactivates Note that if this equipment also readies weapons when deactivated, the weapon will not be usable until both this timer expires and the ready animation has finished, whichever is longer
	real phantom_volume_activation_time; // time in seconds for the phantom volumes on this object to start accelerating things in them

	/* ------ energy */

	real minimum_activation_energy; // energy must be at least this high to activate Like activation cost, but doesn't actually change energy levels
	real low_energy_warning_threshold; // used by UI
	real activation_energy_cost;
	real deactivation_energy_cost;
	real active_energy_rate;
	real recharge_rate;
	s_tag_function movement_speed_to_energy_rate;
	real movement_speed_domain;

	c_flags<e_equipment_flags, ulong> flags;
	c_enum<e_equipment_pickup_behavior, short> pickup_behavior;
	c_enum<e_equipment_activation_source, char> activation_mode;
	char object_noise_adjustment; // for AI perception. while active, adjusts noises made by the owner unit by this many 'notches'. note that this is additive, so a positive number is louder and a negative number is quieter
	string_id unit_stow_marker; // the marker on the unit to attach this equipment to when it is stowed. The equipment should have a marker named "equipment_stow_anchor"
	real_argb_color forced_primary_change_color; // sets the primary change color on the unit to this if the flag above is checked
	real_argb_color forced_secondary_change_color; // sets the secondary change color on the unit to this if the flag above is checked

	/* ------ ai */

	real danger_radius; // how large a danger zone we should create around this equipment (0 means no danger zone)
	real min_deployment_distance; // how far does my target have to be for me to throw this at them
	real awareness_time; // how long I should go unnoticed by nearby enemies
	string_id ai_dialogue_equipment_type; // the equipment ability type name used by the ai dialog system used to filter equipment activation dialogue events
	c_tag_block<s_unit_camera> override_camera;

	/* ------ abilities */

	c_tag_block<s_equipment_ability_type_multiplayer_powerup> multiplayer_powerup;
	c_tag_block<s_equipment_ability_type_spawner> spawner;
	c_tag_block<s_equipment_ability_type_proximity_mine> proximity_mine;
	c_tag_block<s_equipment_ability_type_motion_tracker_noise> motion_tracker_noise;
	s_tag_block unknown_ability_block; // TODO
	c_tag_block<s_equipment_ability_type_invincibility> invincibility_mode;
	c_tag_block<s_equipment_ability_type_tree_of_life> tree_of_life;
	c_tag_block<s_equipment_ability_type_shapeshifter> shapeshifter;
	c_tag_block<s_equipment_ability_type_player_trait_field> player_trait_field;
	c_tag_block<s_equipment_ability_type_ai_trait_field> ai_trait_field;
	c_tag_block<s_equipment_ability_type_repulsor_field> repulsor_field;
	c_tag_block<s_equipment_ability_type_stasis_field> stasis_field;
	s_tag_block iwhbydaddy; // TODO
	s_tag_block super_jump; // TODO
	s_tag_block ammo_pack; // TODO
	s_tag_block power_fist; // TODO

	//
	// TODO: finish
	//
};
