#include <effects/effects.h>
#include <effects/material_effect_definitions.h>
#include <items/equipment_definitions.h>
#include <models/model_definitions.h>
#include <objects/crates.h>
#include <objects/object_definitions.h>
#include <objects/widgets/antenna.h>
#include <objects/widgets/cloth.h>
#include <physics/havok_collision_damage.h>
#include <simulation/game_interface/simulation_game_position_updates.h>
#include <sound/sound_definitions.h>
#include <tag_files/tag_definitions.h>

extern s_enum_definition object_type_enum;
extern s_enum_definition water_density_enum;
extern s_tag_block_definition water_physics_hull_surface_definition_block;
extern s_tag_block_definition jetwash_definition_block;
extern s_tag_block_definition multiplayer_object_definition_block;

/* ---------- definitions */

TAG_REFERENCE(object_any_reference, 1) { (tag)NONE };

TAG_PAD(_field_short_integer, post_object_type_padding, 1);

TAG_ENUM(object_flags_enum, k_number_of_object_flags)
{
	{ "does_not_cast_shadow", _object_does_not_cast_shadow_bit },
	{ "search_cardinal_direction_lightmaps_on_failure", _object_search_cardinal_direction_lightmaps_on_failure_bit },
	{ "preserves_initial_damage_owner", _object_preserves_initial_damage_owner_bit },
	{ "not_a_pathfinding_obstacle", _object_not_a_pathfinding_obstacle_bit },
	{ "extension_of_parent", _object_extension_of_parent_bit },
	{ "does_not_cause_collision_damage", _object_does_not_cause_collision_damage_bit },
	{ "early_mover", _object_early_mover_bit },
	{ "early_mover_localized_physics", _object_early_mover_localized_physics_bit },
	{ "use_static_massive_lightmap_sample", _object_use_static_massive_lightmap_sample_bit },
	{ "scales_attachments", _object_scales_attachments_bit },
	{ "inherits_player_s_appearance", _object_inherits_player_s_appearance_bit },
	{ "non_physical_in_map_editor", _object_non_physical_in_map_editor_bit },
	{ "is_always_on_ceiling", _object_is_always_on_ceiling_bit },
	{ "sample_environment_lighting_only_ignore_object_lighting", _object_sample_environment_lighting_only_ignore_object_lighting_bit },
	{ "effects_created_by_this_object_do_not_spawn_objects_in_multiplayer", _object_effects_created_by_this_object_do_not_spawn_objects_in_multiplayer_bit },
	{ "does_not_collide_with_camera", _object_does_not_collide_with_camera_bit },
	{ "force_collide_with_camera", _object_force_collide_with_camera_bit },
	{ "damage_not_blocked_by_obstructions", _object_damage_not_blocked_by_obstructions_bit },
	{ "does_not_damage_breakable_surfaces", _object_does_not_damage_breakable_surfaces_bit },
};

TAG_ENUM(
	object_lightmap_shadow_mode_enum,
	k_number_of_object_lightmap_shadow_modes)
{
	{ "default", _object_lightmap_shadow_mode_default },
	{ "never", _object_lightmap_shadow_mode_never },
	{ "always", _object_lightmap_shadow_mode_always },
	{ "blur", _object_lightmap_shadow_mode_blur },
};

TAG_ENUM(
	object_sweetener_size_enum,
	k_number_of_object_sweetener_sizes)
{
	{ "small", _object_sweetener_size_small },
	{ "medium", _object_sweetener_size_medium },
	{ "large", _object_sweetener_size_large },
};

TAG_ENUM(
	object_runtime_flags_enum,
	k_number_of_object_runtime_flags)
{
	{ "unknown0", _object_runtime_unknown0_bit },
	{ "unknown1", _object_runtime_unknown1_bit },
	{ "unknown2", _object_runtime_unknown2_bit },
	{ "unknown3", _object_runtime_unknown3_bit },
	{ "unknown4", _object_runtime_unknown4_bit },
	{ "unknown5", _object_runtime_unknown5_bit },
	{ "unknown6", _object_runtime_unknown6_bit },
	{ "unknown7", _object_runtime_unknown7_bit },
	{ "unknown8", _object_runtime_unknown8_bit },
	{ "unknown9", _object_runtime_unknown9_bit },
	{ "unknown10", _object_runtime_unknown10_bit },
	{ "unknown11", _object_runtime_unknown11_bit },
	{ "unknown12", _object_runtime_unknown12_bit },
	{ "unknown13", _object_runtime_unknown13_bit },
	{ "unknown14", _object_runtime_unknown14_bit },
	{ "unknown15", _object_runtime_unknown15_bit },
	{ "unknown16", _object_runtime_unknown16_bit },
	{ "unknown17", _object_runtime_unknown17_bit },
	{ "unknown18", _object_runtime_unknown18_bit },
	{ "unknown19", _object_runtime_unknown19_bit },
	{ "unknown20", _object_runtime_unknown20_bit },
	{ "unknown21", _object_runtime_unknown21_bit },
	{ "unknown22", _object_runtime_unknown22_bit },
	{ "unknown23", _object_runtime_unknown23_bit },
	{ "unknown24", _object_runtime_unknown24_bit },
	{ "unknown25", _object_runtime_unknown25_bit },
	{ "unknown26", _object_runtime_unknown26_bit },
	{ "unknown27", _object_runtime_unknown27_bit },
	{ "unknown28", _object_runtime_unknown28_bit },
	{ "unknown29", _object_runtime_unknown29_bit },
	{ "unknown30", _object_runtime_unknown30_bit },
	{ "unknown31", _object_runtime_unknown31_bit },
};

