#pragma once

#include <cseries/cseries.h>
#include <datatypes/enum.h>
#include <datatypes/flags.h>
#include <math/real_math.h>
#include <tag_files/tag_groups.h>
#include <items/item_definitions.h>

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

	/* ------ AI:
		settings which the AI use to know how they should react to this equipment
	*/

	real danger_radius; // how large a danger zone we should create around this equipment (0 means no danger zone)
	real min_deployment_distance; // how far does my target have to be for me to throw this at them
	real awareness_time; // how long I should go unnoticed by nearby enemies
	string_id ai_dialogue_equipment_type; // the equipment ability type name used by the ai dialog system used to filter equipment activation dialogue events

	// TODO: finish
};
