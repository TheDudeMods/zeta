
#include <effects/effects.h>
#include <items/projectile_definitions.h>
#include <objects/damage.h>
#include <objects/damage_new.h>
#include <physics/grounded_friction.h>
#include <sound/sound_definitions.h>

extern s_tag_group_definition object_group;
extern s_enum_definition damage_reporting_type_enum;
extern s_enum_definition object_type_enum;
extern s_enum_definition ai_sound_volume_enum;

/* ---------- definitions */

TAG_ENUM(
	projectile_flags_enum,
	k_number_of_projectile_flags)
{
	{ "oriented_along_velocity", _projectile_oriented_along_velocity_bit },
	{ "ai_must_use_ballistic_aiming", _projectile_ai_must_use_ballistic_aiming_bit },
	{ "detonation_max_time_if_attached", _projectile_detonation_max_time_if_attached_bit },
	{ "damage_scales_based_on_distance", _projectile_damage_scales_based_on_distance_bit },
	{ "steering_adjusts_orientation", _projectile_steering_adjusts_orientation_bit },
	{ "dont_noise_up_steering", _projectile_dont_noise_up_steering_bit },
	{ "can_track_behind_itself", _projectile_can_track_behind_itself_bit },
	{ "robotron_steering", _projectile_robotron_steering_bit },
	{ "affected_by_phantom_volumes", _projectile_affected_by_phantom_volumes_bit },
	{ "notifies_target_units", _projectile_notifies_target_units_bit },
	{ "use_ground_detonation_when_attached", _projectile_use_ground_detonation_when_attached_bit },
	{ "ai_minor_tracking_threat", _projectile_ai_minor_tracking_threat_bit },
	{ "dangerous_when_inactive", _projectile_dangerous_when_inactive_bit },
	{ "ai_stimulus_when_attached", _projectile_ai_stimulus_when_attached_bit },
	{ "over_pene_detonation", _projectile_over_pene_detonation_bit },
	{ "no_impact_effects_on_bounce", _projectile_no_impact_effects_on_bounce_bit },
	{ "rc1_overpenetration_fixes", _projectile_rc1_overpenetration_fixes_bit },
	{ "disable_instantaneous_first_tick", _projectile_disable_instantaneous_first_tick_bit },
	{ "constrain_gravity_to_velocity_bounds", _projectile_constrain_gravity_to_velocity_bounds_bit },
	{ "allow_deceleration_below_final_velocity", _projectile_allow_deceleration_below_final_velocity_bit },
	{ "supports_tethering", _projectile_supports_tethering_bit },
	{ "damage_not_predictable_by_clients", _projectile_damage_not_predictable_by_clients_bit },
	{ "collides_with_physics_only_surfaces", _projectile_collides_with_physics_only_surfaces_bit },
	{ "detonates_when_attached_to_objects", _projectile_detonates_when_attached_to_objects_bit },
	{ "cannot_be_detached_by_equipment", _projectile_cannot_be_detached_by_equipment_bit },
	{ "does_not_collide_with_world_geometry", _projectile_does_not_collide_with_world_geometry_bit },
	{ "is_collectible", _projectile_is_collectible_bit },
	{ "different_bursts_will_not_trigger_super_combine_detonation", _projectile_different_bursts_will_not_trigger_super_combine_detonation_bit },
	{ "distance_based_damage_scaling_uses_damage_range_low_bounds", _projectile_distance_based_damage_scaling_uses_damage_range_low_bounds_bit },
	{ "skip_object_first_tick", _projectile_skip_object_first_tick_bit },
	{ "use_projectile_camera_in_killcam", _projectile_use_projectile_camera_in_killcam_bit },
	{ "detonates_on_attachment_to_equipped_weapon", _projectile_detonates_on_attachment_to_equipped_weapon_bit },
};