TAG_REFERENCE(object_model_reference, 1){ k_model_group_tag };
TAG_REFERENCE(object_crate_object_reference, 1) { k_crate_group_tag };
TAG_REFERENCE(object_collision_damage_reference, 1) { k_collision_damage_group_tag };

TAG_BLOCK(
	object_early_mover_obb_block,
	sizeof(s_object_early_mover_obb),
	k_maximum_number_of_object_early_mover_obbs)
{
	{ _field_string_id, "node_name" },
	{ _field_real_bounds, "x_bounds" },
	{ _field_real_bounds, "y_bounds" },
	{ _field_real_bounds, "z_bounds" },
	{ _field_real_euler_angles3d, "angles" },
	{ _field_terminator }
};

TAG_REFERENCE(object_creation_effect_reference, 1) { k_effect_group_tag };
TAG_REFERENCE(object_material_effects_reference, 1) { k_material_effects_group_tag };
TAG_REFERENCE(object_melee_sound_reference, 1) { k_sound_group_tag };

TAG_ENUM(
	object_ai_properties_flags_enum,
	k_number_of_object_ai_properties_flags)
{
	{ "destroyable_cover", _object_ai_properties_destroyable_cover_bit },
	{ "pathfinding_ignore_when_dead", _object_ai_properties_pathfinding_ignore_when_dead_bit },
	{ "dynamic_cover", _object_ai_properties_dynamic_cover_bit },
	{ "non_flight_blocking", _object_ai_properties_non_flight_blocking_bit },
	{ "dynamic_cover_from_center", _object_ai_properties_dynamic_cover_from_center_bit },
	{ "has_corner_markers", _object_ai_properties_has_corner_markers_bit },
	{ "consider_for_interaction", _object_ai_properties_consider_for_interaction_bit },
	{ "leap_on_cover_target", _object_ai_properties_leap_on_cover_target_bit },
};

TAG_ENUM(
	object_ai_size_enum,
	k_number_of_object_ai_sizes)
{
	{ "default", _object_ai_size_default },
	{ "tiny", _object_ai_size_tiny },
	{ "small", _object_ai_size_small },
	{ "medium", _object_ai_size_medium },
	{ "large", _object_ai_size_large },
	{ "huge", _object_ai_size_huge },
	{ "immobile", _object_ai_size_immobile },
};

TAG_ENUM(
	object_ai_distance_enum,
	k_number_of_object_ai_distances)
{
	{ "none", _object_ai_distance_none },
	{ "down", _object_ai_distance_down },
	{ "step", _object_ai_distance_step },
	{ "crouch", _object_ai_distance_crouch },
	{ "stand", _object_ai_distance_stand },
	{ "storey", _object_ai_distance_storey },
	{ "tower", _object_ai_distance_tower },
	{ "infinite", _object_ai_distance_infinite },
};

TAG_BLOCK(
	object_ai_properties_block,
	sizeof(s_object_ai_properties),
	k_maximum_number_of_object_ai_properties)
{
	{ _field_long_flags, "flags", &object_ai_properties_flags_enum },
	{ _field_string_id, "ai_type_name" },
	{ _field_string_id, "interaction_name" },
	{ _field_short_enum, "size", &object_ai_size_enum },
	{ _field_short_enum, "leap_jump_speed", &object_ai_distance_enum },
	{ _field_terminator }
};

