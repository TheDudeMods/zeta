#pragma once

#include <cseries/cseries.h>
#include <datatypes/enum.h>
#include <datatypes/flags.h>
#include <math/real_math.h>
#include <objects/damage_new.h>
#include <items/item_definitions.h>

/* ---------- constants */

enum
{
    k_weapon_group_tag = 'weap'
};

/* ---------- types */

enum e_weapon_definition_flags
{
	// TODO
	k_number_of_weapon_definition_flags
};

enum e_weapon_definition_secondary_flags
{
	// TODO
	k_number_of_weapon_definition_secondary_flags
};

enum e_weapon_secondary_trigger_mode
{
	// TODO
	k_number_of_weapon_secondary_trigger_modes
};

struct s_melee_damage_parameters
{
	real_euler_angles2d damage_pyramid_angles; // defines the frustum from the camera that the melee-attack uses to find targets
	real damage_pyramid_depth; // how far the melee attack searches for a target
	real maximum_lunge_range; // 0 defaults to k_default_player_melee_lunge_distance
	real damage_lunge_explosive_depth; // the distance out from the pyramid center to spawn explosive effects. This value will be clamped to the damage pyramid depth. 0 defaults to the damage pyramid depth
	real runtime_damage_lunge_explosive_fraction;
	s_tag_reference melee_damage;
	s_tag_reference melee_response;
	s_tag_reference lunge_melee_damage; // this is only important for the energy sword
	s_tag_reference lunge_melee_response; // this is only important for the energy sword
	s_tag_reference empty_melee_damage; // this is only important for the energy sword
	s_tag_reference empty_melee_response; // this is only important for the energy sword
	s_tag_reference clang_melee_damage; // this is only important for the energy sword
	s_tag_reference clang_melee_response; // this is only important for the energy sword
	s_tag_reference clang_melee_against_melee_damage; // e.g. used by AR to damage sword guy when clanging sword attack
	s_tag_reference clang_melee_against_melee_response; // e.g. used by AR to damage sword guy when clanging sword attack
	s_tag_reference lunge_melee_explosive_damage;
};
static_assert(sizeof(s_melee_damage_parameters) == 0xC8);

struct s_aim_assist_parameters
{
	angle autoaim_angle; // the maximum angle that autoaim works at full strength
	real autoaim_range; // autoaim only has an effect along this distance
	real autoaim_falloff_range; // at what point the autoaim starts falling off. Fully falls off at autoaim range
	real autoaim_near_falloff_range; // at what point the autoaim reaches full power
	angle magnetism_angle; // the maximum angle that magnetism works at full strength
	real magnetism_range; // magnetism only has an effect along this distance
	real magnetism_falloff_range; // at what point magnetism starts falling off. Fully falls off at magnetism range
	real magnetism_near_falloff_range; // at what point magnetism reaches full power
	angle deviation_angle; // the maximum angle that a projectile is allowed to deviate from the gun barrel due to autoaim OR network lead vector reconstruction
	real unknown1;
	real unknown2;
	real unknown3;
	real unknown4;
	real unknown5;
	real unknown6;
};
static_assert(sizeof(s_aim_assist_parameters) == 0x3C);

struct s_tracking_type
{
	string_id tracking_type;
};
static_assert(sizeof(s_tracking_type) == 0x4);

struct s_target_tracking_parameters
{
	c_tag_block<s_tracking_type> tracking_types; // specify the kinds of targets this tracking system can lock on
	real acquire_time;
	real grace_time;
	real decay_time;
	s_tag_reference tracking_sound;
	s_tag_reference locked_sound;
};
static_assert(sizeof(s_target_tracking_parameters) == 0x38);

enum e_weapon_movement_penalty
{
	_weapon_movement_penalized_always,
	_weapon_movement_penalized_when_zoomed,
	_weapon_movement_penalized_when_zoomed_or_reloading,
	k_number_of_weapon_movement_penalties
};

