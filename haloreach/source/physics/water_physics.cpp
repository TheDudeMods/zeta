#include <physics/water_physics.h>

/* ---------- definitions */

TAG_ENUM(
	water_density_enum,
	k_number_of_water_densities)
{
	{ "least", _water_density_least },
	{ "some", _water_density_some },
	{ "equal", _water_density_equal },
	{ "more", _water_density_more },
	{ "more_still", _water_density_more_still },
	{ "lots_more", _water_density_lots_more },
};

TAG_ENUM(
	water_physics_hull_surface_flags_enum,
	k_number_of_water_physics_hull_surface_flags)
{
	{ "works_on_land", _water_physics_hull_surface_works_on_land_bit },
	{ "effects_only", _water_physics_hull_surface_effects_only_bit },
};

TAG_PADDING(
	_field_short_integer,
	water_physics_hull_surface_post_flags_padding,
	1);

TAG_STRUCT(
	water_physics_velocity_mapping_struct,
	sizeof(s_water_physics_velocity_mapping))
{
	{ _field_data, "data" },
	{ _field_real, "max_velocity" },
	{ _field_terminator }
};

TAG_STRUCT(
	water_physics_drag_velocity_mapping_struct,
	sizeof(s_water_physics_drag_velocity_mapping))
{
	{ _field_struct, "pressure", &water_physics_velocity_mapping_struct },
	{ _field_struct, "suction", &water_physics_velocity_mapping_struct },
	{ _field_real, "linear_damping" },
	{ _field_real, "angular_damping" },
	{ _field_terminator }
};

TAG_BLOCK(
	water_physics_material_override_struct,
	sizeof(s_water_physics_material_override),
	NONE)
{
	{ _field_string_id, "material" },
	{ _field_struct, "drag", &water_physics_drag_velocity_mapping_struct },
	{ _field_terminator }
};

TAG_BLOCK(
	water_physics_hull_surface_definition_block,
	sizeof(s_water_physics_hull_surface_definition),
	k_maximum_number_of_water_physics_hull_surfaces)
{
	{ _field_word_flags, "flags", &water_physics_hull_surface_flags_enum },
	{ _field_padding, "post_flags_padding", &water_physics_hull_surface_post_flags_padding  },
	{ _field_string_id, "marker_name" },
	{ _field_real, "radius" },
	{ _field_block, "material_overrides", &water_physics_material_override_struct },
	{ _field_terminator }
};
