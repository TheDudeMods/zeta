#pragma once

#include <cseries/cseries.h>
#include <datatypes/enum.h>
#include <datatypes/flags.h>
#include <datatypes/static_bitarray.h>
#include <math/real_math.h>
#include <tag_files/tag_groups.h>
#include <geometry/geometry_definitions.h>
#include <physics/collision_bsp.h>

/* ---------- constants */

enum
{
	k_structure_bsp_group_tag = 'sbsp',
	k_structure_design_group_tag = 'sddt',
};

/* ---------- types */

struct s_structure_build_identifier
{
	long manifest_id[4];
	long build_index;
	long structure_importer_version;
};
static_assert(sizeof(s_structure_build_identifier) == 0x18);

struct s_structure_design_physics_definition
{
	long importer_version;
	s_tag_block soft_ceiling_mopp_code; // TODO
	s_tag_block soft_ceilings;			// TODO
	s_tag_block water_mopp_code;		// TODO
	s_tag_block water_groups;			// TODO
	s_tag_block water_instances;		// TODO
};
static_assert(sizeof(s_structure_design_physics_definition) == 0x40);

struct s_structure_design_planar_fog_set
{
	s_tag_block planar_fogs; // TODO
	s_tag_block mopp_code; // TODO
};
static_assert(sizeof(s_structure_design_planar_fog_set) == 0x18);

struct s_structure_bsp_instanced_geometry_definition
{
	long checksum;
	real_point3d bounding_sphere_offset;
	real bounding_sphere_radius;
	s_collision_bsp collision_bsp;
	s_tag_block unknown1;
	s_tag_block unknown2;
	s_tag_block unknown3;
	s_tag_block unknown4;
	s_tag_block unknown5;
	s_tag_block unknown6;
	s_tag_block unknown7;
	s_tag_block unknown8;
	s_tag_block unknown9;
	s_tag_block unknown10;
	s_tag_block unknown11;
	s_tag_block unknown12;
	s_tag_block unknown13;
	s_tag_block unknown14;
	s_tag_block unknown15;
	s_tag_block unknown16;
	c_tag_block_index<s_mesh, short> mesh;
	c_tag_block_index<s_compression_info, short> compression;
};
static_assert(sizeof(s_structure_bsp_instanced_geometry_definition) == 0x144);

enum e_structure_bsp_instance_geometry_instance_flags
{
	_instanced_geometry_instance_contains_split_lighting_parts_bit,
	_instanced_geometry_instance_render_only_bit,
	_instanced_geometry_instance_does_not_block_aoe_damage_bit,
	_instanced_geometry_instance_collidable_bit,
	_instanced_geometry_instance_contains_decal_parts_bit,
	_instanced_geometry_instance_contains_water_parts_bit,
	_instanced_geometry_instance_negative_scale_bit,
	_instanced_geometry_instance_outside_map_bit,
	_instanced_geometry_instance_seam_colliding_bit,
	_instanced_geometry_instance_contains_deferred_reflections_bit,
	_instanced_geometry_instance_remove_from_shadow_geometry_bit,
	_instanced_geometry_instance_cinema_only_bit,
	_instanced_geometry_instance_exclude_from_cinema_bit,
	_instanced_geometry_instance_disable_fx_bit,
	_instanced_geometry_instance_disable_play_collision_bit,
	_instanced_geometry_instance_disable_bullet_collision_bit,
	k_number_of_structure_bsp_instance_geometry_instance_flags
};

struct s_structure_bsp_instanced_geometry_instance
{
	real_matrix4x3 matrix;
	c_tag_block_index<s_structure_bsp_instanced_geometry_definition, short> instance_definition;
	c_flags<e_structure_bsp_instance_geometry_instance_flags, ushort> flags;
	c_tag_block_index<s_mesh, short> mesh;
	c_tag_block_index<s_mesh_compression_resource, short> compression;
	long seam_bitvector[4];
	real_bounds x_bounds;
	real_bounds y_bounds;
	real_bounds z_bounds;
	real_point3d world_bounding_sphere_center;
	real world_bounding_sphere_radius;
	real unknown1;
	real unknown2;
	char unknown3;
	char unknown4;
	char unknown5;
	char unknown6;
	long unknown7;
	long unknown8;
	long unknown9;
	long unknown10;
	long unknown11;
	long unknown12;
	long unknown13;
	string_id name;
};
static_assert(sizeof(s_structure_bsp_instanced_geometry_instance) == 0xA0);

struct s_structure_design_definition
{
	s_structure_build_identifier build_identifier;
	s_structure_build_identifier parent_build_identifier;
	s_structure_design_physics_definition physics;
	s_structure_design_planar_fog_set planar_fog_set;

