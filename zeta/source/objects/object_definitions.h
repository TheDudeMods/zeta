#pragma once

#include <cseries/cseries.h>
#include <math/real_math.h>
#include <objects/object_types.h>
#include <tag_files/tag_groups.h>

/* ---------- constants */

enum
{
	k_object_group_tag = 'obje'
};

/* ---------- enumerators */

enum e_object_flags
{
	_object_does_not_cast_shadow_bit,
	_object_search_cardinal_direction_lightmaps_on_failure_bit,
	_object_preserves_initial_damage_owner_bit,
	_object_not_a_pathfinding_obstacle_bit,
	_object_extension_of_parent_bit,
	_object_does_not_cause_collision_damage_bit,
	_object_early_mover_bit,
	_object_early_mover_localized_physics_bit,
	_object_use_static_massive_lightmap_sample_bit,
	_object_scales_attachments_bit,
	_object_inherits_player_s_appearance_bit,
	_object_non_physical_in_map_editor_bit,
	_object_is_always_on_ceiling_bit,
	_object_sample_environment_lighting_only_ignore_object_lighting_bit,
	_object_effects_created_by_this_object_do_not_spawn_objects_in_multiplayer_bit,
	_object_does_not_collide_with_camera_bit,
	_object_force_collide_with_camera_bit,
	_object_damage_not_blocked_by_obstructions_bit,
	_object_does_not_damage_breakable_surfaces_bit,
	k_number_of_object_flags
};

enum e_object_lightmap_shadow_mode
{
	_object_lightmap_shadow_mode_default,
	_object_lightmap_shadow_mode_never,
	_object_lightmap_shadow_mode_always,
	_object_lightmap_shadow_mode_blur,
	k_number_of_object_lightmap_shadow_modes
};

enum e_object_sweetener_size
{
	_object_sweetener_size_small,
	_object_sweetener_size_medium,
	_object_sweetener_size_large,
	k_number_of_object_sweetener_sizes
};

enum e_object_water_density
{
	_object_water_density_least,
	_object_water_density_some,
	_object_water_density_equal,
	_object_water_density_more,
	_object_water_density_more_still,
	_object_water_density_lots_more,
	k_number_of_object_water_densities
};

enum e_object_runtime_flags
{
	_object_runtime_unknown0_bit,
	_object_runtime_unknown1_bit,
	_object_runtime_unknown2_bit,
	_object_runtime_unknown3_bit,
	_object_runtime_unknown4_bit,
	_object_runtime_unknown5_bit,
	_object_runtime_unknown6_bit,
	_object_runtime_unknown7_bit,
	_object_runtime_unknown8_bit,
	_object_runtime_unknown9_bit,
	_object_runtime_unknown10_bit,
	_object_runtime_unknown11_bit,
	_object_runtime_unknown12_bit,
	_object_runtime_unknown13_bit,
	_object_runtime_unknown14_bit,
	_object_runtime_unknown15_bit,
	_object_runtime_unknown16_bit,
	_object_runtime_unknown17_bit,
	_object_runtime_unknown18_bit,
	_object_runtime_unknown19_bit,
	_object_runtime_unknown20_bit,
	_object_runtime_unknown21_bit,
	_object_runtime_unknown22_bit,
	_object_runtime_unknown23_bit,
	_object_runtime_unknown24_bit,
	_object_runtime_unknown25_bit,
	_object_runtime_unknown26_bit,
	_object_runtime_unknown27_bit,
	_object_runtime_unknown28_bit,
	_object_runtime_unknown29_bit,
	_object_runtime_unknown30_bit,
	_object_runtime_unknown31_bit,
	k_number_of_object_runtime_flags
};

enum e_object_ai_properties_flags
{
	_object_ai_properties_destroyable_cover_bit,
	_object_ai_properties_pathfinding_ignore_when_dead_bit,
	_object_ai_properties_dynamic_cover_bit,
	_object_ai_properties_non_flight_blocking_bit,
	_object_ai_properties_dynamic_cover_from_center_bit,
	_object_ai_properties_has_corner_markers_bit,
	_object_ai_properties_consider_for_interaction_bit,
	_object_ai_properties_leap_on_cover_target_bit,
	k_number_of_object_ai_properties_flags
};

enum e_object_ai_size
{
	_object_ai_size_default,
	_object_ai_size_tiny,
	_object_ai_size_small,
	_object_ai_size_medium,
	_object_ai_size_large,
	_object_ai_size_huge,
	_object_ai_size_immobile,
	k_number_of_object_ai_sizes
};

enum e_object_ai_distance
{
	_object_ai_distance_none,
	_object_ai_distance_down,
	_object_ai_distance_step,
	_object_ai_distance_crouch,
	_object_ai_distance_stand,
	_object_ai_distance_storey,
	_object_ai_distance_tower,
	_object_ai_distance_infinite,
	k_number_of_object_ai_distances
};

