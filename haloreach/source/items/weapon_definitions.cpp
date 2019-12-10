#include <objects/crates.h>
#include <objects/damage.h>
#include <objects/damage_new.h>
#include <models/render_model_definitions.h>
#include <animations/animation_definitions.h>
#include <sound/sound_definitions.h>
#include <effects/effects.h>
#include <effects/material_effect_definitions.h>
#include <effects/screen_effect.h>
#include <interface/chud/chud_definitions.h>
#include <items/equipment_definitions.h>
#include <items/projectile_definitions.h>
#include <items/weapon_definitions.h>
#include <units/vehicle_definitions.h>

/* ---------- definitions */

TAG_ENUM(
	weapon_definition_flags_enum,
	k_number_of_weapon_definition_flags)
{
	{ "vertical_heat_display", _weapon_vertical_heat_display_bit },
	{ "mutually_exclusive_triggers", _weapon_mutually_exclusive_triggers_bit },
	{ "attacks_automatically_on_bump", _weapon_attacks_automatically_on_bump_bit },
	{ "must_be_readied", _weapon_must_be_readied_bit },
	{ "doesn_t_count_towards_maximum", _weapon_doesn_t_count_towards_maximum_bit },
	{ "aim_assists_only_when_zoomed", _weapon_aim_assists_only_when_zoomed_bit },
	{ "prevents_grenade_throwing", _weapon_prevents_grenade_throwing_bit },
	{ "must_be_picked_up", _weapon_must_be_picked_up_bit },
	{ "holds_triggers_when_dropped", _weapon_holds_triggers_when_dropped_bit },
	{ "prevents_melee_attack", _weapon_prevents_melee_attack_bit },
	{ "detonates_when_dropped", _weapon_detonates_when_dropped_bit },
	{ "cannot_fire_at_maximum_age", _weapon_cannot_fire_at_maximum_age_bit },
	{ "secondary_trigger_overrides_grenades", _weapon_secondary_trigger_overrides_grenades_bit },
	{ "does_not_depower_active_camo_in_multiplayer", _weapon_does_not_depower_active_camo_in_multiplayer_bit },
	{ "enables_integrated_night_vision", _weapon_enables_integrated_night_vision_bit },
	{ "ai_uses_weapon_melee_damage", _weapon_ai_uses_weapon_melee_damage_bit },
	{ "forces_no_binoculars", _weapon_forces_no_binoculars_bit },
	{ "loop_fp_firing_animation", _weapon_loop_fp_firing_animation_bit },
	{ "prevents_sprinting", _weapon_prevents_sprinting_bit },
	{ "cannot_fire_while_boosting", _weapon_cannot_fire_while_boosting_bit },
	{ "prevents_driving", _weapon_prevents_driving_bit },
	{ "third_person_camera", _weapon_third_person_camera_bit },
	{ "can_be_dual_wielded", _weapon_can_be_dual_wielded_bit },
	{ "can_only_be_dual_wielded", _weapon_can_only_be_dual_wielded_bit },
	{ "melee_only", _weapon_melee_only_bit },
	{ "cannot_fire_if_parent_dead", _weapon_cannot_fire_if_parent_dead_bit },
	{ "weapon_ages_with_each_kill", _weapon_weapon_ages_with_each_kill_bit },
	{ "weapon_uses_old_dual_fire_error_code", _weapon_weapon_uses_old_dual_fire_error_code_bit },
	{ "primary_trigger_melee_attacks", _weapon_primary_trigger_melee_attacks_bit },
	{ "cannot_be_used_by_player", _weapon_cannot_be_used_by_player_bit },
	{ "strict_deviation_angle", _weapon_strict_deviation_angle_bit },
	{ "notifies_target_units", _weapon_notifies_target_units_bit },
};

TAG_ENUM(
	weapon_definition_secondary_flags_enum,
	k_number_of_weapon_definition_secondary_flags)
{
	{ "magnetizes_only_when_zoomed", _weapon_magnetizes_only_when_zoomed_bit },
	{ "force_enable_equipment_tossing", _weapon_force_enable_equipment_tossing_bit },
	{ "non_lunge_melee_dash_disabled", _weapon_non_lunge_melee_dash_disabled_bit },
	{ "do_not_drop_on_dual_wield_melee", _weapon_do_not_drop_on_dual_wield_melee_bit },
	{ "is_equipment_special_weapon", _weapon_is_equipment_special_weapon_bit },
	{ "uses_ghost_reticle", _weapon_uses_ghost_reticle_bit },
	{ "never_overheats", _weapon_never_overheats_bit },
	{ "force_tracers_to_come_from_weapon_barrel", _weapon_force_tracers_to_come_from_weapon_barrel_bit },
	{ "cannot_fire_during_emp", _weapon_cannot_fire_during_emp_bit },
	{ "weapon_can_headshot", _weapon_weapon_can_headshot_bit },
	{ "ai_cannot_fire_tracking_projectiles", _weapon_ai_cannot_fire_tracking_projectiles_bit },
	{ "force_match_owner_animation", _weapon_force_match_owner_animation_bit },
	{ "weapon_unzooms_on_damage", _weapon_weapon_unzooms_on_damage_bit },
	{ "do_not_drop_on_equipment_activation", _weapon_do_not_drop_on_equipment_activation_bit },
	{ "weapon_can_not_be_dropped", _weapon_weapon_can_not_be_dropped_bit },
	{ "disable_function_overlays_during_reload", _weapon_disable_function_overlays_during_reload_bit },
	{ "throw_weapon_on_primary_fire", _weapon_throw_weapon_on_primary_fire_bit },
	{ "do_not_drop_must_be_readied_on_primary_trigger", _weapon_do_not_drop_must_be_readied_on_primary_trigger_bit },
	{ "delete_on_drop", _weapon_delete_on_drop_bit },
	{ "allow_melee_when_using_device", _weapon_allow_melee_when_using_device_bit },
	{ "do_not_lower_weapon_when_using_device", _weapon_do_not_lower_weapon_when_using_device_bit },
	{ "cannot_fire_while_zooming", _weapon_cannot_fire_while_zooming_bit },
	{ "weapon_ages_when_damage_is_inflicted", _weapon_weapon_ages_when_damage_is_inflicted_bit },
	{ "apply_gunner_armor_mod_abilites", _weapon_apply_gunner_armor_mod_abilites_bit },
	{ "wielders_sprint_is_unaffected_by_soft_ping", _weapon_wielders_sprint_is_unaffected_by_soft_ping_bit },
	{ "weapon_drops_further_away", _weapon_weapon_drops_further_away_bit },
	{ "use_automatic_firing_looping_sounds", _weapon_use_automatic_firing_looping_sounds_bit },
	{ "do_not_drop_on_assassination", _weapon_do_not_drop_on_assassination_bit },
	{ "is_part_of_body", _weapon_is_part_of_body_bit },
	{ "suppresses_sprint", _weapon_suppresses_sprint_bit },
	{ "hide_pickup_prompt_unless_special_pickup_priority", _weapon_hide_pickup_prompt_unless_special_pickup_priority_bit },
	{ "weapon_ignores_player_pickup_allowed_trait", _weapon_weapon_ignores_player_pickup_allowed_trait_bit },
};