	/* ------ rain */

	s_render_geometry render_geometry;
	c_tag_block<s_structure_bsp_instanced_geometry_definition> instanced_geometry_definitions;
	c_tag_block<s_structure_bsp_instanced_geometry_instance> instanced_geometry_instances;
	c_tag_block<s_geometry_material> materials;

	long unknown1;
	long unknown2;
	long unknown3;
};
static_assert(sizeof(s_structure_design_definition) == 0x160);

enum e_structure_bsp_definition_flags
{
	_structure_bsp_has_instance_groups_bit,
	_structure_bsp_surface_to_triangle_mapping_remapped_bit,
	_structure_bsp_external_references_converted_to_io_bit,
	_structure_bsp_structure_mopp_needs_rebuilt_bit,
	_structure_bsp_structure_prefab_materials_need_postprocessing_bit,
	_structure_bsp_serialized_havok_data_converted_to_target_platform_bit,
	_structure_bsp_is_prefab_bit,
	_structure_bsp_collision_geometry_is_over_double_the_budget_bit,
	k_number_of_structure_bsp_definition_flags
};

enum e_structure_bsp_content_policy_flags
{
	_structure_bsp_has_working_pathfinding_bit,
	_structure_bsp_convex_decomposition_enabled_bit,
	k_number_of_structure_bsp_content_policy_flags
};

struct s_structure_bsp_cluster;

struct s_structure_seam_identifier
{
	long guid[4];
};
static_assert(sizeof(s_structure_seam_identifier) == 0x10);

struct s_structure_seam_edge_mapping
{
	long structure_edge_index;
};
static_assert(sizeof(s_structure_seam_edge_mapping) == 0x4);

struct s_structure_seam_cluster_mapping
{
	c_tag_block_index<s_structure_bsp_cluster, long> cluster;
	real_point3d cluster_center;
};
static_assert(sizeof(s_structure_seam_cluster_mapping) == 0x10);

struct s_structure_seam_mapping
{
	s_structure_seam_identifier seams_identifier;
	c_tag_block<s_structure_seam_edge_mapping> edge_mapping;
	c_tag_block<s_structure_seam_cluster_mapping> cluster_mapping;
};
static_assert(sizeof(s_structure_seam_mapping) == 0x28);

struct s_structure_seam_to_edge_mapping
{
	short seam_index;
	short structure_edge_index;
};
static_assert(sizeof(s_structure_seam_to_edge_mapping) == 0x4);

enum e_structure_collision_material_flags
{
	_structure_collision_material_is_seam_bit,
	k_number_of_structure_collision_material_flags
};

struct s_structure_collision_material
{
	s_tag_reference render_method;
	short global_material; // TODO: block index
	short conveyor_surface; // TODO: block index
	c_tag_block_index<s_structure_seam_mapping, short> seam_mapping;
	c_flags<e_structure_collision_material_flags, ushort> flags;
};
static_assert(sizeof(s_structure_collision_material) == 0x18);

struct s_structure_bsp_leaf
{
	c_tag_block_index<s_structure_bsp_cluster, uchar> cluster;
};
static_assert(sizeof(s_structure_bsp_leaf) == 0x1);

struct s_structure_bsp_plane
{
	short unknown;
	c_tag_block_index<s_structure_bsp_cluster, short> cluster;
};
static_assert(sizeof(s_structure_bsp_plane) == 0x4);

struct s_structure_bsp_surface
{
	c_tag_block_index<s_structure_bsp_plane, long> first_plane;
	long plane_count;
};
static_assert(sizeof(s_structure_bsp_surface) == 0x8);

struct s_structure_bsp_detail_object
{
	long unknown0;
	long unknown4;
	long unknown8;
	long unknownC;
	long unknown10;
	long unknown14;
	long unknown18;
	long unknown1C;
	long unknown20;
	long unknown24;
	long unknown28;
	long unknown2C;
	long unknown30;
};
static_assert(sizeof(s_structure_bsp_detail_object) == 0x34);

enum e_structure_bsp_cluster_portal_flags
{
	_structure_bsp_cluster_portal_deafen_ai_bit = 0,
	_structure_bsp_cluster_portal_one_way_bit = 1,
	_structure_bsp_cluster_portal_door_bit = 2,
	_structure_bsp_cluster_portal_no_way_bit = 3,
	_structure_bsp_cluster_portal_one_way_reversed_bit = 4,
	_structure_bsp_cluster_portal_deafen_everything_bit = 5,
	k_number_of_structure_bsp_cluster_portal_flags
};

struct s_structure_bsp_cluster_portal_vertex
{
	real_point3d point;
};
static_assert(sizeof(s_structure_bsp_cluster_portal_vertex) == 0xC);