enum e_weapon_type
{
	_weapon_type_undefined,
	_weapon_type_shotgun,
	_weapon_type_needler,
	_weapon_type_plasma_pistol,
	_weapon_type_plasma_rifle,
	_weapon_type_rocket_launcher,
	_weapon_type_energy_blade,
	_weapon_type_splaser,
	_weapon_type_shield,
	_weapon_type_scarab_gun,
	_weapon_type_wolverine_quad,
	_weapon_type_flak_cannon,
	_weapon_type_plasma_launcher,
	k_number_of_weapon_types
};

struct s_weapon_first_person_interface
{
	s_tag_reference first_person_model;
	s_tag_reference first_person_animation;
};
static_assert(sizeof(s_weapon_first_person_interface) == 0x20);

struct s_weapon_predicted_resources
{
	short type; // <--- TODO: enum
	short resource_index;
	long definition_index;
};
static_assert(sizeof(s_weapon_predicted_resources) == 0x8);

enum e_weapon_magazine_flags
{
	_weapon_magazine_wastes_rounds_when_reloaded_bit,
	_weapon_magazine_every_round_must_be_chambered_bit,
	_weapon_magazine_magazine_cannot_change_state_while_firing_bit, // will prevent reload until fire is complete (sticky det)
	_weapon_magazine_allow_overheated_reload_when_empty_bit,
	_weapon_magazine_bottomless_inventory_bit,
	k_number_of_weapon_magazine_flags
};

enum e_weapon_magazine_ammo_refill_type
{
	_weapon_magazine_ammo_refill_none,
	_weapon_magazine_ammo_refill_unsc,
	_weapon_magazine_ammo_refill_covenant,
	_weapon_magazine_ammo_refill_forerunner,
	k_number_of_weapon_magazine_refill_types
};

struct s_weapon_magazine_object
{
	short rounds;
	short : 16;
	s_tag_reference equipment;
};
static_assert(sizeof(s_weapon_magazine_object) == 0x14);

struct s_weapon_magazine_definition
{
	c_flags<e_weapon_magazine_flags, ulong> flags;
	short rounds_recharged; // per second
	short rounds_total_initial;
	short rounds_total_maximum;
	short rounds_loaded_maximum;
	short runtime_rounds_inventory_maximum;
	c_enum<e_weapon_magazine_ammo_refill_type, short> ammo_refill_type;
	real reload_dialogue_time; // the length of time we wait before saying the reload dialogue
	short rounds_reloaded;
	short : 16;
	real chamber_time; // the length of time it takes to chamber the next round
	real unknown1;
	real unknown2;
	real unknown3;
	real unknown4;
	real unknown5;
	real unknown6;
	s_tag_reference reloading_effect;
	s_tag_reference reloading_damage_effect;
	s_tag_reference chambering_effect;
	s_tag_reference chambering_damage_effect;
	c_tag_block<s_weapon_magazine_object> magazines;
};
static_assert(sizeof(s_weapon_magazine_definition) == 0x80);

struct s_weapon_trigger_definition
{
	// TODO
};

struct s_weapon_definition : s_item_definition
{
	c_flags<e_weapon_definition_flags, ulong> flags;
	c_flags<e_weapon_definition_secondary_flags, ulong> secondary_flags;
	string_id unused_label;
	c_enum<e_weapon_secondary_trigger_mode, short> secondary_trigger_mode;
	short maximum_alternate_shots_loaded;
	real turn_on_time; // how long after being readied it takes this weapon to switch its 'turned_on' attachment to 1.0
	real ready_time;
	s_tag_reference ready_effect;
	s_tag_reference ready_damage_effect;

	/* ------ heat */

