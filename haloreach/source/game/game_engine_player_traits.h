#pragma once

#include <cseries/cseries.h>
#include <datatypes/enum.h>
#include <tag_files/tag_groups.h>

/* ---------- types */

enum e_damage_resistance_percentage_setting
{
	_damage_resistance_percentage_unchanged,
	_damage_resistance_percentage_10,
	_damage_resistance_percentage_50,
	_damage_resistance_percentage_90,
	_damage_resistance_percentage_100,
	_damage_resistance_percentage_110,
	_damage_resistance_percentage_150,
	_damage_resistance_percentage_200,
	_damage_resistance_percentage_300,
	_damage_resistance_percentage_500,
	_damage_resistance_percentage_1000,
	_damage_resistance_percentage_2000,
	_damage_resistance_percentage_invulnerable,
	k_number_of_damage_resistance_percentage_settings
};

enum e_health_multiplier_percentage_setting
{
	_health_multiplier_percentage_unchanged,
	_health_multiplier_percentage_0,
	_health_multiplier_percentage_100,
	_health_multiplier_percentage_150,
	_health_multiplier_percentage_200,
	_health_multiplier_percentage_300,
	_health_multiplier_percentage_400,
	k_number_of__health_multiplier_percentage_settings
};

enum e_recharge_rate_percentage_setting
{
	_recharge_rate_percentage_unchanged,
	_recharge_rate_percentage_negative_25,
	_recharge_rate_percentage_negative_10,
	_recharge_rate_percentage_negative_5,
	_recharge_rate_percentage_0,
	_recharge_rate_percentage_10,
	_recharge_rate_percentage_25,
	_recharge_rate_percentage_50,
	_recharge_rate_percentage_75,
	_recharge_rate_percentage_90,
	_recharge_rate_percentage_100,
	_recharge_rate_percentage_110,
	_recharge_rate_percentage_125,
	_recharge_rate_percentage_150,
	_recharge_rate_percentage_200,
	k_number_of_recharge_rate_percentage_settings
};

enum e_shield_multiplier_setting
{
	_shield_multiplier_unchanged,
	_shield_multiplier_no_shields,
	_shield_multiplier_normal_shields,
	_shield_multiplier_1x_overshields,
	_shield_multiplier_2x_overshields,
	_shield_multiplier_3x_overshields,
	_shield_multiplier_4x_overshields,
	k_number_of_shield_multipliers
};

enum e_player_trait_override_setting
{
	_player_trait_unchanged,
	_player_trait_off,
	_player_trait_on,
	k_number_of_player_trait_override_settings
};

enum e_shield_vampirism_percentage_setting
{
	_shield_vampirism_percentage_unchanged,
	_shield_vampirism_percentage_off,
	_shield_vampirism_percentage_10,
	_shield_vampirism_percentage_25,
	_shield_vampirism_percentage_50,
	_shield_vampirism_percentage_100,
	k_number_of_shield_vampirism_percentage_settings
};

enum e_player_trait_vitality_powerup_cancellation
{
	_player_trait_vitality_powerup_cancellation_unchanged,
	_player_trait_vitality_powerup_cancellation_none,
	_player_trait_vitality_powerup_cancellation_no_overshield,
	k_number_of_player_trait_vitality_powerup_cancellations
};

struct s_game_engine_player_traits_vitality
{
	c_enum<e_damage_resistance_percentage_setting, char> damage_resistance;
	c_enum<e_health_multiplier_percentage_setting, char> health_multiplier;
	c_enum<e_recharge_rate_percentage_setting, char> health_recharge_rate;
	c_enum<e_shield_multiplier_setting, char> shield_multiplier;
	c_enum<e_recharge_rate_percentage_setting, char> shield_recharge_rate;
	c_enum<e_recharge_rate_percentage_setting, char> overshield_recharge_rate;
	c_enum<e_player_trait_override_setting, char> headshot_immunity;
	c_enum<e_shield_vampirism_percentage_setting, char> vampirism_percent;
	c_enum<e_player_trait_override_setting, char> assassination_immunity;
	c_enum<e_player_trait_override_setting, char> deathless;
	c_enum<e_player_trait_override_setting, char> fast_track_armor;
	c_enum<e_player_trait_vitality_powerup_cancellation, char> powerup_cancellation;
};
static_assert(sizeof(s_game_engine_player_traits_vitality) == 0xC);