TAG_ENUM(
	weapon_secondary_trigger_mode_enum,
	k_number_of_weapon_secondary_trigger_modes)
{
	{ "normal", _weapon_secondary_trigger_mode_normal },
	{ "slaved_to_primary", _weapon_secondary_trigger_slaved_to_primary },
	{ "inhibits_primary", _weapon_secondary_trigger_inhibits_primary },
	{ "loads_alternate_ammunition", _weapon_secondary_trigger_loads_alternate_ammunition },
	{ "loads_multiple_primary_ammunition", _weapon_secondary_trigger_loads_multiple_primary_ammunition },
};

TAG_REFERENCE(
	weapon_damage_effect_reference,
	1)
{
	k_damage_effect_group_tag
};

TAG_REFERENCE(
	weapon_damage_response_reference,
	2)
{
	k_damage_response_group_tag
};

TAG_REFERENCE(
	weapon_damage_effect_or_response_reference,
	2)
{
	k_damage_effect_group_tag,
	k_damage_response_group_tag
};

TAG_REFERENCE(
	weapon_effect_reference,
	1)
{
	k_effect_group_tag
};

TAG_BLOCK(
	melee_damage_parameters_block,
	sizeof(s_melee_damage_parameters),
	k_maximum_number_of_weapon_melee_damage_parameters)
{
	{ _field_real_euler_angles2d, "damage_pyramid_angles" },
	{ _field_real, "damage_pyramid_depth" },
	{ _field_real, "maximum_lunge_range" },
	{ _field_real, "damage_lunge_explosive_depth" },
	{ _field_real, "runtime_damage_lunge_explosive_fraction" },
	{ _field_tag_reference, "melee_damage", &weapon_damage_effect_reference },
	{ _field_tag_reference, "melee_response", &weapon_damage_effect_or_response_reference },
	{ _field_tag_reference, "lunge_melee_damage", &weapon_damage_effect_reference },
	{ _field_tag_reference, "lunge_melee_response", &weapon_damage_effect_or_response_reference },
	{ _field_tag_reference, "empty_melee_damage", &weapon_damage_effect_reference },
	{ _field_tag_reference, "empty_melee_response", &weapon_damage_effect_or_response_reference },
	{ _field_tag_reference, "clang_melee_damage", &weapon_damage_effect_reference },
	{ _field_tag_reference, "clang_melee_response", &weapon_damage_effect_or_response_reference },
	{ _field_tag_reference, "clang_melee_against_melee_damage", &weapon_damage_effect_reference },
	{ _field_tag_reference, "clang_melee_against_melee_response", &weapon_damage_effect_or_response_reference },
	{ _field_tag_reference, "lunge_melee_explosive_damage", &weapon_effect_reference },
	{ _field_terminator }
};

TAG_STRUCT(
	aim_assist_parameters_struct,
	sizeof(s_aim_assist_parameters))
{
	{ _field_angle, "autoaim_angle" },
	{ _field_real, "autoaim_range" },
	{ _field_real, "autoaim_falloff_range" },
	{ _field_real, "autoaim_near_falloff_range" },
	{ _field_angle, "magnetism_angle" },
	{ _field_real, "magnetism_range" },
	{ _field_real, "magnetism_falloff_range" },
	{ _field_real, "magnetism_near_falloff_range" },
	{ _field_angle, "deviation_angle" },
	{ _field_real, "unknown1" },
	{ _field_real, "unknown2" },
	{ _field_real, "unknown3" },
	{ _field_real, "unknown4" },
	{ _field_real, "unknown5" },
	{ _field_real, "unknown6" },
	{ _field_terminator }
};

TAG_BLOCK(
	tracking_type_block,
	sizeof(s_tracking_type),
	k_maximum_number_of_weapon_tracking_types)
{
	{ _field_string_id, "tracking_type" },
	{ _field_terminator }
};