	real_fraction heat_recovery_threshold; // the heat value a weapon must return to before leaving the overheated state, once it has become overheated in the first place
	real_fraction overheated_threshold; // the heat value over which a weapon first becomes overheated (should be greater than the heat recovery threshold)
	real_fraction heat_detonation_threshold; // the heat value above which the weapon has a chance of exploding each time it is fired
	real_fraction heat_detonation_fraction; // the percent chance (between 0.0 and 1.0) the weapon will explode when fired over the heat detonation threshold
	real heat_loss_per_second; // the amount of heat lost each second when the weapon is not being fired
	string_id heat_loss; // function value sets the current heat loss per second
	string_id heat_loss_venting; // function value sets the heat loss per second while weapon is being vented
	real heat_venting_time;
	real_fraction heat_venting_exit_heat; // heat at which to begin the venting exit animations so that the weapon is just about fully cooled when the exit animation completes
	real_fraction heat_illumination; // the amount of illumination given off when the weapon is overheated
	real_fraction heat_warning_threshold; // the amount of heat at which a warning will be displayed on the hud
	real overheated_heat_loss_per_second; // the amount of heat lost each second when the weapon is not being fired
	string_id overheated_heat_loss; // function value sets the heat loss per second when weapon is overheated
	s_tag_reference overheated;
	s_tag_reference overheated_damage_effect;
	s_tag_reference detonation;
	s_tag_reference detonation_damage_effect;

	/* ------ melee */

	c_tag_block<s_melee_damage_parameters> melee_damage_parameters;
	s_tag_reference clang_effect; // effect that is played in the air between two players that clang with this weapon
	c_enum<e_damage_reporting_type, char> melee_damage_reporting_type;
	char : 8;

	/* ------ zoom */

	short magnification_levels; // the number of magnification levels this weapon allows
	real_bounds magnification_range;

	/* ------ aim assist */

	s_aim_assist_parameters aim_assist;
	c_tag_block<s_target_tracking_parameters> target_tracking;

	/* ------ ballistics */

	real_bounds ballistic_arcing_firing_bounds; // word units; at the min range (or closer), the minimum ballistic arcing is used, at the max (or farther away), the maximum arcing is used
	real_bounds ballistic_arcing_fraction_bounds; // controls speed and degree of arc. 0 = low, fast, 1 = high, slow

	/* ------ movement */

	c_enum<e_weapon_movement_penalty, short> movement_penalized;
	short : 16;
	real_fraction forward_movement_penalty; // percent slowdown to forward movement for units carrying this weapon
	real_fraction sideways_movement_penalty; // percent slowdown to sideways and backward movement for units carrying this weapon

	/* ------ AI targeting parameters */

	real ai_scariness;

	/* ------ miscellaneous */

	real weapon_power_on_time;
	real weapon_power_off_time;
	s_tag_reference weapon_power_on_effect;
	s_tag_reference weapon_power_off_effect;
	real age_heat_recovery_penalty; // how much the weapon's heat recovery is penalized as it ages
	real age_rate_of_fire_penalty; // how much the weapon's rate of fire is penalized as it ages
	real_fraction age_misfire_start; // the age threshold when the weapon begins to misfire
	real_fraction age_misfire_chance; // at age 1.0, the misfire chance per shot
	s_tag_reference pickup_sound;
	s_tag_reference zoom_in_sound;
	s_tag_reference zoom_out_sound;
	real active_camo_ding; // how much to decrease active camo when a round is fired
	string_id handle_node; // the node that get's attached to the unit's hand

	/* ------ weapon labels */
	string_id weapon_class;
	string_id weapon_name;

	c_enum<e_weapon_type, short> weapon_type;
	short low_ammo_threshold;

	/* ------ interface */

	real unknown1;
	real unknown2;
	real unknown3;
	real unknown4;
	c_tag_block<s_weapon_first_person_interface> first_person;
	s_tag_reference hud_interface;
	s_tag_reference alternate_hud_interface; // the parent of the weapon can indicate that this hud should be used instead of the default

	c_tag_block<s_weapon_predicted_resources> predicted_resources;
	c_tag_block<s_weapon_magazine_definition> magazines;

	//
	// TODO: finish
	//
};
