#include <units/unit_definitions.h>
#include <units/biped_definitions.h>
#include <units/vehicle_definitions.h>

extern s_tag_group_definition object_group;
extern s_enum_definition campaign_team_enum;
extern s_enum_definition ai_sound_volume_enum;
extern s_tag_block_definition campaign_metagame_bucket_block;

/* ---------- definitions */

TAG_ENUM(
    unit_definition_flags_enum,
    k_number_of_unit_definition_flags)
{
    { "circular_aiming", _unit_definition_circular_aiming_bit },
    { "destroyed_after_dying", _unit_definition_destroyed_after_dying_bit },
    { "half_speed_interpolation", _unit_definition_half_speed_interpolation_bit },
    { "fires_from_camera", _unit_definition_fires_from_camera_bit },
    { "entrance_inside_bounding_sphere", _unit_definition_entrance_inside_bounding_sphere_bit },
    { "doesnt_show_readied_weapon", _unit_definition_doesnt_show_readied_weapon_bit },
    { "causes_passenger_dialogue", _unit_definition_causes_passenger_dialogue_bit },
    { "resists_pings", _unit_definition_resists_pings_bit },
    { "melee_attack_is_fatal", _unit_definition_melee_attack_is_fatal_bit },
    { "dont_reface_during_pings", _unit_definition_dont_reface_during_pings_bit },
    { "has_no_aiming", _unit_definition_has_no_aiming_bit },
    { "simple_creature", _unit_definition_simple_creature_bit },
    { "impact_melee_attaches_to_unit", _unit_definition_impact_melee_attaches_to_unit_bit },
    { "impact_melee_dies_on_shield", _unit_definition_impact_melee_dies_on_shield_bit },
    { "cannot_open_doors_automatically", _unit_definition_cannot_open_doors_automatically_bit },
    { "melee_attackers_cannot_attach", _unit_definition_melee_attackers_cannot_attach_bit },
    { "not_instantly_killed_by_melee", _unit_definition_not_instantly_killed_by_melee_bit },
    { "shield_sapping", _unit_definition_shield_sapping_bit },
    { "runs_around_flaming", _unit_definition_runs_around_flaming_bit },
    { "inconsequential", _unit_definition_inconsequential_bit },
    { "special_cinematic_unit", _unit_definition_special_cinematic_unit_bit },
    { "ignored_by_autoaiming", _unit_definition_ignored_by_autoaiming_bit },
    { "shields_fry_infection_forms", _unit_definition_shields_fry_infection_forms_bit },
    { "can_dual_wield", _unit_definition_can_dual_wield_bit },
    { "acts_as_gunner_for_parent", _unit_definition_acts_as_gunner_for_parent_bit },
    { "controlled_by_parent_gunner", _unit_definition_controlled_by_parent_gunner_bit },
    { "parents_primary_weapon", _unit_definition_parents_primary_weapon_bit },
    { "parents_secondary_weapon", _unit_definition_parents_secondary_weapon_bit },
    { "unit_has_boost", _unit_definition_unit_has_boost_bit },
};

TAG_REFERENCE(
    unit_hologram_unit_reference,
    2)
{
    k_biped_group_tag,
    k_vehicle_group_tag
};

TAG_GROUP(
    unit_group,
    k_unit_group_tag,
    sizeof(s_unit_definition),
    &object_group)
{
    { _field_long_flags, "unit_flags", &unit_definition_flags_enum },
    { _field_short_enum, "default_team", &campaign_team_enum },
    { _field_short_enum, "constant_sound_volume", &ai_sound_volume_enum },
    { _field_tag_reference, "hologram_unit", &unit_hologram_unit_reference },
    { _field_block, "campaign_metagame_bucket", &campaign_metagame_bucket_block },
    //
    // TODO: finish
    //
    { _field_terminator }
};
