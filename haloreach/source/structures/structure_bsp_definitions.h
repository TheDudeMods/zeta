#pragma once

#include <cseries/cseries.h>
#include <datatypes/enum.h>
#include <datatypes/flags.h>
#include <datatypes/static_bitarray.h>
#include <math/real_math.h>
#include <tag_files/tag_groups.h>
#include <geometry/geometry_definitions.h>

/* ---------- constants */

enum
{
	k_structure_bsp_group_tag = 'sbsp',
	k_structure_design_group_tag = 'sddt',
};

/* ---------- types */

struct s_structure_design_build_identifier
{
	long manifest_id[4];
	long build_index;
	long structure_importer_version;
};
static_assert(sizeof(s_structure_design_build_identifier) == 0x18);

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
	long unknown0[80];
	c_tag_block_index<s_mesh, short> mesh;
	c_tag_block_index<s_mesh_compression_resource, short> compression;
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
	real unknown7;
	real unknown8;
	real unknown9;
	real unknown10;
	real unknown11;
	real unknown12;
	real unknown13;
	string_id name;
};
static_assert(sizeof(s_structure_bsp_instanced_geometry_instance) == 0xA0);

struct s_structure_design_definition
{
	s_structure_design_build_identifier build_identifier;
	s_structure_design_build_identifier parent_build_identifier;
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