enum e_weapon_damage_modifier_setting
{
	_weapon_damage_modifier_unchanged,
	_weapon_damage_modifier_percentage_0,
	_weapon_damage_modifier_percentage_25,
	_weapon_damage_modifier_percentage_50,
	_weapon_damage_modifier_percentage_75,
	_weapon_damage_modifier_percentage_90,
	_weapon_damage_modifier_percentage_100,
	_weapon_damage_modifier_percentage_110,
	_weapon_damage_modifier_percentage_125,
	_weapon_damage_modifier_percentage_150,
	_weapon_damage_modifier_percentage_200,
	_weapon_damage_modifier_percentage_300,
	_weapon_damage_modifier_instant_kill,
	k_number_of_weapon_damage_modifier_settings
};

enum e_player_trait_weapons_initial_grenade_count_choices
{
	_player_trait_weapons_initial_grenade_count_unchanged,
	_player_trait_weapons_initial_grenade_count_map_default,
	_player_trait_weapons_initial_grenade_count_none,
	_player_trait_weapons_initial_grenade_count_1_frag,
	_player_trait_weapons_initial_grenade_count_2_frags,
	_player_trait_weapons_initial_grenade_count_3_frags,
	_player_trait_weapons_initial_grenade_count_4_frags,
	_player_trait_weapons_initial_grenade_count_1_plasma,
	_player_trait_weapons_initial_grenade_count_2_plasmas,
	_player_trait_weapons_initial_grenade_count_3_plasmas,
	_player_trait_weapons_initial_grenade_count_4_plasmas,
	_player_trait_weapons_initial_grenade_count_1x_each,
	_player_trait_weapons_initial_grenade_count_2x_each,
	_player_trait_weapons_initial_grenade_count_3x_each,
	_player_trait_weapons_initial_grenade_count_4x_each,
	k_number_of_player_trait_weapons_initial_grenade_count_choices
};

enum e_player_trait_weapons_infinite_ammo_choices
{
	_player_trait_weapons_infinite_ammo_unchanged,
	_player_trait_weapons_infinite_ammo_off,
	_player_trait_weapons_infinite_ammo_on,
	_player_trait_weapons_infinite_ammo_bottomless_clip,
	k_number_of_player_trait_weapons_infinite_ammo_choices
};

enum e_player_trait_weapons_equipment_usage_choices
{
	_player_trait_weapons_equipment_usage_unchanged,
	_player_trait_weapons_equipment_usage_off,
	_player_trait_weapons_equipment_usage_not_with_objectives,
	_player_trait_weapons_equipment_usage_on,
	k_number_of_player_trait_weapons_equipment_usage_choices
};

struct s_game_engine_player_traits_weapons
{
	c_enum<e_weapon_damage_modifier_setting, char> damage_modifier;
	c_enum<e_weapon_damage_modifier_setting, char> melee_damage_modifier;
	c_enum<e_player_trait_override_setting, char> grenade_regeneration;
	c_enum<e_player_trait_override_setting, char> weapon_pickup;
	c_enum<e_player_trait_weapons_initial_grenade_count_choices, char> initial_grenades;
	c_enum<e_player_trait_weapons_infinite_ammo_choices, char> infinite_ammo;
	c_enum<e_player_trait_weapons_equipment_usage_choices, char> equipment_usage;
	c_enum<e_player_trait_override_setting, char> equipment_drop;
	c_enum<e_player_trait_override_setting, char> infinite_equipment;
	char : 8;
	char : 8;
	char : 8;
	string_id initial_primary_weapon;
	string_id initial_secondary_weapon;
	string_id initial_equipment;
};
static_assert(sizeof(s_game_engine_player_traits_weapons) == 0x18);

