#pragma once

#include <cseries/cseries.h>
#include <datatypes/enum.h>
#include <datatypes/flags.h>
#include <math/real_math.h>
#include <tag_files/tag_groups.h>
#include <geometry/geometry_definitions.h>

/* ---------- constants */

enum
{
	k_scenario_lightmap_group_tag = 'sLdT',
	k_scenario_lightmap_bsp_data_group_tag = 'Lbsp',
};

/* ---------- types */

struct s_scenario_lightmap_data_reference
{
	s_tag_reference lightmap_data;
	s_tag_reference wetness_data;
};
static_assert(sizeof(s_scenario_lightmap_data_reference) == 0x20);

struct s_scenario_lightmap
{
	// TODO: finish
	long unknown0;
	c_tag_block<s_scenario_lightmap_data_reference> lightmap_data_references;
	s_tag_block airprobes;
	s_tag_block unknown1;
	s_tag_block unknown2;
	s_tag_block unknown3;
	s_tag_block unknown4;
};
static_assert(sizeof(s_scenario_lightmap) == 0x4C);

struct s_scenario_lightmap_bsp_data
{
	// TODO: finish
	short unknown1;
	short bsp_index;
	long structure_checksum;
	s_tag_reference unknown2;
	real brightness;
	s_tag_reference primary_map;
	s_tag_reference intensity_map;
	s_tag_block unknown3;
	s_tag_block unknown4;
	s_tag_block unknown5;
	s_tag_block instanced_geometry;
	s_tag_block colors;
	s_render_geometry render_geometry;
	s_tag_block unknown6;
	s_tag_block airprobes;
	s_tag_block unknown7;
	s_tag_block unknown8;
	s_tag_block unknown9;
	s_tag_block compile_data;
};
static_assert(sizeof(s_scenario_lightmap_bsp_data) == 0x168);