TAG_REFERENCE(
	weapon_sound_or_sound_looping_reference,
	2)
{
	k_sound_group_tag,
	k_sound_looping_group_tag
};

TAG_BLOCK(
	target_tracking_parameters_block,
	sizeof(s_target_tracking_parameters),
	k_maximum_number_of_weapon_target_tracking_parameters)
{
	{ _field_block, "tracking_types", &tracking_type_block },
	{ _field_real, "acquire_time" },
	{ _field_real, "grace_time" },
	{ _field_real, "decay_time" },
	{ _field_tag_reference, "tracking_sound", &weapon_sound_or_sound_looping_reference },
	{ _field_tag_reference, "locked_sound", &weapon_sound_or_sound_looping_reference },
	{ _field_terminator }
};

TAG_ENUM(
	weapon_movement_penalty_enum,
	k_number_of_weapon_movement_penalties)
{
	{ "always", _weapon_movement_penalized_always },
	{ "when_zoomed", _weapon_movement_penalized_when_zoomed },
	{ "when_zoomed_or_reloading", _weapon_movement_penalized_when_zoomed_or_reloading },
};

TAG_ENUM(
	weapon_type_enum,
	k_number_of_weapon_types)
{
	{ "undefined", _weapon_type_undefined },
	{ "shotgun", _weapon_type_shotgun },
	{ "needler", _weapon_type_needler },
	{ "plasma_pistol", _weapon_type_plasma_pistol },
	{ "plasma_rifle", _weapon_type_plasma_rifle },
	{ "rocket_launcher", _weapon_type_rocket_launcher },
	{ "energy_blade", _weapon_type_energy_blade },
	{ "splaser", _weapon_type_splaser },
	{ "shield", _weapon_type_shield },
	{ "scarab_gun", _weapon_type_scarab_gun },
	{ "wolverine_quad", _weapon_type_wolverine_quad },
	{ "flak_cannon", _weapon_type_flak_cannon },
	{ "plasma_launcher", _weapon_type_plasma_launcher },
};

TAG_REFERENCE(
	weapon_render_model_reference,
	1)
{
	k_render_model_group_tag
};

TAG_REFERENCE(
	weapon_model_animation_graph_reference,
	1)
{
	k_model_animation_graph_group_tag
};

TAG_BLOCK(
	weapon_first_person_interface_block,
	sizeof(s_weapon_first_person_interface),
	k_maximum_number_of_weapon_first_person_interfaces)
{
	{ _field_tag_reference, "first_person_model", &weapon_render_model_reference },
	{ _field_tag_reference, "first_person_animation", &weapon_model_animation_graph_reference },
	{ _field_terminator }
};

TAG_BLOCK(
	weapon_predicted_resources_block,
	sizeof(s_weapon_predicted_resources),
	k_maximum_number_of_weapon_predicted_resources)
{
	{ _field_short_integer, "type" },
	{ _field_short_integer, "resource_index" },
	{ _field_long_integer, "definition_index" },
	{ _field_terminator }
};

TAG_ENUM(
	weapon_magazine_flags_enum,
	k_number_of_weapon_magazine_flags)
{
	{ "wastes_rounds_when_reloaded", _weapon_magazine_wastes_rounds_when_reloaded_bit },
	{ "every_round_must_be_chambered", _weapon_magazine_every_round_must_be_chambered_bit },
	{ "magazine_cannot_change_state_while_firing", _weapon_magazine_magazine_cannot_change_state_while_firing_bit },
	{ "allow_overheated_reload_when_empty", _weapon_magazine_allow_overheated_reload_when_empty_bit },
	{ "bottomless_inventory", _weapon_magazine_bottomless_inventory_bit },
};

TAG_ENUM(
	weapon_magazine_ammo_refill_type_enum,
	k_number_of_weapon_magazine_refill_types)
{
	{ "none", _weapon_magazine_ammo_refill_none },
	{ "unsc", _weapon_magazine_ammo_refill_unsc },
	{ "covenant", _weapon_magazine_ammo_refill_covenant },
	{ "forerunner", _weapon_magazine_ammo_refill_forerunner },
};

TAG_PAD(
	_field_short_integer,
	weapon_magazine_post_rounds_reloaded_pad,
	1);

TAG_REFERENCE(
	weapon_sound_or_effect_reference,
	2)
{
	k_sound_group_tag,
		k_effect_group_tag
};

TAG_PAD(
	_field_short_integer,
	weapon_magazine_object_post_rounds_pad,
	1);

TAG_REFERENCE(
	weapon_equipment_reference,
	1)
{
	k_equipment_group_tag
};

TAG_BLOCK(
	weapon_magazine_object_block,
	sizeof(s_weapon_magazine_object),
	k_maximum_number_of_weapon_magazine_objects)
{
	{ _field_short_integer, "rounds" },
	{ _field_pad, "", &weapon_magazine_object_post_rounds_pad },
	{ _field_tag_reference, "equipment", &weapon_equipment_reference },
	{ _field_terminator }
};