enum e_player_trait_movement_speed_choices
{
	_player_trait_movement_speed_unchanged,
	_player_trait_movement_speed_percentage_0,
	_player_trait_movement_speed_percentage_25,
	_player_trait_movement_speed_percentage_50,
	_player_trait_movement_speed_percentage_75,
	_player_trait_movement_speed_percentage_90,
	_player_trait_movement_speed_percentage_100,
	_player_trait_movement_speed_percentage_110,
	_player_trait_movement_speed_percentage_120,
	_player_trait_movement_speed_percentage_130,
	_player_trait_movement_speed_percentage_140,
	_player_trait_movement_speed_percentage_150,
	_player_trait_movement_speed_percentage_160,
	_player_trait_movement_speed_percentage_170,
	_player_trait_movement_speed_percentage_180,
	_player_trait_movement_speed_percentage_190,
	_player_trait_movement_speed_percentage_200,
	_player_trait_movement_speed_percentage_300,
	k_number_of_player_trait_movement_speed_choices
};

enum e_player_trait_movement_gravity_multiplier_choices
{
	_player_trait_movement_gravity_multiplier_unchanged,
	_player_trait_movement_gravity_multiplier_percentage_50,
	_player_trait_movement_gravity_multiplier_percentage_75,
	_player_trait_movement_gravity_multiplier_percentage_100,
	_player_trait_movement_gravity_multiplier_percentage_150,
	_player_trait_movement_gravity_multiplier_percentage_200,
	_player_trait_movement_gravity_multiplier_percentage_250,
	_player_trait_movement_gravity_multiplier_percentage_300,
	_player_trait_movement_gravity_multiplier_percentage_350,
	_player_trait_movement_gravity_multiplier_percentage_400,
	_player_trait_movement_gravity_multiplier_percentage_450,
	_player_trait_movement_gravity_multiplier_percentage_500,
	_player_trait_movement_gravity_multiplier_percentage_550,
	_player_trait_movement_gravity_multiplier_percentage_600,
};

enum e_player_trait_movement_vehicle_usage_choices
{
	_player_trait_movement_vehicle_usage_unchanged,
	_player_trait_movement_vehicle_usage_none,
	_player_trait_movement_vehicle_usage_passenger_only,
	_player_trait_movement_vehicle_usage_driver_only,
	_player_trait_movement_vehicle_usage_gunner_only,
	_player_trait_movement_vehicle_usage_not_passenger,
	_player_trait_movement_vehicle_usage_not_driver,
	_player_trait_movement_vehicle_usage_not_gunner,
	_player_trait_movement_vehicle_usage_full,
	k_number_of_player_trait_movement_vehicle_usage_choices
};

enum e_player_trait_movement_double_jump_choices
{
	_player_trait_movement_double_jump_unchanged,
	_player_trait_movement_double_jump_off,
	_player_trait_movement_double_jump_on,
	_player_trait_movement_double_jump_on_plus_lunge,
	k_number_of_player_trait_movement_double_jump_choices
};

struct s_game_engine_player_traits_movement
{
	c_enum<e_player_trait_movement_speed_choices, char> speed;
	c_enum<e_player_trait_movement_gravity_multiplier_choices, char> gravity_multiplier;
	c_enum<e_player_trait_movement_vehicle_usage_choices, char> vehicle_usage;
	c_enum<e_player_trait_movement_double_jump_choices, char> double_jump;
	long override_jump_height_percentage; // -1 is unchanged, 0-400 is the percentage of the default jump height
};
static_assert(sizeof(s_game_engine_player_traits_movement) == 0x8);

enum e_player_trait_appearance_active_camo_choices
{
	_player_trait_appearance_active_camo_unchanged,
	_player_trait_appearance_active_camo_off,
	_player_trait_appearance_active_camo_poor,
	_player_trait_appearance_active_camo_good,
	_player_trait_appearance_active_camo_excellent,
	_player_trait_appearance_active_camo_invisible,
	k_number_of_player_trait_appearance_active_camo_choices
};

enum e_player_trait_appearance_waypoint_choices
{
	_player_trait_appearance_waypoint_unchanged,
	_player_trait_appearance_waypoint_off,
	_player_trait_appearance_waypoint_allies,
	_player_trait_appearance_waypoint_all,
	k_number_of_player_trait_appearance_waypoint_choices
};

