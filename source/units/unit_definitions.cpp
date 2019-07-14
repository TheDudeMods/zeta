#include <ai/character_definitions.h>
#include <camera/camera_track.h>
#include <effects/effect_definitions.h>
#include <effects/screen_effect.h>
#include <interface/chud/chud_definitions.h>
#include <items/weapon_definitions.h>
#include <objects/damage.h>
#include <objects/damage_new.h>
#include <physics/havok_collision_damage.h>
#include <physics/spring_acceleration.h>
#include <sound/sound_definitions.h>
#include <units/unit_definitions.h>
#include <units/unit_dialogue.h>
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

TAG_REFERENCE(
    unit_screen_effect_reference,
    1)
{
    k_area_screen_effect_group_tag
};

TAG_BLOCK(
    unit_screen_effect_reference_block,
    sizeof(s_unit_screen_effect_reference),
    k_maximum_number_of_unit_screen_effect_references)
{
    { _field_tag_reference, "type", &unit_screen_effect_reference },
    { _field_terminator }
};

TAG_ENUM(
    unit_camera_flags_enum,
    k_number_of_unit_camera_flags)
{
    { "pitch_bounds_absolute_space", _unit_camera_pitch_bounds_absolute_space_bit },
    { "only_collides_with_environment", _unit_camera_only_collides_with_environment_bit },
    { "hides_player_unit_from_camera", _unit_camera_hides_player_unit_from_camera_bit },
    { "use_aiming_vector_instead_of_marker_forward", _unit_camera_use_aiming_vector_instead_of_marker_forward_bit },
};

TAG_PADDING(
    _field_short_integer,
    unit_camera_post_flags_padding,
    1);

TAG_REFERENCE(
    unit_camera_track_reference,
    1)
{
    k_camera_track_group_tag
};

TAG_BLOCK(
    unit_camera_track_reference_block,
    sizeof(s_unit_camera_track_reference),
    k_maximum_number_of_unit_camera_track_references)
{
    { _field_tag_reference, "track", &unit_camera_track_reference },
    { _field_tag_reference, "screen_effect", &unit_screen_effect_reference },
    { _field_terminator }
};

TAG_STRUCT(
    unit_camera_obstruction_struct,
    sizeof(s_unit_camera_obstruction))
{
    { _field_real_fraction, "cylinder_fraction" },
    { _field_angle, "obstruction_test_angle" },
    { _field_real, "obstruction_max_inward_accel" },
    { _field_real, "obstruction_max_outward_accel" },
    { _field_real, "obstruction_max_velocity" },
    { _field_real, "obstruction_return_delay" },
    { _field_terminator }
};

TAG_ENUM(
    unit_camera_acceleration_input_variable_enum,
    k_number_of_unit_camera_acceleration_input_variables)
{
    { "linear_velocity", _unit_camera_acceleration_input_variable_linear_velocity },
    { "linear_acceleration", _unit_camera_acceleration_input_variable_linear_acceleration },
    { "yaw", _unit_camera_acceleration_input_variable_yaw },
    { "pitch", _unit_camera_acceleration_input_variable_pitch },
    { "roll", _unit_camera_acceleration_input_variable_roll },
};

TAG_PADDING(
    _field_char_integer,
    unit_camera_acceleration_function_post_input_variable_padding,
    3);

TAG_STRUCT(
    unit_camera_acceleration_function_struct,
    sizeof(s_unit_camera_acceleration_function))
{
    { _field_char_enum, "input_variable", &unit_camera_acceleration_input_variable_enum },
    { _field_padding, "post_input_variable_padding", &unit_camera_acceleration_function_post_input_variable_padding },
    { _field_data, "data" },
    { _field_real, "maximum_value" },
    { _field_real, "camera_scale_axial" },
    { _field_real, "camera_scale_perpendicular" },
    { _field_terminator }
};

TAG_BLOCK(
    unit_camera_acceleration_displacement_block,
    sizeof(s_unit_camera_acceleration_displacement),
    k_maximum_number_of_unit_camera_acceleration_displacements)
{
    { _field_real, "maximum_camera_velocity" },
    { _field_struct, "forward_back", &unit_camera_acceleration_function_struct },
    { _field_struct, "left_right", &unit_camera_acceleration_function_struct },
    { _field_struct, "up_down", &unit_camera_acceleration_function_struct },
    { _field_terminator }
};

