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
    k_unit_group_tag = 'unit'
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

/* ---------- structures */

struct s_unit_definition : s_object_definition
{
    c_flags<e_unit_definition_flags, long> unit_flags;
    c_enum<e_campaign_team, short> default_team;
    c_enum<e_ai_sound_volume, short> constant_sound_volume;
    s_tag_reference hologram_unit;
    c_tag_block<s_campaign_metagame_bucket> campaign_metagame_bucket;
    //
    // TODO: finish
    //
};