TAG_ENUM(
	projectile_detonation_timer_start_enum,
	k_number_of_projectile_detonation_timer_starts)
{
	{ "immediately", _projectile_detonation_timer_start_immediately },
	{ "after_first_bounce", _projectile_detonation_timer_start_after_first_bounce },
	{ "when_at_rest", _projectile_detonation_timer_start_when_at_rest },
	{ "after_first_bounce_off_any_surface", _projectile_detonation_timer_start_after_first_bounce_off_any_surface },
};

TAG_REFERENCE(
	projectile_effect_reference,
	1)
{
	k_effect_group_tag
};

TAG_REFERENCE(
	projectile_damage_effect_reference,
	1)
{
	k_damage_effect_group_tag
};

TAG_REFERENCE(
	projectile_sound_reference,
	1)
{
	k_sound_group_tag
};

TAG_PADDING(
	_field_char_integer,
	projectile_post_damage_porting_type_padding,
	1);

TAG_REFERENCE(
	projectile_damage_response_reference,
	1)
{
	k_damage_response_group_tag
};

TAG_REFERENCE(
	projectile_grounded_friction_reference,
	1)
{
	k_grounded_friction_group_tag
};

TAG_ENUM(
	projectile_material_response_type_enum,
	k_number_of_projectile_material_response_types)
{
	{ "impact_detonate", _projectile_material_response_type_impact_detonate },
	{ "fizzle", _projectile_material_response_type_fizzle },
	{ "overpenetrate", _projectile_material_response_type_overpenetrate },
	{ "attach", _projectile_material_response_type_attach },
	{ "bounce", _projectile_material_response_type_bounce },
	{ "bounce_dud", _projectile_material_response_type_bounce_dud },
	{ "fizzle_ricochet", _projectile_material_response_type_fizzle_ricochet },
	{ "turn_physical", _projectile_material_response_type_turn_physical },
	{ "airstrike", _projectile_material_response_type_airstrike },
};

TAG_ENUM(
	projectile_material_response_flags_enum,
	k_number_of_projectile_material_response_flags)
{
	{ "only_against_units", _projectile_material_response_only_against_units_bit },
	{ "never_against_units", _projectile_material_response_never_against_units_bit },
	{ "only_against_bipeds", _projectile_material_response_only_against_bipeds_bit },
	{ "only_against_vehicles", _projectile_material_response_only_against_vehicles_bit },
	{ "never_against_wuss_players", _projectile_material_response_never_against_wuss_players_bit },
	{ "only_when_tethered", _projectile_material_response_only_when_tethered_bit },
	{ "only_when_not_tethered", _projectile_material_response_only_when_not_tethered_bit },
	{ "only_against_dead_bipeds", _projectile_material_response_only_against_dead_bipeds_bit },
	{ "never_against_dead_bipeds", _projectile_material_response_never_against_dead_bipeds_bit },
	{ "only_ai_projectiles", _projectile_material_response_only_ai_projectiles_bit },
	{ "never_ai_projectiles", _projectile_material_response_never_ai_projectiles_bit },
};

TAG_ENUM(
	projectile_material_response_effect_scale_enum,
	k_number_of_projectile_material_response_effect_scales)
{
	{ "damage", _projectile_material_response_effect_scale_damage },
	{ "angle", _projectile_material_response_effect_scale_angle },
};

TAG_PADDING(
	_field_short_integer,
	projectile_material_response_old_post_default_response_padding,
	1);

TAG_PADDING(
	_field_short_integer,
	projectile_material_response_old_post_runtime_material_index_padding,
	1);

TAG_PADDING(
	_field_short_integer,
	projectile_material_response_old_post_scale_effects_by_padding,
	1);

