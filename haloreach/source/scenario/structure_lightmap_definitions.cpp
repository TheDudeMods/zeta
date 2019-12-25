#include <scenario/structure_lightmap_definitions.h>

/* ---------- definitions */

TAG_BLOCK(
	scenario_lightmap_data_reference_block,
	sizeof(s_scenario_lightmap_data_reference),
	NONE)
{
	{ _field_tag_reference, "lightmap_data", nullptr },
	{ _field_tag_reference, "wetness_data", nullptr },
	{ _field_terminator }
};

TAG_GROUP(
	scenario_lightmap_group,
	k_scenario_lightmap_group_tag,
	sizeof(s_scenario_lightmap))
{
	{ _field_long_integer, "unknown0" },
	{ _field_block, "lightmap_data_references", &scenario_lightmap_data_reference_block },
	{ _field_block, "airprobes", nullptr },
	{ _field_block, "unknown1", nullptr },
	{ _field_block, "unknown2", nullptr },
	{ _field_block, "unknown3", nullptr },
	{ _field_block, "unknown4", nullptr },
};

extern s_struct_definition render_geometry_struct;

TAG_GROUP(
	scenario_lightmap_bsp_data_group,
	k_scenario_lightmap_bsp_data_group_tag,
	sizeof(s_scenario_lightmap_bsp_data))
{
	{ _field_short_integer, "unknown1" },
	{ _field_short_integer, "bsp_index" },
	{ _field_long_integer, "structure_checksum" },
	{ _field_tag_reference, "unknown2" },
	{ _field_real, "brightness" },
	{ _field_tag_reference, "primary_map" },
	{ _field_tag_reference, "intensity_map" },
	{ _field_block, "unknown3", nullptr },
	{ _field_block, "unknown4", nullptr },
	{ _field_block, "unknown5", nullptr },
	{ _field_block, "instanced_geometry", nullptr },
	{ _field_block, "colors", nullptr },
	{ _field_struct, "render_geometry", &render_geometry_struct },
	{ _field_block, "unknown6", nullptr },
	{ _field_block, "airprobes", nullptr },
	{ _field_block, "unknown7", nullptr },
	{ _field_block, "unknown8", nullptr },
	{ _field_block, "unknown9", nullptr },
	{ _field_block, "compile_data", nullptr },
	{ _field_terminator }
};