TAG_ENUM(
	object_function_flags_enum,
	k_number_of_object_function_flags)
{
	{ "invert", _object_function_invert_bit },
	{ "mapping_does_not_control_active", _object_function_mapping_does_not_control_active_bit },
	{ "always_active", _object_function_always_active_bit },
	{ "random_time_offset", _object_function_random_time_offset_bit },
	{ "always_exports_value", _object_function_always_exports_value_bit },
	{ "turn_off_with_uses_magnitude", _object_function_turn_off_with_uses_magnitude_bit },
};

TAG_ENUM(
	object_function_interpolation_mode_enum,
	k_number_of_object_function_interpolations)
{
	{ "constant_velocity", _object_function_interpolation_constant_velocity },
	{ "linear_acceleration", _object_function_interpolation_linear_acceleration },
	{ "damped_spring", _object_function_interpolation_damped_spring },
	{ "fractional", _object_function_interpolation_fractional },
};

TAG_BLOCK(
	object_function_interpolation_block,
	sizeof(s_object_function_interpolation),
	k_maximum_number_of_object_function_interpolations)
{
	{ _field_long_enum, "interpolation_mode", &object_function_interpolation_block },
	{ _field_real, "linear_travel_time" },
	{ _field_real, "acceleration" },
	{ _field_real, "spring_k" },
	{ _field_real, "spring_c" },
	{ _field_real, "fraction" },
	{ _field_terminator }
};

TAG_BLOCK(
	object_runtime_interpolator_function_block,
	sizeof(s_object_runtime_interpolator_function),
	k_maximum_number_of_object_runtime_interpolator_functions)
{
	{ _field_long_integer, "runtime_interpolator_to_object_function_mapping" },
	{ _field_terminator }
};

TAG_BLOCK(
	object_function_block,
	sizeof(s_object_function),
	k_maximum_number_of_object_functions)
{
	{ _field_long_flags, "flags", &object_function_flags_enum },
	{ _field_string_id, "import_name" },
	{ _field_string_id, "export_name" },
	{ _field_string_id, "turn_off_with" },
	{ _field_string_id, "ranged_interpolation_name" },
	{ _field_real, "minimum_value" },
	{ _field_data, "default_function" },
	{ _field_string_id, "scale_by" },
	{ _field_block, "interpolation", &object_function_interpolation_block },
	{ _field_long_block_index, "runtime_interpolator_index", &object_runtime_interpolator_function_block },
	{ _field_terminator }
};

TAG_PAD(_field_short_integer, object_post_hud_text_message_padding, 1);

TAG_ENUM(
	object_attachment_change_color_enum,
	k_number_of_object_attachment_change_colors)
{
	{ "none", _object_attachment_change_color_none },
	{ "primary", _object_attachment_change_color_primary },
	{ "secondary", _object_attachment_change_color_secondary },
	{ "tertiary", _object_attachment_change_color_tertiary },
	{ "quaternary", _object_attachment_change_color_quaternary },
};

TAG_ENUM(
	object_attachment_flags_enum,
	k_number_of_object_attachment_flags)
{
	{ "force_always_on", _object_attachment_force_always_on_bit },
	{ "effect_size_scale_from_object_scale", _object_attachment_effect_size_scale_from_object_scale_bit },
};

TAG_BLOCK(
	object_attachment_block,
	sizeof(s_object_attachment),
	k_maximum_number_of_object_attachments)
{
	{ _field_tag_reference, "type", &object_any_reference },
	{ _field_string_id, "marker" },
	{ _field_short_enum, "change_color", &object_attachment_change_color_enum },
	{ _field_word_flags, "flags", &object_attachment_flags_enum },
	{ _field_string_id, "primary_scale" },
	{ _field_string_id, "secondary_scale" },
	{ _field_terminator }
};

TAG_REFERENCE(object_widget_reference, 2) { k_antenna_group_tag, k_clothwind_group_tag };

TAG_BLOCK(
	object_widget_block,
	sizeof(s_object_widget),
	k_maximum_number_of_object_widgets)
{
	{ _field_tag_reference, "type", &object_widget_reference },
	{ _field_terminator }
};

TAG_BLOCK(
	object_change_color_initial_permutation_block,
	sizeof(s_object_change_color_initial_permutation),
	k_maximum_number_of_object_change_color_initial_permutations)
{
	{ _field_real, "weight" },
	{ _field_real_rgb_color, "color_lower_bound" },
	{ _field_real_rgb_color, "color_upper_bound" },
	{ _field_string_id, "variant_name" },
	{ _field_terminator }
};

TAG_ENUM(
	object_change_color_function_flags_enum,
	k_number_of_object_change_color_function_flags)
{
	{ "blend_in_hsv", _object_change_color_function_blend_in_hsv_bit },
	{ "more_colors", _object_change_color_function_more_colors_bit },
};