struct s_oriented_bounds
{
	real_point3d center;
	real_vector3d extents;
	real_quaternion orientation;
};
static_assert(sizeof(s_oriented_bounds) == 0x28);

struct s_structure_bsp_cluster_portal
{
	s_oriented_bounds oriented_bounds;
	c_tag_block_index<s_structure_bsp_cluster, short> back_cluster;
	c_tag_block_index<s_structure_bsp_cluster, short> front_cluster;
	c_tag_block_index<s_structure_bsp_plane, long> plane;
	real_point3d centroid;
	real bounding_radius;
	c_flags<e_structure_bsp_cluster_portal_flags, ulong> flags;
	c_tag_block<s_structure_bsp_cluster_portal_vertex> vertices;
};
static_assert(sizeof(s_structure_bsp_cluster_portal) == 0x50);

struct s_structure_bsp_cluster_portal_index
{
	short portal_index; // TODO: block index
};
static_assert(sizeof(s_structure_bsp_cluster_portal_index) == 0x2);

struct s_structure_bsp_cluster_seam_index
{
	short seam_index; // TODO: block index
};
static_assert(sizeof(s_structure_bsp_cluster_seam_index));

struct s_structure_bsp_cluster
{
	real_bounds x_bounds;
	real_bounds y_bounds;
	real_bounds z_bounds;
	char unknown1; // TODO: block index
	char sky_index; // TODO: block index
	char camera_effect_index; // TODO: block index
	char unknown2; // TODO: block index
	short unknown3;
	short unknown4;
	short runtime_decal_start_index;
	short runtime_decal_entry_count;
	short unknown5;
	short unknown6;
	short unknown7;
	short unknown8;
	short unknown9;
	short unknown10;
	long unknown11;
	c_tag_block<s_structure_bsp_cluster_portal_index> portals;
	c_tag_block_index<s_mesh, short> mesh;
	short instance_imposter_cluster_mopp_index; // TODO: block index
	c_tag_block<s_structure_bsp_cluster_seam_index> seam_indices;
	// TODO: finish
	s_tag_block decorator_grids;
	long unknown12;
	long unknown13;
	long unknown14;
	long unknown15;
	long unknown16;
	long unknown17;
	s_tag_block unknown18;
	s_tag_block unknown19;
};
static_assert(sizeof(s_structure_bsp_cluster) == 0x8C);

struct s_structure_bsp_sky_owner_cluster
{
	c_tag_block_index<s_structure_bsp_cluster, short> owner_cluster;
};
static_assert(sizeof(s_structure_bsp_sky_owner_cluster) == 0x2);

struct s_structure_bsp_instanced_geometry_name
{
	string_id name;
};
static_assert(sizeof(s_structure_bsp_instanced_geometry_name) == 0x4);

struct s_structure_bsp_instanced_geometry_name_index
{
	c_tag_block_index<s_structure_bsp_instanced_geometry_name, short> name;
};
static_assert(sizeof(s_structure_bsp_instanced_geometry_name_index) == 0x2);

struct s_structure_bsp_instanced_geometry_subgroup
{
	real_point3d position;
	real unknownC;
	short unknown10;
	short unknown12;
	real unknown14;
	real unknown18;
	c_tag_block<s_structure_bsp_instanced_geometry_name_index> members;
};
static_assert(sizeof(s_structure_bsp_instanced_geometry_subgroup) == 0x28);

enum e_structure_bsp_instanced_geometry_group_flags
{
	_structure_bsp_instanced_geometry_group_visible_bit,
	k_number_of_structure_bsp_instanced_geometry_group_flags
};

struct s_structure_bsp_instanced_geometry_subgroup_index
{
	c_tag_block_index<s_structure_bsp_instanced_geometry_subgroup, short> subgroup;
};
static_assert(sizeof(s_structure_bsp_instanced_geometry_subgroup_index) == 0x2);

struct s_structure_bsp_instanced_geometry_group
{
	c_flags<e_structure_bsp_instanced_geometry_group_flags, ulong> flags;
	c_tag_block<s_structure_bsp_instanced_geometry_subgroup_index> members;
};
static_assert(sizeof(s_structure_bsp_instanced_geometry_group) == 0x10);