TAG_BLOCK(
	projectile_material_response_old_block,
	sizeof(s_projectile_material_response_old),
	k_maximum_number_of_projectile_material_responses)
{
	{ _field_short_enum, "default_response", &projectile_material_response_type_enum },
	{ _field_padding, "post_default_response_padding", &projectile_material_response_old_post_default_response_padding },
	{ _field_string_id, "material_name" },
	{ _field_short_integer, "runtime_material_index" },
	{ _field_padding, "post_runtime_material_index_padding", &projectile_material_response_old_post_runtime_material_index_padding },
	{ _field_short_enum, "potential_response", &projectile_material_response_type_enum },
	{ _field_word_flags, "response_flags", &projectile_material_response_flags_enum },
	{ _field_real_fraction, "chance_fraction" },
	{ _field_angle_bounds, "between" },
	{ _field_real_bounds, "and" },
	{ _field_short_enum, "scale_effects_by", &projectile_material_response_effect_scale_enum },
	{ _field_padding, "post_scale_effects_by_padding", &projectile_material_response_old_post_scale_effects_by_padding },
	{ _field_angle, "angular_noise" },
	{ _field_real, "velocity_noise" },
	{ _field_real, "initial_friction" },
	{ _field_real, "parallel_friction" },
	{ _field_real, "perpendicular_friction" },
	{ _field_terminator }
};

TAG_BLOCK(
	projectile_material_response_block,
	sizeof(s_projectile_material_response),
	k_maximum_number_of_projectile_material_responses)
{
	{ _field_string_id, "material_name" },
	{ _field_short_integer, "runtime_material_index" },
	{ _field_word_flags, "response_flags", &projectile_material_response_flags_enum },
	{ _field_real_fraction, "chance_fraction" },
	{ _field_angle_bounds, "between" },
	{ _field_real_bounds, "and" },
	{ _field_short_enum, "response", &projectile_material_response_type_enum },
	{ _field_short_enum, "scale_effects_by", &projectile_material_response_effect_scale_enum },
	{ _field_angle, "angular_noise" },
	{ _field_real, "velocity_noise" },
	{ _field_real, "initial_friction" },
	{ _field_real, "parallel_friction" },
	{ _field_real, "perpendicular_friction" },
	{ _field_terminator }
};

TAG_BLOCK(
	projectile_brute_grenade_block,
	sizeof(s_projectile_brute_grenade),
	k_maximum_number_of_projectile_brute_grenades)
{
	{ _field_angle, "minimum_angular_velocity" },
	{ _field_angle, "maximum_angular_velocity" },
	{ _field_angle, "spin_angular_velocity" },
	{ _field_real, "angular_damping" },
	{ _field_real, "drag_angle_k" },
	{ _field_real, "drag_speed_k" },
	{ _field_real, "drag_exponent" },
	{ _field_real, "attach_sample_radius" },
	{ _field_real, "attach_acc_k" },
	{ _field_real, "attach_acc_s" },
	{ _field_real, "attach_acc_e" },
	{ _field_real, "attach_acc_damping" },
	{ _field_terminator }
};

TAG_BLOCK(
	projectile_fire_bomb_grenade_block,
	sizeof(s_projectile_fire_bomb_grenade),
	k_maximum_number_of_projectile_fire_bomb_grenades)
{
	{ _field_real, "projection_offset" },
	{ _field_terminator }
};

TAG_BLOCK(
	projectile_conical_spread_block,
	sizeof(s_projectile_conical_spread),
	k_maximum_number_of_projectile_conical_spreads)
{
	{ _field_short_integer, "yaw_count" },
	{ _field_short_integer, "pitch_count" },
	{ _field_real, "distribution_exponent" },
	{ _field_angle, "spread" },
	{ _field_terminator }
};