TAG_ENUM(
    unit_camera_gamepad_input_shape_enum,
    k_number_of_unit_camera_gamepad_input_shapes)
{
    { "none", _unit_camera_gamepad_input_shape_none },
    { "unit_circle", _unit_camera_gamepad_input_shape_unit_circle },
    { "unit_square", _unit_camera_gamepad_input_shape_unit_square },
};

TAG_PADDING(
    _field_char_integer,
    unit_camera_gamepad_stick_info_post_input_shape_padding,
    1);

TAG_BLOCK(
    unit_camera_gamepad_stick_function_block,
    sizeof(s_unit_camera_gamepad_stick_function),
    k_maximum_number_of_unit_camera_gamepad_stick_functions)
{
    { _field_data, "data" },
    { _field_terminator }
};

TAG_BLOCK(
    unit_camera_gamepad_stick_info_block,
    sizeof(s_unit_camera_gamepad_stick_info),
    k_maximum_number_of_unit_camera_gamepad_stick_overrides)
{
    { _field_char_enum, "input_shape", &unit_camera_gamepad_input_shape_enum },
    { _field_padding, "post_input_shape_padding", &unit_camera_gamepad_stick_info_post_input_shape_padding },
    { _field_real_fraction, "peg_threshold" },
    { _field_real_point2d, "pegged_time" },
    { _field_real_point2d, "pegged_scale" },
    { _field_angle, "peg_max_angular_velocity" },
    { _field_block, "input_mapping_function", &unit_camera_gamepad_stick_function_block },
    { _field_terminator }
};

TAG_STRUCT(
    unit_camera_struct,
    sizeof(s_unit_camera))
{
    { _field_word_flags, "flags", &unit_camera_flags_enum },
    { _field_padding, "post_flags_padding", &unit_camera_post_flags_padding },
    { _field_string_id, "camera_marker_name" },
    { _field_angle, "pitch_auto_level" },
    { _field_angle_bounds, "pitch_range" },
    { _field_block, "camera_tracks", &unit_camera_track_reference_block },
    { _field_angle, "pitch_minimum_spring" },
    { _field_angle, "pitch_maximum_spring" },
    { _field_angle, "spring_velocity" },
    { _field_angle, "look_acceleration" },
    { _field_angle, "look_deceleration" },
    { _field_real_fraction, "look_acceleration_smoothing_fraction" },
    { _field_angle, "override_fov" },
    { _field_struct, "camera_obstruction", &unit_camera_obstruction_struct },
    { _field_block, "camera_acceleration", &unit_camera_acceleration_displacement_block },
    { _field_block, "move_stick_overrides", &unit_camera_gamepad_stick_info_block },
    { _field_block, "look_stick_overrides", &unit_camera_gamepad_stick_info_block },
    { _field_terminator }
};

TAG_REFERENCE(
    unit_assassination_damage_response_reference,
    1)
{
    k_damage_response_group_tag
};

TAG_REFERENCE(
    unit_assassination_object_reference,
    1)
{
    k_object_group_tag
};

TAG_REFERENCE(
    unit_seat_acceleration_reference,
    1)
{
    k_spring_acceleration_group_tag
};

TAG_REFERENCE(
    unit_spawned_turret_character_reference,
    1)
{
    k_character_group_tag
};

TAG_REFERENCE(
    unit_damage_effect_reference,
    1)
{
    k_damage_effect_group_tag
};

TAG_ENUM(
    unit_motion_sensor_blip_size_enum,
    k_number_of_unit_motion_sensor_blip_sizes)
{
    { "medium", _unit_motion_sensor_blip_size_medium },
    { "small", _unit_motion_sensor_blip_size_small },
    { "large", _unit_motion_sensor_blip_size_large },
};

TAG_ENUM(
    unit_item_owner_size_enum,
    k_number_of_unit_item_owner_sizes)
{
    { "small", _unit_item_owner_size_small },
    { "medium", _unit_item_owner_size_medium },
    { "large", _unit_item_owner_size_large },
    { "huge", _unit_item_owner_size_huge },
};

