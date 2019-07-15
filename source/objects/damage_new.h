#pragma once

#include <cseries/cseries.h>
#include <tag_files/tag_groups.h>

/* ---------- constants */

enum
{
    k_damage_response_group_tag = 'drdf'
};

/* ---------- enumerators */

enum e_damage_reporting_type
{
	_damage_reporting_type_guardians_unknown,
	_damage_reporting_type_guardians,
	_damage_reporting_type_guardians_scripting,
	_damage_reporting_type_suicide,
	_damage_reporting_type_magnum,
	_damage_reporting_type_assault_rifle,
	_damage_reporting_type_dmr,
	_damage_reporting_type_shotgun,
	_damage_reporting_type_sniper_rifle,
	_damage_reporting_type_rocket_launcher,
	_damage_reporting_type_spartan_laser,
	_damage_reporting_type_frag_grenade,
	_damage_reporting_type_grenade_launcher,
	_damage_reporting_type_plasma_pistol,
	_damage_reporting_type_needler,
	_damage_reporting_type_plasma_rifle,
	_damage_reporting_type_plasma_repeater,
	_damage_reporting_type_needle_rifle,
	_damage_reporting_type_spiker,
	_damage_reporting_type_plasma_launcher,
	_damage_reporting_type_gravity_hammer,
	_damage_reporting_type_energy_sword,
	_damage_reporting_type_plasma_grenade,
	_damage_reporting_type_concussion_rifle,
	_damage_reporting_type_ghost,
	_damage_reporting_type_revenant,
	_damage_reporting_type_revenant_gunner,
	_damage_reporting_type_wraith,
	_damage_reporting_type_wraith_turret,
	_damage_reporting_type_banshee,
	_damage_reporting_type_banshee_bomb,
	_damage_reporting_type_seraph,
	_damage_reporting_type_mongoose,
	_damage_reporting_type_warthog,
	_damage_reporting_type_warthog_chaingun,
	_damage_reporting_type_warthog_gauss,
	_damage_reporting_type_warthog_rocket,
	_damage_reporting_type_scorpion,
	_damage_reporting_type_scorpion_turret,
	_damage_reporting_type_falcon,
	_damage_reporting_type_falcon_gunner,
	_damage_reporting_type_falling,
	_damage_reporting_type_generic_collision,
	_damage_reporting_type_generic_melee,
	_damage_reporting_type_generic_explosion,
	_damage_reporting_type_birthday_explosion,
	_damage_reporting_type_flag,
	_damage_reporting_type_bomb,
	_damage_reporting_type_bomb_explosion,
	_damage_reporting_type_ball,
	_damage_reporting_type_teleporter,
	_damage_reporting_type_shifted_blame,
	_damage_reporting_type_armor_lock,
	_damage_reporting_type_target_locator,
	_damage_reporting_type_human_turret,
	_damage_reporting_type_plasma_cannon,
	_damage_reporting_type_plasma_mortar,
	_damage_reporting_type_plasma_turret,
	_damage_reporting_type_shade_turret,
	_damage_reporting_type_sabre,
	_damage_reporting_type_focus_rifle,
	_damage_reporting_type_fuel_rod,
	_damage_reporting_type_missile_pod,
	_damage_reporting_type_tank,
	_damage_reporting_type_hornet,
	k_number_of_damage_reporting_types
};
