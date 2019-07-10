#pragma once

#include <cseries/cseries.h>
#include <math/real_math.h>
#include <objects/object_types.h>

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

/* ---------- structures */

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
	//
	// TODO: finish
	//
};
