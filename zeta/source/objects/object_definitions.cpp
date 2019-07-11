#include <objects/object_definitions.h>
#include <tag_files/tag_definitions.h>

extern s_enum_definition object_type_enum;

TAG_PADDING(_field_short_integer, post_object_type_padding, 1);

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

TAG_ENUM(object_lightmap_shadow_mode_enum, k_number_of_object_lightmap_shadow_modes)
{
	{ "default", _object_lightmap_shadow_mode_default },
	{ "never", _object_lightmap_shadow_mode_never },
	{ "always", _object_lightmap_shadow_mode_always },
	{ "blur", _object_lightmap_shadow_mode_blur },
};

TAG_ENUM(object_sweetener_size_enum, k_number_of_object_sweetener_sizes)
{
	{ "small", _object_sweetener_size_small },
	{ "medium", _object_sweetener_size_medium },
	{ "large", _object_sweetener_size_large },
};

TAG_ENUM(object_water_density_enum, k_number_of_object_water_densities)
{
	{ "least", _object_water_density_least },
	{ "some", _object_water_density_some },
	{ "equal", _object_water_density_equal },
	{ "more", _object_water_density_more },
	{ "more_still", _object_water_density_more_still },
	{ "lots_more", _object_water_density_lots_more },
};

TAG_ENUM(object_runtime_flags_enum, k_number_of_object_runtime_flags)
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

TAG_STRUCT(object_early_mover_obb_block, sizeof(s_object_early_mover_obb))
{
	{ _field_string_id, "node_name" },
	{ _field_real_bounds, "x_bounds" },
	{ _field_real_bounds, "y_bounds" },
	{ _field_real_bounds, "z_bounds" },
	{ _field_real_euler_angles3d, "angles" },
	{ _field_terminator }
};

TAG_GROUP(object_group, k_object_group_tag, sizeof(s_object_definition))
{
	{ _field_short_enum, "object_type", &object_type_enum },
	{ _field_padding, "post_object_type_padding", &post_object_type_padding },
	{ _field_long_flags, "object_flags", &object_flags_enum },
	{ _field_real, "bounding_radius" },
	{ _field_real_point3d, "bounding_offset" },
	{ _field_real, "horizontal_acceleration_scale" },
	{ _field_real, "vertical_acceleration_scale" },
	{ _field_real, "angular_acceleration_scale" },
	{ _field_long_flags, "runtime_flags", &object_runtime_flags_enum },
	{ _field_real, "dynamic_light_sphere_radius" },
	{ _field_real_point3d, " dynamic_light_sphere_offset" },
	{ _field_string_id, "generic_hud_text" },
	{ _field_tag_reference, "generic_name_list" },
	{ _field_tag_reference, "generic_service_tag_list" },
	{ _field_string_id, "default_variant" },
	{ _field_tag_reference, "model" },
	{ _field_tag_reference, "crate_object" },
	{ _field_tag_reference, "collision_damage" },
	{ _field_tag_reference, "brittle_collision_damage" },
	{ _field_block, "early_mover_obb", &object_early_mover_obb_block},
	//
	// TODO: finish
	//
	{ _field_terminator }
};