TAG_BLOCK(
    unit_posture_block,
    sizeof(s_unit_posture),
    k_maximum_number_of_unit_postures)
{
    { _field_string_id, "name" },
    { _field_real_point3d, "pill_offset" },
    { _field_terminator }
};

TAG_REFERENCE(
    unit_hud_interface_reference,
    1)
{
    k_chud_definition_group_tag
};

TAG_BLOCK(
    unit_hud_interface_block,
    sizeof(s_unit_hud_interface_reference),
    k_maximum_number_of_unit_hud_references)
{
    { _field_tag_reference, "type", &unit_hud_interface_reference },
    { _field_terminator }
};

TAG_PADDING(
    _field_short_integer,
    unit_dialogue_variant_post_variant_padding,
    1);

TAG_REFERENCE(
    unit_dialogue_reference,
    1)
{
    k_unit_dialogue_group_tag
};

TAG_BLOCK(
    unit_dialogue_variant_block,
    sizeof(s_unit_dialogue_variant),
    k_maximum_number_of_unit_dialogue_variants)
{
    { _field_short_integer, "variant_number" },
    { _field_padding, "post_variant_padding", &unit_dialogue_variant_post_variant_padding },
    { _field_tag_reference, "dialogue", &unit_dialogue_reference },
    { _field_terminator }
};

TAG_ENUM(
    unit_grenade_type_enum,
    k_number_of_unit_grenade_types)
{
    { "human_fragmentation", _unit_grenade_type_human_fragmentation },
    { "covenant_plasma", _unit_grenade_type_covenant_plasma },
};

TAG_BLOCK(
    unit_powered_seat_block,
    sizeof(s_unit_powered_seat),
    k_maximum_number_of_unit_powered_seats)
{
    { _field_real, "driver_powerup_time" },
    { _field_real, "driver_powerdown_time" },
    { _field_terminator }
};

TAG_REFERENCE(
    unit_weapon_reference,
    1)
{
    k_weapon_group_tag
};

TAG_BLOCK(
    unit_weapon_reference_block,
    sizeof(s_unit_weapon_reference),
    k_maximum_number_of_unit_weapons)
{
    { _field_tag_reference, "weapon", &unit_weapon_reference },
    { _field_string_id, "parent_marker" },
    { _field_terminator }
};

TAG_BLOCK(
    unit_target_tracking_type_block,
    sizeof(s_unit_target_tracking_type),
    k_maximum_number_of_unit_target_tracking_types)
{
    { _field_string_id, "tracking_type" },
    { _field_terminator }
};

TAG_REFERENCE(
    unit_sound_reference,
    2)
{
    k_sound_group_tag,
    k_sound_looping_group_tag
};

TAG_BLOCK(
    unit_target_tracking_block,
    sizeof(s_unit_target_tracking),
    k_maximum_number_of_unit_target_trackings)
{
    { _field_block, "tracking_types", &unit_target_tracking_type_block },
    { _field_real, "acquire_time" },
    { _field_real, "grace_time" },
    { _field_real, "decay_time" },
    { _field_tag_reference, "tracking_sound", &unit_sound_reference },
    { _field_tag_reference, "locked_sound", &unit_sound_reference },
};