TAG_BLOCK(
	weapon_magazine_definition_block,
	sizeof(s_weapon_magazine_definition),
	k_maximum_number_of_weapon_magazines)
{
	{ _field_long_flags, "flags", &weapon_magazine_flags_enum },
	{ _field_short_integer, "rounds_recharged" },
	{ _field_short_integer, "rounds_total_initial" },
	{ _field_short_integer, "rounds_total_maximum" },
	{ _field_short_integer, "rounds_loaded_maximum" },
	{ _field_short_integer, "runtime_rounds_inventory_maximum" },
	{ _field_short_enum, "ammo_refill_type", &weapon_magazine_ammo_refill_type_enum },
	{ _field_real, "reload_dialogue_time" },
	{ _field_short_integer, "rounds_reloaded" },
	{ _field_pad, "", &weapon_magazine_post_rounds_reloaded_pad },
	{ _field_real, "chamber_time" },
	{ _field_real, "unknown1" },
	{ _field_real, "unknown2" },
	{ _field_real, "unknown3" },
	{ _field_real, "unknown4" },
	{ _field_real, "unknown5" },
	{ _field_real, "unknown6" },
	{ _field_tag_reference, "reloading_effect", &weapon_sound_or_effect_reference },
	{ _field_tag_reference, "reloading_damage_effect", &weapon_sound_or_effect_reference },
	{ _field_tag_reference, "chambering_effect", &weapon_sound_or_effect_reference },
	{ _field_tag_reference, "chambering_damage_effect", &weapon_sound_or_effect_reference },
	{ _field_block, "magazines", &weapon_magazine_object_block },
	{ _field_terminator }
};

TAG_ENUM(
	weapon_trigger_definition_flags_enum,
	k_number_of_weapon_trigger_definition_flags)
{
	{ "autofire_single_action_only", _weapon_trigger_autofire_single_action_only_bit },
};

TAG_ENUM(
	weapon_trigger_input_enum,
	k_number_of_weapon_trigger_inputs)
{
	{ "right_trigger", _weapon_trigger_input_right_trigger },
	{ "left_trigger", _weapon_trigger_input_left_trigger },
	{ "melee_attack", _weapon_trigger_input_melee_attack },
	{ "automated_fire", _weapon_trigger_input_automated_fire },
	{ "right_bumper", _weapon_trigger_input_right_bumper },
};

TAG_ENUM(
	weapon_trigger_behavior_enum,
	k_number_of_weapon_trigger_behaviors)
{
	{ "spew", _weapon_trigger_behavior_spew },
	{ "latch", _weapon_trigger_behavior_latch },
	{ "latch_autofire", _weapon_trigger_behavior_latch_autofire },
	{ "latch_tether", _weapon_trigger_behavior_latch_tether },
	{ "charge", _weapon_trigger_behavior_charge },
	{ "latch_zoom", _weapon_trigger_behavior_latch_zoom },
	{ "spew_charge", _weapon_trigger_behavior_spew_charge },
	{ "sword_charge", _weapon_trigger_behavior_sword_charge },
	{ "double_latch_tether", _weapon_trigger_behavior_double_latch_tether },
	{ "charge_with_magazine", _weapon_trigger_behavior_charge_with_magazine },
};

TAG_ENUM(
	weapon_trigger_prediction_enum,
	k_number_of_weapon_trigger_predictions)
{
	{ "none", _weapon_trigger_prediction_none },
	{ "spew", _weapon_trigger_prediction_spew },
	{ "charge", _weapon_trigger_prediction_charge },
};

TAG_ENUM(
	weapon_trigger_autofire_action_enum,
	k_number_of_weapon_trigger_autofire_actions)
{
	{ "fire", _weapon_trigger_autofire_action_fire },
	{ "charge", _weapon_trigger_autofire_action_charge },
	{ "track", _weapon_trigger_autofire_action_track },
	{ "fire_other", _weapon_trigger_autofire_action_fire_other },
};

TAG_STRUCT(
	weapon_trigger_autofire_parameters_struct,
	sizeof(s_weapon_trigger_autofire_parameters))
{
	{ _field_real, "autofire_time" },
	{ _field_real, "autofire_throw" },
	{ _field_short_enum, "secondary_action", &weapon_trigger_autofire_action_enum },
	{ _field_short_enum, "primary_action", &weapon_trigger_autofire_action_enum },
	{ _field_terminator }
};

TAG_ENUM(
	weapon_trigger_overcharged_action_enum,
	k_number_of_weapon_trigger_overcharged_actions)
{
	{ "none", _weapon_trigger_overcharged_action_none },
	{ "explode", _weapon_trigger_overcharged_action_explode },
	{ "discharge", _weapon_trigger_overcharged_action_discharge },
};

TAG_ENUM(
	weapon_trigger_charge_projectiles_enum,
	k_number_of_weapon_trigger_charge_projectiles)
{
	{ "default", _weapon_trigger_charge_projectiles_default },
	{ "one_for_every_charge_level", _weapon_trigger_charge_projectiles_one_for_every_charge_level },
};

TAG_ENUM(
	weapon_trigger_charging_flags_enum,
	k_number_of_weapon_trigger_charging_flags)
{
	{ "can_fire_from_partial_charge", _weapon_trigger_can_fire_from_partial_charge_bit },
	{ "unknown1", _weapon_trigger_charging_unknown1_bit },
	{ "unknown2", _weapon_trigger_charging_unknown2_bit },
	{ "unknown3", _weapon_trigger_charging_unknown3_bit },
	{ "disallow_fire_from_partial_charge", _weapon_trigger_disallow_fire_from_partial_charge_bit },
};

TAG_BLOCK(
	weapon_trigger_charging_fire_fraction_block,
	sizeof(s_weapon_trigger_charging_fire_fraction),
	k_maximum_number_of_weapon_trigger_charging_fire_fractions)
{
	{ _field_real_fraction, "charge_fraction" },
	{ _field_terminator }
};

