#include <physics/character_physics_definitions.h>
#include <tag_files/tag_groups.h>

/* ---------- definitions */

TAG_ENUM(
	character_physics_flags_enum,
	k_number_of_character_physics_flags)
{
	{ "centered_at_origin", _character_physics_centered_at_origin_bit },
	{ "shape_spherical", _character_physics_shape_spherical_bit },
	{ "use_player_physics", _character_physics_use_player_physics_bit },
	{ "climb_any_surface", _character_physics_climb_any_surface_bit },
	{ "flying", _character_physics_flying_bit },
	{ "not_physical", _character_physics_not_physical_bit },
	{ "dead_character_collision_group", _character_physics_dead_character_collision_group_bit },
	{ "suppress_ground_planes_on_bipeds", _character_physics_suppress_ground_planes_on_bipeds_bit },
	{ "physical_ragdoll", _character_physics_physical_ragdoll_bit },
	{ "do_not_resize_dead_spheres", _character_physics_do_not_resize_dead_spheres_bit },
};

TAG_STRUCT(
	character_ground_physics_definition_struct,
	sizeof(s_character_ground_physics_definition))
{
	{ _field_angle, "maximum_slope_angle" },
	{ _field_angle, "downhill_falloff_angle" },
	{ _field_angle, "downhill_cutoff_angle" },
	{ _field_angle, "uphill_falloff_angle" },
	{ _field_angle, "uphill_cutoff_angle" },
	{ _field_real, "downhill_velocity_scale" },
	{ _field_real, "uphill_velocity_scale" },
	{ _field_real, "runtime_minimum_normal_k" },
	{ _field_real, "runtime_downhill_k0" },
	{ _field_real, "runtime_downhill_k1" },
	{ _field_real, "runtime_uphill_k0" },
	{ _field_real, "runtime_uphill_k1" },
	{ _field_real, "climb_inflection_angle" },
	{ _field_real, "scale_airborne_reaction_time" },
	{ _field_real, "scale_ground_adhesion_velocity" },
	{ _field_real, "gravity_scale" },
	{ _field_real, "airborne_acceleration_scale" },
	{ _field_terminator }
};

TAG_ENUM(
	character_flying_physics_flags_enum,
	k_number_of_character_flying_physics_flags)
{
	{ "use_world_up", _character_flying_physics_use_world_up_bit },
};

TAG_STRUCT(
	character_flying_physics_definition_struct,
	sizeof(s_character_flying_physics_definition))
{
	{ _field_angle, "bank_angle" },
	{ _field_real, "bank_apply_time" },
	{ _field_real, "bank_decay_time" },
	{ _field_real, "pitch_ratio" },
	{ _field_real, "maximum_velocity" },
	{ _field_real, "maximum_sidestep_velocity" },
	{ _field_real, "acceleration" },
	{ _field_real, "deceleration" },
	{ _field_angle, "angular_velocity_maximum" },
	{ _field_angle, "angular_acceleration_maximum" },
	{ _field_real, "crouch_velocity_modifier" },
	{ _field_long_flags, "flags", &character_flying_physics_flags_enum },
	{ _field_terminator }
};

TAG_STRUCT(
	character_physics_definition_struct,
	sizeof(s_character_physics_definition))
{
	{ _field_long_flags, "flags", &character_physics_flags_enum },
	{ _field_real, "height_standing" },
	{ _field_real, "height_crouching" },
	{ _field_real, "radius" },
	{ _field_real, "mass" },
	{ _field_string_id, "living_material_name" },
	{ _field_string_id, "dead_material_name" },
	{ _field_short_integer, "runtime_global_material_type" }, // <--- TODO: block index
	{ _field_short_integer, "runtime_dead_global_material_type" }, // <--- TODO: block index
	{ _field_block, "dead_sphere_shapes" },
	{ _field_block, "pill_shapes" },
	{ _field_block, "sphere_shapes" },
	{ _field_struct, "ground_physics", &character_ground_physics_definition_struct },
	{ _field_struct, "flying_physics", &character_flying_physics_definition_struct },
	{ _field_terminator }
};