TAG_ENUM(
    unit_seat_flags_enum,
    k_number_of_unit_seat_flags)
{
    { "seat_invisible", _unit_seat_invisible_bit },
    { "seat_locked", _unit_seat_locked_bit },
    { "seat_driver", _unit_seat_driver_bit },
    { "seat_gunner", _unit_seat_gunner_bit },
    { "seat_third_person_camera", _unit_seat_third_person_camera_bit },
    { "seat_allows_weapons", _unit_seat_allows_weapons_bit },
    { "seat_third_person_on_enter", _unit_seat_third_person_on_enter_bit },
    { "seat_first_person_camera_slaved_to_gun", _unit_seat_first_person_camera_slaved_to_gun_bit },
    { "seat_allow_vehicle_communication_animations", _unit_seat_allow_vehicle_communication_animations_bit },
    { "seat_not_valid_without_driver", _unit_seat_not_valid_without_driver_bit },
    { "seat_boarding_seat", _unit_seat_boarding_seat_bit },
    { "seat_ai_firing_disabled_by_max_acceleration", _unit_seat_ai_firing_disabled_by_max_acceleration_bit },
    { "seat_boarding_enters_seat", _unit_seat_boarding_enters_seat_bit },
    { "seat_boarding_need_any_passenger", _unit_seat_boarding_need_any_passenger_bit },
    { "seat_invalid_for_player", _unit_seat_invalid_for_player_bit },
    { "seat_invalid_for_non_player", _unit_seat_invalid_for_non_player_bit },
    { "seat_invalid_for_hero", _unit_seat_invalid_for_hero_bit },
    { "seat_gunner_player_only", _unit_seat_gunner_player_only_bit },
    { "seat_invisible_under_major_damage", _unit_seat_invisible_under_major_damage_bit },
    { "seat_melee_instant_killable", _unit_seat_melee_instant_killable_bit },
    { "seat_leader_preference", _unit_seat_leader_preference_bit },
    { "seat_allows_exit_and_detach", _unit_seat_allows_exit_and_detach_bit },
    { "seat_blocks_headshots", _unit_seat_blocks_headshots_bit },
    { "seat_exits_to_ground", _unit_seat_exits_to_ground_bit },
    { "seat_forward_from_attachment", _unit_seat_forward_from_attachment_bit },
    { "seat_disallow_ai_shooting", _unit_seat_disallow_ai_shooting_bit },
    { "seat_prevents_weapon_stowing", _unit_seat_prevents_weapon_stowing_bit },
    { "seat_takes_top_level_aoe_damage", _unit_seat_takes_top_level_aoe_damage_bit },
    { "seat_disallow_exit", _unit_seat_disallow_exit_bit },
    { "seat_local_aiming", _unit_seat_local_aiming_bit },
    { "seat_pelvis_relative_attachment", _unit_seat_pelvis_relative_attachment_bit },
    { "seat_apply_velocity_on_death_exit", _unit_seat_apply_velocity_on_death_exit_bit },
};

TAG_ENUM(
    unit_ai_seat_type_enum,
    k_number_of_unit_ai_seat_types)
{
    { "none", _unit_ai_seat_type_none },
    { "passenger", _unit_ai_seat_type_passenger },
    { "gunner", _unit_ai_seat_type_gunner },
    { "small_cargo", _unit_ai_seat_type_small_cargo },
    { "large_cargo", _unit_ai_seat_type_large_cargo },
    { "driver", _unit_ai_seat_type_driver },
};

extern s_tag_block_definition unit_seat_block;

TAG_PADDING(
    _field_short_integer,
    unit_boarding_seat_post_seat_padding,
    1);

TAG_BLOCK(
    unit_boarding_seat_block,
    sizeof(s_unit_boarding_seat),
    k_maximum_number_of_unit_boarding_seats)
{
    { _field_short_block_index, "seat", &unit_seat_block },
    { _field_padding, "post_seat_padding", &unit_boarding_seat_post_seat_padding },
    { _field_terminator }
};

TAG_BLOCK(
    unit_seat_block,
    sizeof(s_unit_seat),
    k_maximum_number_of_unit_seats)
{
    { _field_long_enum, "flags", &unit_seat_flags_enum },
    { _field_string_id, "label" },
    { _field_string_id, "marker_name" },
    { _field_string_id, "entry_marker_name" },
    { _field_string_id, "boarding_grenade_marker" },
    { _field_string_id, "boarding_grenade_string" },
    { _field_string_id, "boarding_melee_string" },
    { _field_string_id, "in_seat_string" },
    { _field_real, "ping_scale" },
    { _field_real, "turnover_time" },
    { _field_tag_reference, "seat_acceleration" },
    { _field_real, "ai_scariness" },
    { _field_short_enum, "ai_seat_type", &unit_ai_seat_type_enum },
    { _field_short_block_index, "boarding_seat", &unit_seat_block },
    { _field_block, "additional_boarding_seats", &unit_boarding_seat_block },
    { _field_real_fraction, "listener_interpolation_factor" },
    { _field_real_bounds, "yaw_rate_bounds" },
    { _field_real_bounds, "pitch_rate_bounds" },
    { _field_real, "pitch_interpolation_time" },
    { _field_real, "min_speed_reference" },
    { _field_real, "max_speed_reference" },
    { _field_real, "speed_exponent" },
    { _field_struct, "unit_camera", &unit_camera_struct },
    { _field_block, "hud_interface_references", &unit_hud_interface_reference },
    { _field_string_id, "enter_seat_string" },
    { _field_angle_bounds, "yaw_range" },
    { _field_tag_reference, "built_in_gunner" },
    { _field_real, "entry_radius" },
    { _field_angle, "entry_marker_cone_angle" },
    { _field_angle, "entry_marker_facing_angle" },
    { _field_real, "maximum_relative_velocity" },
    { _field_real, "open_time" },
    { _field_real, "close_time" },
    { _field_string_id, "open_function_name" },
    { _field_string_id, "opening_function_name" },
    { _field_string_id, "closing_function_name" },
    { _field_string_id, "invisible_seat_region" },
    { _field_long_integer, "runtime_invisible_seat_region_index" },
    { _field_terminator }
};