TAG_STRUCT(
	weapon_trigger_charging_parameters_struct,
	sizeof(s_weapon_trigger_charging_parameters))
{
	{ _field_real, "charging_time" },
	{ _field_real, "charged_time" },
	{ _field_char_enum, "overcharged_action", &weapon_trigger_overcharged_action_enum },
	{ _field_char_enum, "charge_projectiles", &weapon_trigger_charge_projectiles_enum },
	{ _field_word_flags, "flags", &weapon_trigger_charging_flags_enum },
	{ _field_real, "charged_illumination" },
	{ _field_tag_reference, "charging_effect", &weapon_sound_or_effect_reference },
	{ _field_tag_reference, "charging_damage_effect", &weapon_damage_effect_or_response_reference },
	{ _field_tag_reference, "charging_continuous_damage_response", &weapon_damage_response_reference },
	{ _field_real, "charged_drain_rate" },
	{ _field_tag_reference, "discharge_effect", &weapon_sound_or_effect_reference },
	{ _field_tag_reference, "discharge_damage_effect", &weapon_damage_effect_or_response_reference },
	{ _field_block, "fire_fractions", &weapon_trigger_charging_fire_fraction_block },
	{ _field_terminator }
};

extern s_tag_block_definition weapon_barrel_definition_block;

TAG_PAD(
	_field_short_integer,
	weapon_trigger_definition_post_prediction_pad,
	1);

TAG_BLOCK(
	weapon_trigger_definition_block,
	sizeof(s_weapon_trigger_definition),
	k_maximum_number_of_weapon_triggers)
{
	{ _field_long_flags, "flags", &weapon_trigger_definition_flags_enum },
	{ _field_short_enum, "input", &weapon_trigger_input_enum },
	{ _field_short_enum, "behavior", &weapon_trigger_behavior_enum },
	{ _field_short_block_index, "primary_barrel", &weapon_barrel_definition_block },
	{ _field_short_block_index, "secondary_barrel", &weapon_barrel_definition_block },
	{ _field_short_enum, "prediction", &weapon_trigger_prediction_enum },
	{ _field_pad, "", &weapon_trigger_definition_post_prediction_pad },
	{ _field_struct, "autofire", &weapon_trigger_autofire_parameters_struct },
	{ _field_struct, "charging", &weapon_trigger_charging_parameters_struct },
	{ _field_terminator }
};

TAG_ENUM(
	weapon_barrel_definition_flags_enum,
	k_number_of_weapon_barrel_definition_flags)
{
	{ "tracks_fired_projectile", _weapon_barrel_tracks_fired_projectile_bit },
	{ "random_firing_effects", _weapon_barrel_random_firing_effects_bit },
	{ "can_fire_with_partial_ammo", _weapon_barrel_can_fire_with_partial_ammo_bit },
	{ "projectiles_use_weapon_origin", _weapon_barrel_projectiles_use_weapon_origin_bit },
	{ "ejects_during_chamber", _weapon_barrel_ejects_during_chamber_bit },
	{ "use_error_when_unzoomed", _weapon_barrel_use_error_when_unzoomed_bit },
	{ "projectile_vector_cannot_be_adjusted", _weapon_barrel_projectile_vector_cannot_be_adjusted_bit },
	{ "projectiles_have_identical_error", _weapon_barrel_projectiles_have_identical_error_bit },
	{ "projectiles_fire_parallel", _weapon_barrel_projectiles_fire_parallel_bit },
	{ "cant_fire_when_others_firing", _weapon_barrel_cant_fire_when_others_firing_bit },
	{ "cant_fire_when_others_recovering", _weapon_barrel_cant_fire_when_others_recovering_bit },
	{ "dont_clear_fire_bit_after_recovering", _weapon_barrel_dont_clear_fire_bit_after_recovering_bit },
	{ "stagger_fire_across_multiple_markers", _weapon_barrel_stagger_fire_across_multiple_markers_bit },
	{ "can_fire_at_maximum_age", _weapon_barrel_can_fire_at_maximum_age_bit },
	{ "use_1_firing_effect_per_burst", _weapon_barrel_use_1_firing_effect_per_burst_bit },
	{ "prevent_marker_deviation", _weapon_barrel_prevent_marker_deviation_bit },
	{ "error_ignores_zoom", _weapon_barrel_error_ignores_zoom_bit },
	{ "projectile_fires_in_marker_direction", _weapon_barrel_projectile_fires_in_marker_direction_bit },
	{ "skip_test_for_object_being_outside_bsp", _weapon_barrel_skip_test_for_object_being_outside_bsp_bit },
	{ "only_reload_if_all_barrels_idle", _weapon_barrel_only_reload_if_all_barrels_idle_bit },
	{ "only_switch_weapons_if_barrel_idle", _weapon_barrel_only_switch_weapons_if_barrel_idle_bit },
	{ "use_automatic_fire_looping_sounds", _weapon_barrel_use_automatic_fire_looping_sounds_bit },
};

TAG_STRUCT(
	weapon_barrel_firing_parameters_struct,
	sizeof(s_weapon_barrel_firing_parameters))
{
	{ _field_real_bounds, "rounds_per_second" },
	{ _field_string_id, "rate_of_fire_acceleration" },
	{ _field_real, "acceleration_time" },
	{ _field_string_id, "rate_of_fire_deceleration" },
	{ _field_real, "deceleration_time" },
	{ _field_real, "barrel_spin_scale" },
	{ _field_real_fraction, "blurred_rate_of_fire" },
	{ _field_short_bounds, "shots_per_fire" },
	{ _field_real, "fire_recovery_time" },
	{ _field_real_fraction, "soft_recovery_fraction" },
	{ _field_real, "melee_fire_recovery_time" },
	{ _field_real_fraction, "melee_soft_recovery_fraction" },
	{ _field_terminator }
};

