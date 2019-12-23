#include <structures/structure_bsp_definitions.h>

/* ---------- definitions */

TAG_ARRAY(
	_field_long_integer,
	structure_build_identifier_manifest_id_array,
	4);

TAG_STRUCT(
	structure_build_identifier_struct,
	sizeof(s_structure_design_build_identifier))
{
	{ _field_array, "manifest_id", &structure_build_identifier_manifest_id_array },
	{ _field_long_integer, "build_index" },
	{ _field_long_integer, "structure_importer_version" },
	{ _field_terminator }
};

TAG_STRUCT(
	structure_physics_definition_struct,
	sizeof(s_structure_design_physics_definition))
{
	{ _field_long_integer, "importer_version" },
	{ _field_block, "soft_ceiling_mopp_code", nullptr }, // TODO
	{ _field_block, "soft_ceilings", nullptr }, // TODO
	{ _field_block, "water_mopp_code", nullptr }, // TODO
	{ _field_block, "water_groups", nullptr }, // TODO
	{ _field_block, "water_instances", nullptr }, // TODO
	{ _field_terminator }
};

TAG_STRUCT(
	structure_planar_fog_set_struct,
	sizeof(s_structure_design_planar_fog_set))
{
	{ _field_block, "planar_fogs", nullptr }, // TODO
	{ _field_block, "mopp_code", nullptr }, // TODO
	{ _field_terminator }
};

extern s_struct_definition render_geometry_struct;
extern s_tag_block_definition geometry_material_block;

TAG_GROUP(
	structure_design_group,
	k_structure_design_group_tag,
	sizeof(s_structure_design_definition))
{
	{ _field_struct, "build_identifier", &structure_build_identifier_struct },
	{ _field_struct, "parent_build_identifier", &structure_build_identifier_struct },
	{ _field_struct, "physics", &structure_physics_definition_struct },
	{ _field_struct, "planar_fog_set", &structure_planar_fog_set_struct },
	{ _field_struct, "render_geometry", &render_geometry_struct },
	{ _field_block, "instanced_geometry_definitions", nullptr }, // TODO
	{ _field_block, "instanced_geometry_instances", nullptr }, // TODO
	{ _field_block, "materials", &geometry_material_block },
	{ _field_long_integer, "unknown1" },
	{ _field_long_integer, "unknown2" },
	{ _field_long_integer, "unknown3" },
	{ _field_terminator }
};