enum e_player_trait_appearance_gamertag_visible_choices
{
	_player_trait_appearance_gamertag_visible_unchanged,
	_player_trait_appearance_gamertag_visible_off,
	_player_trait_appearance_gamertag_visible_allies,
	_player_trait_appearance_gamertag_visible_all,
	k_number_of_player_trait_appearance_gamertag_visible_choices
};

enum e_player_trait_appearance_aura_choices
{
	_player_trait_appearance_aura_unchanged,
	_player_trait_appearance_aura_off,
	_player_trait_appearance_aura_team_color,
	_player_trait_appearance_aura_black,
	_player_trait_appearance_aura_white,
	k_number_of_player_trait_appearance_aura_choices
};

enum e_player_trait_appearance_forced_color_choices
{
	_player_trait_appearance_forced_color_unchanged,
	_player_trait_appearance_forced_color_disabled,
	_player_trait_appearance_forced_color_red,
	_player_trait_appearance_forced_color_blue,
	_player_trait_appearance_forced_color_green,
	_player_trait_appearance_forced_color_orange,
	_player_trait_appearance_forced_color_purple,
	_player_trait_appearance_forced_color_gold,
	_player_trait_appearance_forced_color_brown,
	_player_trait_appearance_forced_color_pink,
	_player_trait_appearance_forced_color_white,
	_player_trait_appearance_forced_color_black,
	_player_trait_appearance_forced_color_zombie,
	_player_trait_appearance_forced_color_gray,
	k_number_of_player_trait_appearance_forced_color_choices
};

struct s_game_engine_player_traits_appearance
{
	c_enum<e_player_trait_appearance_active_camo_choices, char> active_camo;
	c_enum<e_player_trait_appearance_waypoint_choices, char> waypoint;
	c_enum<e_player_trait_appearance_gamertag_visible_choices, char> gamertag_visible;
	c_enum<e_player_trait_appearance_aura_choices, char> aura;
	c_enum<e_player_trait_appearance_forced_color_choices, char> forced_color;
	char : 8;
	char : 8;
	char : 8;
};
static_assert(sizeof(s_game_engine_player_traits_appearance) == 0x8);

enum e_player_trait_sensors_motion_tracker_choices
{
	_player_trait_sensors_motion_tracker_unchanged,
	_player_trait_sensors_motion_tracker_disabled,
	_player_trait_sensors_motion_tracker_ally_movement,
	_player_trait_sensors_motion_tracker_player_movement,
	_player_trait_sensors_motion_tracker_player_locations,
	k_number_of_player_trait_sensors_motion_tracker_choices
};

enum e_player_trait_sensors_motion_tracker_range_choices
{
	_player_trait_sensors_motion_tracker_range_unchanged,
	_player_trait_sensors_motion_tracker_range_10_meters,
	_player_trait_sensors_motion_tracker_range_15_meters,
	_player_trait_sensors_motion_tracker_range_25_meters,
	_player_trait_sensors_motion_tracker_range_50_meters,
	_player_trait_sensors_motion_tracker_range_75_meters,
	_player_trait_sensors_motion_tracker_range_100_meters,
	_player_trait_sensors_motion_tracker_range_150_meters,
	k_number_of_player_trait_sensors_motion_tracker_range_choices
};

struct s_game_engine_player_traits_sensors
{
	c_enum<e_player_trait_sensors_motion_tracker_choices, char> motion_tracker;
	c_enum<e_player_trait_sensors_motion_tracker_range_choices, char> motion_tracker_range;
	c_enum<e_player_trait_override_setting, char> directional_damage_indicator;
	char : 8;
};
static_assert(sizeof(s_game_engine_player_traits_sensors) == 0x4);

struct s_game_engine_player_traits
{
	c_tag_block<s_game_engine_player_traits_vitality> vitality_traits;
	c_tag_block<s_game_engine_player_traits_weapons> weapon_traits;
	c_tag_block<s_game_engine_player_traits_movement> movement_traits;
	c_tag_block<s_game_engine_player_traits_appearance> appearance_traits;
	c_tag_block<s_game_engine_player_traits_sensors> sensors;
};
static_assert(sizeof(s_game_engine_player_traits) == 0x3C);
