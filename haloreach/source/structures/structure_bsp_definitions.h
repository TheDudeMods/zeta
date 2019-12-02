#pragma once

#include <cseries/cseries.h>
#include <math/real_math.h>
#include <tag_files/tag_groups.h>
#include <geometry/geometry_definitions.h>
#include <objects/object_types.h>

/* ---------- structures */

struct s_scenario_structure_bsp
{
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	short : 16;
	short : 16;
	short : 16;
	short : 16;
	s_tag_block structure_seams;
	long : 32;
	long : 32;
	long : 32;
	s_tag_block collision_materials;
	s_tag_block unknown64;
	s_tag_block unknown70;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	real_bounds world_x_bounds;
	real_bounds world_y_bounds;
	real_bounds world_z_bounds;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	s_tag_block cluster_portals;
	s_tag_block detail_objects;
	s_tag_block clusters;
	s_tag_block materials;
	s_tag_block sky_owner_cluster;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	s_tag_block background_sound_environment_palette;
	s_tag_data unknown1A0;
	s_tag_block markers;
	long : 32;
	long : 32;
	long : 32;
	s_tag_block unknown1CC;
	s_tag_block runtime_decals;
	s_tag_block environment_object_palette;
	s_tag_block environment_objects;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	s_tag_block instanced_geometry_groups;
	s_tag_block instanced_geometry_subgroups;
	long : 32;
	long : 32;
	long : 32;
	s_tag_block instanced_geometry_instances;
	s_tag_reference instanced_geometry_imposters;
	s_tag_block decorators;
	s_render_geometry geometry1;
	s_tag_block decals;
	s_tag_block decal_properties;
	s_render_geometry geometry2;
	s_tag_block unknown_sound_clusters_a;
	s_tag_block transparent_planes;
	long : 32;
	long : 32;
	long : 32;
	s_tag_block collision_mopp_codes;
	long : 32;
	real_bounds collision_x_bounds;
	real_bounds collision_y_bounds;
	real_bounds collision_z_bounds;
	s_tag_block breakable_surface_mopp_codes;
	s_tag_block breakable_surface_key_table;
	long : 32;
	long : 32;
	long : 32;
	s_render_geometry geometry3;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long : 32;
	long collision_resource_index;
	long : 32;
	long pathfinding_resource_index;
	long : 32;
	long : 32;
};
static_assert(sizeof(s_scenario_structure_bsp) == 0x544);

struct s_structure_bsp_pathfinding_object_ref_bsp2d_ref_resource
{
	long node_or_sector_ref;
};
static_assert(sizeof(s_structure_bsp_pathfinding_object_ref_bsp2d_ref_resource) == 0x4);

struct s_structure_bsp_pathfinding_object_ref_bsp_resource
{
	long bsp_index;
	short node_index;
	short unused;
	c_tag_block<s_structure_bsp_pathfinding_object_ref_bsp2d_ref_resource> bsp2d_refs;
	long vertex_offset;
};
static_assert(sizeof(s_structure_bsp_pathfinding_object_ref_bsp_resource) == 0x18);

struct s_structure_bsp_pathfinding_object_ref_resource
{
	ushort flags;
	short unused;
	c_tag_block<s_structure_bsp_pathfinding_object_ref_bsp_resource> bsps;
	long object_unique_id;
	short origin_bsp_index;
	c_enum<e_object_type, char> object_type;
	char source;
};
static_assert(sizeof(s_structure_bsp_pathfinding_object_ref_resource) == 0x18);

struct s_structure_bsp_pathfinding_tag_resources
{
	s_tag_block sectors;
	s_tag_block links;
	s_tag_block references;
	s_tag_block bsp2d_nodes;
	s_tag_block vertices;
	s_tag_block object_refs;
	s_tag_block pathfinding_hints;
	s_tag_block instanced_geometry_references;
	long structure_checksum;
	s_tag_block giant_pathfinding;
	s_tag_block seams;
	s_tag_block jump_seams;
	s_tag_block doors;
};
static_assert(sizeof(s_structure_bsp_pathfinding_tag_resources) == 0x94);

struct s_structure_bsp_cache_file_tag_resources
{
	s_tag_block surface_planes;
	s_tag_block planes;
	s_tag_block edge_to_seams;
	c_tag_block<s_structure_bsp_pathfinding_tag_resources> pathfinding_data;
};
static_assert(sizeof(s_structure_bsp_cache_file_tag_resources) == 0x30);