TAG_ENUM(
	weapon_barrel_prediction_type_enum,
	k_number_of_weapon_barrel_prediction_types)
{
	{ "none", _weapon_barrel_prediction_none },
	{ "continuous", _weapon_barrel_prediction_continuous },
	{ "instant", _weapon_barrel_prediction_instant },
	{ "continuous_burst", _weapon_barrel_prediction_continuous_burst },
};

TAG_ENUM(
	weapon_barrel_projectile_distribution_function_enum,
	k_number_of_weapon_barrel_projectile_distribution_functions)
{
	{ "point", _weapon_barrel_projectile_distribution_point },
	{ "horizontal_fan", _weapon_barrel_projectile_distribution_horizontal_fan },
};

TAG_STRUCT(
	weapon_barrel_projectile_distribution_struct,
	sizeof(s_weapon_barrel_projectile_distribution))
{
	{ _field_short_enum, "distribution_function", &weapon_barrel_projectile_distribution_function_enum },
	{ _field_short_integer, "projectiles_per_shot" },
	{ _field_angle, "distribution_angle" },
	{ _field_terminator }
};

TAG_STRUCT(
	weapon_barrel_projectile_error_parameters_struct,
	sizeof(s_weapon_barrel_projectile_error_parameters))
{
	{ _field_angle, "minimum_error" },
	{ _field_angle_bounds, "error_angle" },
	{ _field_terminator }
};

extern s_struct_definition tag_function_struct;

TAG_BLOCK(
	weapon_barrel_accuracy_penalty_function_block,
	sizeof(s_tag_function),
	NONE)
{
	{ _field_struct, "function", &tag_function_struct },
	{ _field_terminator }
};

TAG_STRUCT(
	weapon_barrel_wield_accuracy_penalties_struct,
	sizeof(s_weapon_barrel_wield_accuracy_penalties))
{
	{ _field_block, "firing_penalty_function", &weapon_barrel_accuracy_penalty_function_block },
	{ _field_block, "firing_crouched_penalty_function", &weapon_barrel_accuracy_penalty_function_block },
	{ _field_block, "moving_penalty_function", &weapon_barrel_accuracy_penalty_function_block },
	{ _field_block, "turning_penalty_function", &weapon_barrel_accuracy_penalty_function_block },
	{ _field_real, "error_angle_max_rotation" },
	{ _field_terminator }
};

TAG_STRUCT(
	weapon_barrel_accuracy_penalties_struct,
	sizeof(s_weapon_barrel_accuracy_penalties))
{
	{ _field_real, "reload_penalty" },
	{ _field_real, "switch_penalty" },
	{ _field_real, "zoom_penalty" },
	{ _field_real, "jump_penalty" },
	{ _field_struct, "single_wield_penalties", &weapon_barrel_wield_accuracy_penalties_struct },
	{ _field_struct, "dual_wield_penalties", &weapon_barrel_wield_accuracy_penalties_struct },
	{ _field_terminator }
};

TAG_BLOCK(
	weapon_barrel_first_person_offset_block,
	sizeof(s_weapon_barrel_first_person_offset),
	k_maximum_number_of_weapon_barrel_first_person_offsets)
{
	{ _field_real_point3d, "first_person_offset" },
	{ _field_terminator }
};

TAG_BLOCK(
	weapon_barrel_firing_effect_block,
	sizeof(s_weapon_barrel_firing_effect),
	k_maximum_number_of_weapon_barrel_firing_effects)
{
	{ _field_short_bounds, "shot_count_range" },
	{ _field_tag_reference, "firing_effect", &weapon_sound_or_effect_reference },
	{ _field_tag_reference, "misfire_effect", &weapon_sound_or_effect_reference },
	{ _field_tag_reference, "empty_effect", &weapon_sound_or_effect_reference },
	{ _field_tag_reference, "optional_secondary_firing_effect", &weapon_sound_or_effect_reference },
	{ _field_tag_reference, "firing_damage", &weapon_damage_effect_or_response_reference },
	{ _field_tag_reference, "misfire_damage", &weapon_damage_effect_or_response_reference },
	{ _field_tag_reference, "empty_damage", &weapon_damage_effect_or_response_reference },
	{ _field_tag_reference, "optional_secondary_firing_damage", &weapon_damage_effect_or_response_reference },
	{ _field_tag_reference, "firing_rider_damage", &weapon_damage_effect_or_response_reference },
	{ _field_tag_reference, "misfire_rider_damage", &weapon_damage_effect_or_response_reference },
	{ _field_tag_reference, "empty_rider_damage", &weapon_damage_effect_or_response_reference },
	{ _field_tag_reference, "optional_secondary_firing_rider_damage", &weapon_damage_effect_or_response_reference },
	{ _field_terminator }
};

extern s_enum_definition ai_sound_volume_enum;
extern s_enum_definition damage_reporting_type_enum;

TAG_PAD(
	_field_char_integer,
	weapon_barrel_definition_post_damage_reporting_type_pad,
	3);

TAG_REFERENCE(
	weapon_projectile_reference,
	1)
{
	k_projectile_group_tag
};

TAG_REFERENCE(
	weapon_crate_reference,
	1)
{
	k_crate_group_tag
};