TAG_REFERENCE(
    unit_emp_disabled_effect_reference,
    1)
{
    k_effect_group_tag
};

TAG_REFERENCE(
    unit_boost_collision_damage_reference,
    1)
{
    k_collision_damage_group_tag
};

TAG_ENUM(
    unit_boost_flags_enum,
    k_number_of_unit_boost_flags)
{
    { "pegs_throttle", _unit_boost_pegs_throttle_bit },
};

TAG_STRUCT(
    unit_boost_struct,
    sizeof(s_unit_boost))
{
    { _field_tag_reference, "collision_damage" },
    { _field_long_flags, "flags", &unit_boost_flags_enum },
    { _field_real, "boost_peak_power" },
    { _field_real, "boost_rise_time" },
    { _field_real, "boost_fall_time" },
    { _field_real, "boost_power_per_second" },
    { _field_real, "boost_low_warning_threshold" },
    { _field_real, "recharge_rate" },
    { _field_data, "trigger_to_boost" },
    { _field_terminator }
};

TAG_STRUCT(
    unit_lipsync_struct,
    sizeof(s_unit_lipsync))
{
    { _field_real_fraction, "attack_weight" },
    { _field_real_fraction, "decay_weight" },
    { _field_terminator }
};

TAG_GROUP(
    unit_group,
    k_unit_group_tag,
    sizeof(s_unit_definition) - sizeof(s_object_definition),
    &object_group)
{
    { _field_long_flags, "unit_flags", &unit_definition_flags_enum },
    { _field_short_enum, "default_team", &campaign_team_enum },
    { _field_short_enum, "constant_sound_volume", &ai_sound_volume_enum },
    { _field_tag_reference, "hologram_unit", &unit_hologram_unit_reference },
    { _field_block, "campaign_metagame_bucket", &campaign_metagame_bucket_block },
    { _field_block, "screen_effects", &unit_screen_effect_reference_block },
    { _field_real, "camera_stiffness" },
    { _field_struct, "unit_camera", &unit_camera_struct },
    { _field_struct, "sync_action_camera", &unit_camera_struct },
    { _field_tag_reference, "assassination_start_damage_response", &unit_assassination_damage_response_reference },
    { _field_tag_reference, "assassination_object", &unit_assassination_object_reference },
    { _field_string_id, "assassination_object_stow_marker" },
    { _field_string_id, "assassination_object_out_marker" },
    { _field_string_id, "assassination_object_anchor_marker" },
    { _field_tag_reference, "seat_acceleration", &unit_seat_acceleration_reference },
    { _field_real, "soft_ping_threshold" },
    { _field_real, "soft_ping_interrupt_time" },
    { _field_real, "hard_ping_threshold" },
    { _field_real, "hard_ping_interrupt_time" },
    { _field_real, "hard_death_threshold" },
    { _field_real, "feign_death_threshold" },
    { _field_real, "feign_death_time" },
    { _field_real, "distance_of_evade_animation" },
    { _field_real, "pain_screen_duration" },
    { _field_real, "pain_screen_region_fade_out_duration" },
    { _field_real, "pain_screen_region_fade_out_weight_threshold" },
    { _field_angle, "paint_screen_angle_tolerance" },
    { _field_angle, "pain_screen_angle_randomness" },
    { _field_real, "defensive_screen_duration" },
    { _field_real, "defensive_screen_scrub_fallback_fraction" },
    { _field_real, "distance_of_dive_animation" },
    { _field_real, "terminal_velocity_fall_ratio" },
    { _field_real, "stun_movement_penalty" },
    { _field_real, "stun_turning_penalty" },
    { _field_real, "stun_jumping_penalty" },
    { _field_real, "minimum_stun_time" },
    { _field_real, "maximum_stun_time" },
    { _field_real, "feign_death_chance" },
    { _field_real, "feign_repeat_chance" },
    { _field_tag_reference, "spawned_turret_character", &unit_spawned_turret_character_reference },
    { _field_short_integer, "spawned_actor_count_min" },
    { _field_short_integer, "spawned_actor_count_max" },
    { _field_real, "spawned_velocity" },
    { _field_string_id, "aiming_pivot_marker" },
    { _field_angle, "aiming_velocity_maximum" },
    { _field_angle, "aiming_acceleration_maximum" },
    { _field_real, "casual_aiming_modifier" },
    { _field_angle, "looking_velocity_maximum" },
    { _field_angle, "looking_acceleration_maximum" },
    { _field_real, "object_velocity_maximum" },
    { _field_string_id, "right_hand_node" },
    { _field_string_id, "left_hand_node" },
    { _field_string_id, "preferred_gun_node" },
    { _field_string_id, "preferred_grenade_node" },
    { _field_string_id, "other_node" },
    { _field_tag_reference, "melee_damage", &unit_damage_effect_reference },
    { _field_tag_reference, "native_melee_override", &unit_damage_effect_reference },
    { _field_tag_reference, "boarding_melee_damage", &unit_damage_effect_reference },
    { _field_tag_reference, "boarding_melee_response", &unit_damage_effect_reference },
    { _field_tag_reference, "eviction_melee_damage", &unit_damage_effect_reference },
    { _field_tag_reference, "eviction_melee_response", &unit_damage_effect_reference },
    { _field_tag_reference, "landing_melee_damage", &unit_damage_effect_reference },
    { _field_tag_reference, "flurry_melee_damage", &unit_damage_effect_reference },
    { _field_tag_reference, "obstacle_smash_damage", &unit_damage_effect_reference },
    { _field_tag_reference, "assassination_damage", &unit_damage_effect_reference },
    { _field_short_enum, "motion_sensor_blip_size", &unit_motion_sensor_blip_size_enum },
    { _field_short_enum, "item_owner_size", &unit_item_owner_size_enum },
    { _field_string_id, "equipment_variant_name" },
    { _field_string_id, "grounded_equipment_variant_name" },
    { _field_block, "postures", &unit_posture_block },
    { _field_block, "hud_interfaces", &unit_hud_interface_block },
    { _field_block, "dialogue_variants", &unit_dialogue_variant_block },
    { _field_angle, "grenade_angle" },
    { _field_angle, "grenade_angle_max_elevation" },
    { _field_angle, "grenade_angle_min_elevation" },
    { _field_real, "grenade_velocity" },
    { _field_short_enum, "grenade_type", &unit_grenade_type_enum },
    { _field_short_integer, "grenade_count" },
    { _field_block, "powered_seats", &unit_powered_seat_block },
    { _field_block, "weapons", &unit_weapon_reference_block },
    { _field_block, "target_tracking", &unit_target_tracking_block },
    { _field_block, "seats", &unit_seat_block },
    { _field_real, "opening_time" },
    { _field_real, "closing_time" },
    { _field_real, "emp_disabled_time" },
    { _field_tag_reference, "emp_disabled_effect", &unit_emp_disabled_effect_reference },
    { _field_struct, "boost", &unit_boost_struct },
    { _field_struct, "lipsync", &unit_lipsync_struct },
    { _field_tag_reference, "exit_and_detach_damage", &unit_damage_effect_reference },
    { _field_tag_reference, "exit_and_detach_weapon", &unit_weapon_reference },
    { _field_terminator }
};