enum e_object_function_interpolation_mode
{
	_object_function_interpolation_constant_velocity,
	_object_function_interpolation_linear_acceleration,
	_object_function_interpolation_damped_spring,
	_object_function_interpolation_fractional,
	k_number_of_object_function_interpolations
};

enum e_object_function_flags
{
	_object_function_invert_bit,
	_object_function_mapping_does_not_control_active_bit,
	_object_function_always_active_bit,
	_object_function_random_time_offset_bit,
	_object_function_always_exports_value_bit,
	_object_function_turn_off_with_uses_magnitude_bit,
	k_number_of_object_function_flags
};

enum e_object_attachment_change_color
{
	_object_attachment_change_color_none,
	_object_attachment_change_color_primary,
	_object_attachment_change_color_secondary,
	_object_attachment_change_color_tertiary,
	_object_attachment_change_color_quaternary,
	k_number_of_object_attachment_change_colors
};

enum e_object_attachment_flags
{
	_object_attachment_force_always_on_bit,
	_object_attachment_effect_size_scale_from_object_scale_bit,
	k_number_of_object_attachment_flags
};

/* ---------- structures */

struct s_object_early_mover_obb
{
	string_id node_name;
	real_bounds x_bounds;
	real_bounds y_bounds;
	real_bounds z_bounds;
	real_euler_angles3d angles;
};
static_assert(sizeof(s_object_early_mover_obb) == 0x28);

struct s_object_ai_properties
{
	c_flags<e_object_ai_properties_flags, long> flags;
	string_id ai_type_name;
	string_id interaction_name;
	c_enum<e_object_ai_size, short> size;
	c_enum<e_object_ai_distance, short> leap_jump_speed;
};
static_assert(sizeof(s_object_ai_properties) == 0x10);

struct s_object_function_interpolation
{
	c_enum<e_object_function_interpolation_mode, long> interpolation_mode;
	real linear_travel_time;
	real acceleration;
	real spring_k;
	real spring_c;
	real fraction;
};
static_assert(sizeof(s_object_function_interpolation) == 0x18);

struct s_object_runtime_interpolator_function
{
	long runtime_interpolator_to_object_function_mapping;
};
static_assert(sizeof(s_object_runtime_interpolator_function) == 0x4);

struct s_object_function
{
	c_flags<e_object_function_flags, long> flags;
	string_id import_name;
	string_id export_name;
	string_id turn_off_with;
	string_id ranged_interpolation_name;
	real minimum_value;
	s_tag_data default_function;
	string_id scale_by;
	c_tag_block<s_object_function_interpolation> interpolation;
	c_tag_block_index<s_object_runtime_interpolator_function, long> runtime_interpolator_index;
};
static_assert(sizeof(s_object_function) == 0x40);

struct s_object_attachment
{
	s_tag_reference type;
	string_id marker;
	c_enum<e_object_attachment_change_color, short> change_color;
	c_flags<e_object_attachment_flags, word> flags;
	string_id primary_scale;
	string_id secondary_scale;
};
static_assert(sizeof(s_object_attachment) == 0x20);

struct s_object_definition
{
	c_enum<e_object_type, short> object_type;
	short : 16;
	c_enum<e_object_flags, long> object_flags;
	real bounding_radius;
	real_point3d bounding_offset;
	real horizontal_acceleration_scale;
	real vertical_acceleration_scale;
	real angular_acceleration_scale;
	c_enum<e_object_lightmap_shadow_mode, short> lightmap_shadow_mode;
	c_enum<e_object_sweetener_size, char> sweetener_size;
	c_enum<e_object_water_density, char> water_density;
	c_flags<e_object_runtime_flags, long> runtime_flags;
	real dynamic_light_sphere_radius;
	real_point3d dynamic_light_sphere_offset;
	string_id generic_hud_text;
	s_tag_reference generic_name_list;
	s_tag_reference generic_service_tag_list;
	string_id default_variant;
	s_tag_reference model;
	s_tag_reference crate_object;
	s_tag_reference collision_damage;
	s_tag_reference brittle_collision_damage;
	c_tag_block<s_object_early_mover_obb> early_mover_obb;
	s_tag_reference creation_effect;
	s_tag_reference material_effects;
	s_tag_reference melee_impact;
	c_tag_block<s_object_ai_properties> ai_properties;
	c_tag_block<s_object_function> functions;
	c_tag_block<s_object_runtime_interpolator_function> runtime_interpolator_functions;
	short hud_text_message_index;
	short : 16;
	c_tag_block<s_object_attachment> attachments;
	//
	// TODO: finish
	//
};