TAG_BLOCK(
	weapon_barrel_definition_block,
	sizeof(s_weapon_barrel_definition),
	k_maximum_number_of_weapon_barrels)
{
	{ _field_long_flags, "flags", &weapon_barrel_definition_flags_enum },
	{ _field_struct, "firing", &weapon_barrel_firing_parameters_struct },
	{ _field_short_block_index, "magazine", &weapon_magazine_definition_block },
	{ _field_short_integer, "rounds_per_shot" },
	{ _field_short_integer, "minimum_rounds_loaded" },
	{ _field_short_integer, "rounds_between_tracers" },
	{ _field_string_id, "optional_barrel_marker_name" },
	{ _field_short_enum, "prediction_type", &weapon_barrel_prediction_type_enum },
	{ _field_short_enum, "firing_noise", &ai_sound_volume_enum },
	{ _field_real, "unknown" },
	{ _field_real, "acceleration_time" },
	{ _field_real, "deceleration_time" },
	{ _field_real_bounds, "damage_error_bounds" },
	{ _field_angle, "min_error_look_pitch_rate" },
	{ _field_angle, "full_error_look_pitch_rate" },
	{ _field_real, "look_pitch_error_power" },
	{ _field_struct, "projectile_distribution", &weapon_barrel_projectile_distribution_struct },
	{ _field_struct, "projectile_error", &weapon_barrel_projectile_error_parameters_struct },
	{ _field_struct, "accuracy_penalties", &weapon_barrel_accuracy_penalties_struct },
	{ _field_block, "first_person_offset", &weapon_barrel_first_person_offset_block },
	{ _field_char_enum, "projectile_damage_reporting_type", &damage_reporting_type_enum },
	{ _field_pad, "", &weapon_barrel_definition_post_damage_reporting_type_pad },
	{ _field_tag_reference, "projectile", &weapon_projectile_reference },
	{ _field_tag_reference, "optional_secondary_projectile", &weapon_projectile_reference },
	{ _field_tag_reference, "damage_effect", &weapon_damage_effect_reference },
	{ _field_tag_reference, "crate_projectile", &weapon_crate_reference },
	{ _field_real, "crate_projectile_speed" },
	{ _field_real, "ejection_port_recovery_time" },
	{ _field_real, "illumination_recovery_time" },
	{ _field_real, "heat_generated_per_round" },
	{ _field_string_id, "heat_generated_per_round_function" },
	{ _field_real, "age_generated_per_round" },
	{ _field_real, "campaign_age_generated_per_round" },
	{ _field_real, "overload_time" },
	{ _field_real, "runtime_illumination_recovery_rate" },
	{ _field_real, "runtime_ejection_port_recovery_rate" },
	{ _field_real, "rate_of_fire_acceleration_time" },
	{ _field_real, "rate_of_fire_deceleration_time" },
	{ _field_real, "bloom_rate_of_decay" },
	{ _field_block, "firing_effects", &weapon_barrel_firing_effect_block },
	{ _field_terminator }
};

TAG_ENUM(
	weapon_screen_effect_flags_enum,
	k_number_of_weapon_screen_effect_flags)
{
	{ "overrides_unit_and_camera_screen_effects", _weapon_screen_effect_overrides_unit_and_camera_screen_effects_bit },
	{ "unzoomed", _weapon_screen_effect_unzoomed_bit },
	{ "zoom_level1", _weapon_screen_effect_zoom_level1_bit },
	{ "zoom_level2", _weapon_screen_effect_zoom_level2_bit },
};

TAG_PAD(
	_field_char_integer,
	weapon_screen_effect_post_flags_padding,
	3);

TAG_REFERENCE(
	weapon_area_screen_effect_reference,
	1)
{
	k_area_screen_effect_group_tag
};

TAG_BLOCK(
	weapon_screen_effect_block,
	sizeof(s_weapon_screen_effect),
	k_maximum_number_of_weapon_screen_effects)
{
	{ _field_byte_flags, "flags", &weapon_screen_effect_flags_enum },
	{ _field_pad, "", &weapon_screen_effect_post_flags_padding },
	{ _field_tag_reference, "screen_effect", &weapon_area_screen_effect_reference },
	{ _field_terminator }
};

extern s_tag_group item_group;

TAG_PAD(
	_field_char_integer,
	weapon_definition_post_melee_damage_reporting_type_pad,
	1);

TAG_PAD(
	_field_short_integer,
	weapon_definition_post_movement_penalized_pad,
	1);

TAG_REFERENCE(
	weapon_chud_definition_reference,
	1)
{
	k_chud_definition_group_tag
};

TAG_REFERENCE(
	weapon_vehicle_reference,
	1)
{
	k_vehicle_group_tag
};

TAG_REFERENCE(
	weapon_definition_reference,
	1)
{
	k_weapon_group_tag
};

TAG_REFERENCE(
	weapon_material_effects_reference,
	1)
{
	k_material_effects_group_tag
};

TAG_REFERENCE(
	weapon_sound_reference,
	1)
{
	k_sound_group_tag
};