TAG_BLOCK(
	object_change_color_function_block,
	sizeof(s_object_change_color_function),
	k_maximum_number_of_object_change_color_functions)
{
	{ _field_long_flags, "flags", &object_change_color_function_flags_enum },
	{ _field_real_rgb_color, "color_lower_bound" },
	{ _field_real_rgb_color, "color_upper_bound" },
	{ _field_string_id, "darken_by" },
	{ _field_string_id, "scale_by" },
	{ _field_terminator }
};

TAG_BLOCK(
	object_change_color_block,
	sizeof(s_object_change_color),
	k_maximum_number_of_object_change_colors)
{
	{ _field_block, "initial_permutations", &object_change_color_initial_permutation_block },
	{ _field_block, "functions", &object_change_color_function_block },
	{ _field_terminator }
};

TAG_BLOCK(
	object_predicted_resource_block,
	sizeof(s_object_predicted_resource),
	NONE)
{
	{ _field_short_integer, "type_index" },
	{ _field_short_integer, "resource_index" },
	{ _field_long_integer, "tag_index" },
	{ _field_terminator }
};

TAG_REFERENCE(
	object_simulation_interpolation_reference,
	1)
{
	k_simulation_interpolation_group_tag
};

TAG_REFERENCE(
	object_reviving_equipment_reference,
	1)
{
	k_equipment_group_tag
};

TAG_BLOCK(
	object_reviving_equipment_block,
	sizeof(s_object_reviving_equipment),
	NONE)
{
	{ _field_tag_reference, "type", &object_reviving_equipment_reference },
	{ _field_terminator }
};

TAG_GROUP(
	object_group,
	k_object_group_tag,
	sizeof(s_object_definition))
{
	{ _field_short_enum, "object_type", &object_type_enum },
	{ _field_pad, "post_object_type_padding", &post_object_type_padding },
	{ _field_long_flags, "object_flags", &object_flags_enum },
	{ _field_real, "bounding_radius" },
	{ _field_real_point3d, "bounding_offset" },
	{ _field_real, "horizontal_acceleration_scale" },
	{ _field_real, "vertical_acceleration_scale" },
	{ _field_real, "angular_acceleration_scale" },
	{ _field_short_enum, "lightmap_shadow_mode", &object_lightmap_shadow_mode_enum },
	{ _field_char_enum, "sweetener_size", &object_sweetener_size_enum },
	{ _field_char_enum, "water_density", &water_density_enum },
	{ _field_long_flags, "runtime_flags", &object_runtime_flags_enum },
	{ _field_real, "dynamic_light_sphere_radius" },
	{ _field_real_point3d, "dynamic_light_sphere_offset" },
	{ _field_string_id, "generic_hud_text" },
	{ _field_tag_reference, "generic_name_list" },
	{ _field_tag_reference, "generic_service_tag_list" },
	{ _field_string_id, "default_variant" },
	{ _field_tag_reference, "model", &object_model_reference },
	{ _field_tag_reference, "crate_object", &object_crate_object_reference },
	{ _field_tag_reference, "collision_damage", &object_collision_damage_reference },
	{ _field_tag_reference, "brittle_collision_damage", &object_collision_damage_reference },
	{ _field_block, "early_mover_obb", &object_early_mover_obb_block },
	{ _field_tag_reference, "creation_effect", &object_creation_effect_reference },
	{ _field_tag_reference, "material_effects", &object_material_effects_reference },
	{ _field_tag_reference, "melee_sound", &object_melee_sound_reference },
	{ _field_block, "ai_properties", &object_ai_properties_block },
	{ _field_block, "functions", &object_function_block },
	{ _field_block, "runtime_interpolator_functions", &object_runtime_interpolator_function_block },
	{ _field_short_integer, "hud_text_message_index" },
	{ _field_pad, "post_hud_text_message_padding", &object_post_hud_text_message_padding },
	{ _field_block, "attachments", &object_attachment_block },
	{ _field_block, "hull_surfaces", &water_physics_hull_surface_definition_block },
	{ _field_block, "jetwash", &jetwash_definition_block },
	{ _field_block, "widgets", &object_widget_block },
	{ _field_block, "change_colors", &object_change_color_block },
	{ _field_block, "multiplayer_object", &multiplayer_object_definition_block },
	{ _field_tag_reference, "simulation_interpolation", &object_simulation_interpolation_reference },
	{ _field_block, "reviving_equipment", &object_reviving_equipment_block },
	{ _field_block, "unknown_object_block", nullptr }, // TODO
	{ _field_terminator }
};
