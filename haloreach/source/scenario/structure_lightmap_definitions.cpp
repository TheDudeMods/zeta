#include <scenario/structure_lightmap_definitions.h>

/* ---------- definitions */

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