struct s_structure_bsp_definition
{
	s_structure_build_identifier build_identifier;
	s_structure_build_identifier parent_build_identifier;
	long import_info_checksum;
	long import_version;
	c_flags<e_structure_bsp_definition_flags, ushort> flags;
	c_flags<e_structure_bsp_content_policy_flags, ushort> content_policy_flags;
	c_flags<e_structure_bsp_content_policy_flags, ushort> failed_content_policy_flags;
	short unused1;
	c_tag_block<s_structure_seam_mapping> seam_identifiers;
	c_tag_block<s_structure_seam_to_edge_mapping> seam_to_edge_mapping;
	c_tag_block<s_structure_collision_material> collision_materials;
	c_tag_block<s_structure_bsp_leaf> leaves;
	s_tag_block unknown1;
	long unknown2[29];
	real_bounds world_bounds_x;
	real_bounds world_bounds_y;
	real_bounds world_bounds_z;
	c_tag_block<s_structure_bsp_surface> surfaces;
	c_tag_block<s_structure_bsp_plane> planes;
	c_tag_block<s_structure_bsp_cluster_portal> cluster_portals;
	c_tag_block<s_structure_bsp_detail_object> detail_objects;
	c_tag_block<s_structure_bsp_cluster> clusters;
	c_tag_block<s_geometry_material> materials;
	c_tag_block<s_structure_bsp_sky_owner_cluster> sky_owner_cluster;
	long unknown3[15];
	s_tag_block background_sound_environment_palette;
	s_tag_data unknown4;
	s_tag_block markers;
	s_tag_block unknown5;
	s_tag_block unknown6;
	s_tag_block runtime_decals;
	s_tag_block environment_object_palette;
	s_tag_block environment_objects;
	long unknown7[16];
	c_tag_block<s_structure_bsp_instanced_geometry_group> instanced_geometry_groups;
	c_tag_block<s_structure_bsp_instanced_geometry_subgroup> instanced_geometry_subgroups;
	long unknown8;
	long unknown9;
	c_tag_block<s_structure_bsp_instanced_geometry_name> instanced_geometry_instances;
	s_tag_reference instanced_geometry_imposters;
	s_tag_block decorators;
	long unknown10;
	s_render_geometry decorator_geometry;
	s_tag_block decals;
	s_tag_block decal_properties;
	s_render_geometry decal_geometry;
	s_tag_block unknown_sound_clusters_a;
	s_tag_block transparent_planes;
	s_tag_block unknown11;
	s_tag_block collision_mopp_codes;
	long unknown12;
	real_bounds collision_bounds_x;
	real_bounds collision_bounds_y;
	real_bounds collision_bounds_z;
	s_tag_block breakable_surface_mopp_codes;
	s_tag_block breakable_surface_key_table;
	s_tag_block unknown13;
	s_render_geometry render_geometry;
	s_tag_block unknown14;
	s_tag_block unknown15;
	s_tag_block unknown16;
	long tag_resources_index;
	long unused2;
	long cache_file_tag_resources_index;
	long unused3;
	long unknown17;
	long unknown18;
};
static_assert(sizeof(s_structure_bsp_definition) == 0x548);

struct s_structure_bsp_tag_resources
{
	c_tag_block<s_collision_bsp> collision_bsp;
	s_tag_block large_collision_bsp;
	c_tag_block<s_structure_bsp_instanced_geometry_definition> instanced_geometry_definitions;
};
static_assert(sizeof(s_structure_bsp_tag_resources) == 0x24);

struct s_structure_bsp_resource_instanced_geometry_instance
{
	real_matrix4x3 matrix;
	c_tag_block_index<s_structure_bsp_instanced_geometry_definition, short> instance_definition;
	c_flags<e_structure_bsp_instance_geometry_instance_flags, ushort> flags;
	c_tag_block_index<s_mesh, short> mesh;
	c_tag_block_index<s_mesh_compression_resource, short> compression;
	long seam_bitvector[4];
	real_bounds x_bounds;
	real_bounds y_bounds;
	real_bounds z_bounds;
	real_point3d world_bounding_sphere_center;
	real world_bounding_sphere_radius;
	real unknown1;
	real unknown2;
	char unknown3;
	char unknown4;
	char unknown5;
	char unknown6;
	long unknown7;
	long unknown8;
	long unknown9;
	long unknown10;
	long unknown11;
	long unknown12;
	long unknown13;
};
static_assert(sizeof(s_structure_bsp_resource_instanced_geometry_instance) == 0x9C);

struct s_structure_bsp_cache_file_tag_resources
{
	c_tag_block<s_structure_bsp_surface> surfaces;
	c_tag_block<s_structure_bsp_plane> planes;
	c_tag_block<s_structure_seam_to_edge_mapping> edges_to_seams;
	s_tag_block pathfinding_data;
	s_tag_block unknown1;
	s_tag_block unknown2;
	c_tag_block<s_structure_bsp_resource_instanced_geometry_instance> instanced_geometry_instances;
	s_tag_block unknown3;
	s_tag_block unknown4;
	s_tag_block unknown5;
};
static_assert(sizeof(s_structure_bsp_cache_file_tag_resources) == 0x78);