TAG_GROUP(
	projectile_group,
	k_projectile_group_tag,
	sizeof(s_projectile_definition) - sizeof(s_object_definition),
	&object_group)
{
	{ _field_long_flags, "projectile_flags", &projectile_flags_enum },
	{ _field_short_enum, "detonation_timer_starts", &projectile_detonation_timer_start_enum },
	{ _field_short_enum, "impact_noise", &ai_sound_volume_enum },
	{ _field_real, "collision_radius" },
	{ _field_real, "arming_time" },
	{ _field_real, "danger_radius" },
	{ _field_real, "danger_stimuli_radius" },
	{ _field_short_integer, "danger_group_burst_count" },
	{ _field_short_integer, "danger_group_burst_max_count" },
	{ _field_real_bounds, "timer" },
	{ _field_real, "minimum_velocity" },
	{ _field_real, "maximum_range" },
	{ _field_real, "bounce_maximum_range" },
	{ _field_real, "max_latch_time_to_detonate" },
	{ _field_real, "max_latch_time_to_arm" },
	{ _field_short_enum, "detonation_noise", &ai_sound_volume_enum },
	{ _field_short_integer, "super_detonation_projectile_count" },
	{ _field_real, "tether_release_safety_delay" },
	{ _field_tag_reference, "detonation_started", &projectile_effect_reference },
	{ _field_tag_reference, "detonation_effect_airborne", &projectile_effect_reference },
	{ _field_tag_reference, "detonation_effect_ground", &projectile_effect_reference },
	{ _field_tag_reference, "detonation_damage", &projectile_damage_effect_reference },
	{ _field_tag_reference, "attached_detonation_damage", &projectile_damage_effect_reference },
	{ _field_tag_reference, "super_detonation", &projectile_effect_reference },
	{ _field_tag_reference, "super_detonation_damage", &projectile_damage_effect_reference },
	{ _field_tag_reference, "detonation_sound", &projectile_sound_reference },
	{ _field_char_enum, "damage_reporting_type", &damage_reporting_type_enum },
	{ _field_padding, "post_damage_porting_type_padding", &projectile_post_damage_porting_type_padding },
	{ _field_word_flags, "super_detonation_object_types", &object_type_enum },
	{ _field_tag_reference, "super_attached_detonation_damage", &projectile_damage_effect_reference },
	{ _field_real, "material_effect_radius" },
	{ _field_tag_reference, "flyby_sound", &projectile_sound_reference },
	{ _field_tag_reference, "flyby_response", &projectile_damage_response_reference },
	{ _field_real, "flyby_effects_range" },
	{ _field_tag_reference, "impact_effect", &projectile_effect_reference },
	{ _field_tag_reference, "object_impact_effect", &projectile_effect_reference },
	{ _field_tag_reference, "impact_damage", &projectile_damage_effect_reference },
	{ _field_real, "boarding_detonation_time" },
	{ _field_tag_reference, "boarding_detonation_damage", &projectile_damage_effect_reference },
	{ _field_tag_reference, "boarding_attached_detonation_damage", &projectile_damage_effect_reference },
	{ _field_real, "air_gravity_scale" },
	{ _field_real_bounds, "air_damage_range" },
	{ _field_real, "water_gravity_scale" },
	{ _field_real_bounds, "water_damage_range" },
	{ _field_real, "initial_velocity" },
	{ _field_real, "final_velocity" },
	{ _field_real, "indirect_fire_velocity" },
	{ _field_real, "ai_velocity_scale_normal" },
	{ _field_real, "ai_velocity_scale_heroic" },
	{ _field_real, "ai_velocity_scale_legendary" },
	{ _field_real, "ai_guided_angular_velocity_scale_normal" },
	{ _field_real, "ai_guided_angular_velocity_scale_legendary" },
	{ _field_angle, "guided_angular_velocity_lower" },
	{ _field_angle, "guided_angular_velocity_upper" },
	{ _field_angle, "guided_angular_velocity_at_rest" },
	{ _field_real_bounds, "acceleration_range" },
	{ _field_real, "runtime_acceleration_bound_inverse" },
	{ _field_real_fraction, "ai_target_leading_scale" },
	{ _field_real_fraction, "targeted_leading_fraction" },
	{ _field_real, "guided_error_radius" },
	{ _field_block, "material_responses_old", &projectile_material_response_old_block },
	{ _field_block, "material_responses", &projectile_material_response_block },
	{ _field_block, "brute_grenade", &projectile_brute_grenade_block },
	{ _field_block, "fire_bomb_grenade", &projectile_fire_bomb_grenade_block },
	{ _field_block, "conical_spread", &projectile_conical_spread_block },
	{ _field_tag_reference, "grounded_friction_settings", &projectile_grounded_friction_reference },
	{ _field_terminator }
};