TAG_GROUP(
	weapon_group,
	k_weapon_group_tag,
	sizeof(s_weapon_definition) - sizeof(s_item_definition),
	&item_group)
{
	{ _field_long_flags, "flags", &weapon_definition_flags_enum },
	{ _field_long_flags, "secondary_flags", &weapon_definition_secondary_flags_enum },
	{ _field_string_id, "unused_label" },
	{ _field_short_enum, "secondary_trigger_mode", &weapon_secondary_trigger_mode_enum },
	{ _field_short_integer, "maximum_alternate_shots_loaded" },
	{ _field_real, "turn_on_time" },
	{ _field_real, "ready_time" },
	{ _field_tag_reference, "ready_effect", &weapon_sound_or_effect_reference },
	{ _field_tag_reference, "ready_damage_effect", &weapon_damage_effect_or_response_reference },
	{ _field_real_fraction, "heat_recovery_threshold" },
	{ _field_real_fraction, "overheated_threshold" },
	{ _field_real_fraction, "heat_detonation_threshold" },
	{ _field_real_fraction, "heat_detonation_fraction" },
	{ _field_real, "heat_loss_per_second" },
	{ _field_string_id, "heat_loss" },
	{ _field_string_id, "heat_loss_venting" },
	{ _field_real, "heat_venting_time" },
	{ _field_real_fraction, "heat_venting_exit_heat" },
	{ _field_real_fraction, "heat_illumination" },
	{ _field_real_fraction, "heat_warning_threshold" },
	{ _field_real, "overheated_heat_loss_per_second" },
	{ _field_string_id, "overheated_heat_loss" },
	{ _field_tag_reference, "overheated", &weapon_sound_or_effect_reference },
	{ _field_tag_reference, "overheated_damage_effect", &weapon_damage_effect_or_response_reference },
	{ _field_tag_reference, "detonation", &weapon_sound_or_effect_reference },
	{ _field_tag_reference, "detonation_damage_effect", &weapon_damage_effect_or_response_reference },
	{ _field_block, "melee_damage_parameters", &melee_damage_parameters_block },
	{ _field_tag_reference, "clang_effect", &weapon_sound_or_effect_reference },
	{ _field_char_enum, "melee_damage_reporting_type", &damage_reporting_type_enum },
	{ _field_pad, "", &weapon_definition_post_melee_damage_reporting_type_pad },
	{ _field_short_integer, "magnification_levels" },
	{ _field_real_bounds, "magnification_range" },
	{ _field_struct, "aim_assist", &aim_assist_parameters_struct },
	{ _field_block, "target_tracking", &target_tracking_parameters_block },
	{ _field_real_bounds, "ballistic_arcing_firing_bounds" },
	{ _field_real_bounds, "ballistic_arcing_fraction_bounds" },
	{ _field_short_enum, "movement_penalized", &weapon_movement_penalty_enum },
	{ _field_pad, "", &weapon_definition_post_movement_penalized_pad },
	{ _field_real_fraction, "forward_movement_penalty" },
	{ _field_real_fraction, "sideways_movement_penalty" },
	{ _field_real, "ai_scariness" },
	{ _field_real, "weapon_power_on_time" },
	{ _field_real, "weapon_power_off_time" },
	{ _field_tag_reference, "weapon_power_on_effect", &weapon_sound_or_effect_reference },
	{ _field_tag_reference, "weapon_power_off_effect", &weapon_sound_or_effect_reference },
	{ _field_real, "age_heat_recovery_penalty" },
	{ _field_real, "age_rate_of_fire_penalty" },
	{ _field_real_fraction, "age_misfire_start" },
	{ _field_real_fraction, "age_misfire_chance" },
	{ _field_tag_reference, "pickup_sound", &weapon_sound_reference },
	{ _field_tag_reference, "zoom_in_sound", &weapon_sound_reference },
	{ _field_tag_reference, "zoom_out_sound", &weapon_sound_reference },
	{ _field_real, "active_camo_ding" },
	{ _field_string_id, "handle_node" },
	{ _field_string_id, "weapon_class" },
	{ _field_string_id, "weapon_name" },
	{ _field_short_enum, "weapon_type", &weapon_type_enum },
	{ _field_short_integer, "low_ammo_threshold" },
	{ _field_real, "unknown1" },
	{ _field_real, "unknown2" },
	{ _field_real, "unknown3" },
	{ _field_real, "unknown4" },
	{ _field_block, "first_person", &weapon_first_person_interface_block },
	{ _field_tag_reference, "hud_interface", &weapon_chud_definition_reference },
	{ _field_tag_reference, "alternate_hud_interface", &weapon_chud_definition_reference },
	{ _field_block, "predicted_resources", &weapon_predicted_resources_block },
	{ _field_block, "magazines", &weapon_magazine_definition_block },
	{ _field_block, "new_triggers", &weapon_trigger_definition_block },
	{ _field_block, "barrels", &weapon_barrel_definition_block },
	{ _field_real, "runtime_weapon_power_on_velocity" },
	{ _field_real, "runtime_weapon_power_off_velocity" },
	{ _field_real, "max_movement_acceleration" },
	{ _field_real, "max_movement_velocity" },
	{ _field_real, "max_turning_acceleration" },
	{ _field_real, "max_turning_velocity" },
	{ _field_tag_reference, "deployed_vehicle", &weapon_vehicle_reference },
	{ _field_tag_reference, "tossed_weapon", &weapon_definition_reference },
	{ _field_tag_reference, "age_effect", &weapon_effect_reference },
	{ _field_tag_reference, "aged_weapon", &weapon_definition_reference },
	{ _field_tag_reference, "aged_material_effects", &weapon_material_effects_reference },
	{ _field_real, "external_aging_amount" },
	{ _field_real, "campaign_external_aging_amount" },
	{ _field_real, "external_heat_amount" },
	{ _field_real_vector3d, "first_person_weapon_offset" },
	{ _field_real_vector2d, "first_person_scope_size" },
	{ _field_real_bounds, "support_third_person_camera_range" },
	{ _field_real, "weapon_zoom_time" },
	{ _field_real, "weapon_ready_for_use_time" },
	{ _field_string_id, "unit_stow_anchor_name" },
	{ _field_block, "screen_effects", &weapon_screen_effect_block },
	{ _field_terminator }
};
