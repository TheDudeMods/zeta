#include <structures/structure_bsp_definitions.h>

/* ---------- definitions */

TAG_ARRAY(
	_field_long_integer,
	structure_build_identifier_manifest_id_array,
	4);

TAG_STRUCT(
	structure_build_identifier_struct,
	sizeof(s_structure_build_identifier))
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

TAG_ENUM(
	structure_bsp_definition_flags_enum,
	k_number_of_structure_bsp_definition_flags)
{
	{ "has_instance_groups", _structure_bsp_has_instance_groups_bit },
	{ "surface_to_triangle_mapping_remapped", _structure_bsp_surface_to_triangle_mapping_remapped_bit },
	{ "external_references_converted_to_io", _structure_bsp_external_references_converted_to_io_bit },
	{ "structure_mopp_needs_rebuilt", _structure_bsp_structure_mopp_needs_rebuilt_bit },
	{ "structure_prefab_materials_need_postprocessing", _structure_bsp_structure_prefab_materials_need_postprocessing_bit },
	{ "serialized_havok_data_converted_to_target_platform", _structure_bsp_serialized_havok_data_converted_to_target_platform_bit },
	{ "is_prefab", _structure_bsp_is_prefab_bit },
	{ "collision_geometry_is_over_double_the_budget", _structure_bsp_collision_geometry_is_over_double_the_budget_bit },
};

TAG_ENUM(
	structure_bsp_content_policy_flags_enum,
	k_number_of_structure_bsp_content_policy_flags)
{
	{ "bsp_has_working_pathfinding", _structure_bsp_has_working_pathfinding_bit },
	{ "bsp_convex_decomposition_enabled", _structure_bsp_convex_decomposition_enabled_bit },
};

TAG_PAD(
	_field_short_integer,
	structure_bsp_post_failed_content_policy_flags_pad,
	1);

TAG_ARRAY(
	_field_long_integer,
	structure_seam_identifier_guid_array,
	4);

TAG_BLOCK(
	structure_seam_identifier_block,
	sizeof(s_structure_seam_identifier),
	NONE)
{
	{ _field_array, "guid", &structure_seam_identifier_guid_array },
	{ _field_terminator }
};

TAG_BLOCK(
	structure_seam_edge_mapping_block,
	sizeof(s_structure_seam_edge_mapping),
	NONE)
{
	{ _field_long_integer, "structure_edge_index" },
	{ _field_terminator }
};

extern s_tag_block_definition structure_bsp_cluster_block;

TAG_BLOCK(
	structure_seam_cluster_mapping_block,
	sizeof(s_structure_seam_cluster_mapping),
	NONE)
{
	{ _field_long_block_index, "cluster", &structure_bsp_cluster_block },
	{ _field_real_point3d, "cluster_center" },
	{ _field_terminator }
};

TAG_BLOCK(
	structure_seam_mapping_block,
	sizeof(s_structure_seam_mapping),
	NONE)
{
	{ _field_struct, "seams_identifier", &structure_seam_identifier_block },
	{ _field_block, "edge_mapping", &structure_seam_edge_mapping_block },
	{ _field_block, "cluster_mapping", &structure_seam_cluster_mapping_block },
	{ _field_terminator }
};

TAG_BLOCK(
	structure_seam_to_edge_mapping_block,
	sizeof(s_structure_seam_to_edge_mapping),
	NONE)
{
	{ _field_short_integer, "seam_index" },
	{ _field_short_integer, "structure_edge_index" },
	{ _field_terminator }
};

TAG_ENUM(
	structure_collision_material_flags_enum,
	k_number_of_structure_collision_material_flags)
{
	{ "is_seam", _structure_collision_material_is_seam_bit },
};

TAG_BLOCK(
	structure_collision_material_block,
	sizeof(s_structure_collision_material),
	NONE)
{
	{ _field_tag_reference, "render_method" },
	{ _field_short_integer, "global_material" },
	{ _field_short_integer, "conveyor_surface" },
	{ _field_short_block_index, "seam_mapping", &structure_seam_mapping_block },
	{ _field_word_flags, "flags", &structure_collision_material_flags_enum },
	{ _field_terminator }
};

TAG_BLOCK(
	structure_bsp_leaf_block,
	sizeof(s_structure_bsp_leaf),
	NONE)
{
	{ _field_char_block_index, "cluster", &structure_bsp_cluster_block },
	{ _field_terminator }
};

TAG_BLOCK(
	structure_bsp_plane_block,
	sizeof(s_structure_bsp_plane),
	NONE)
{
	{ _field_short_integer, "unknown" },
	{ _field_short_block_index, "cluster", &structure_bsp_cluster_block },
	{ _field_terminator }
};

TAG_BLOCK(
	structure_bsp_surface_block,
	sizeof(s_structure_bsp_surface),
	NONE)
{
	{ _field_long_block_index, "first_plane", &structure_bsp_plane_block },
	{ _field_long_integer, "plane_count" },
	{ _field_terminator }
};

TAG_BLOCK(
	structure_bsp_detail_object_block,
	sizeof(s_structure_bsp_detail_object),
	NONE)
{
	{ _field_long_integer, "unknown0" },
	{ _field_long_integer, "unknown4" },
	{ _field_long_integer, "unknown8" },
	{ _field_long_integer, "unknownC" },
	{ _field_long_integer, "unknown10" },
	{ _field_long_integer, "unknown14" },
	{ _field_long_integer, "unknown18" },
	{ _field_long_integer, "unknown1C" },
	{ _field_long_integer, "unknown20" },
	{ _field_long_integer, "unknown24" },
	{ _field_long_integer, "unknown28" },
	{ _field_long_integer, "unknown2C" },
	{ _field_long_integer, "unknown30" },
	{ _field_terminator }
};

TAG_ENUM(
	structure_bsp_cluster_portal_flags_enum,
	k_number_of_structure_bsp_cluster_portal_flags)
{
	{ "deafen_ai", _structure_bsp_cluster_portal_deafen_ai_bit },
	{ "one_way", _structure_bsp_cluster_portal_one_way_bit },
	{ "door", _structure_bsp_cluster_portal_door_bit },
	{ "no_way", _structure_bsp_cluster_portal_no_way_bit },
	{ "one_way_reversed", _structure_bsp_cluster_portal_one_way_reversed_bit },
	{ "deafen_everything", _structure_bsp_cluster_portal_deafen_everything_bit },
};

TAG_BLOCK(
	structure_bsp_cluster_portal_vertex_block,
	sizeof(s_structure_bsp_cluster_portal_vertex),
	NONE)
{
	{ _field_real_point3d, "point" },
	{ _field_terminator }
};

TAG_STRUCT(
	oriented_bounds_struct,
	sizeof(s_oriented_bounds))
{
	{ _field_real_point3d, "center" },
	{ _field_real_vector3d, "extents" },
	{ _field_real_quaternion, "orientation" },
	{ _field_terminator }
};

TAG_BLOCK(
	structure_bsp_cluster_portal_block,
	sizeof(s_structure_bsp_cluster_portal),
	NONE)
{
	{ _field_struct, "oriented_bounds", &oriented_bounds_struct },
	{ _field_short_block_index, "back_cluster", &structure_bsp_cluster_block },
	{ _field_short_block_index, "front_cluster", &structure_bsp_cluster_block },
	{ _field_long_block_index, "plane", &structure_bsp_plane_block },
	{ _field_real_point3d, "centroid" },
	{ _field_real, "bounding_radius" },
	{ _field_long_flags, "flags", &structure_bsp_cluster_portal_flags_enum },
	{ _field_block, "vertices", &structure_bsp_cluster_portal_vertex_block },
	{ _field_terminator }
};

TAG_BLOCK(
	structure_bsp_cluster_portal_index_block,
	sizeof(s_structure_bsp_cluster_portal_index),
	NONE)
{
	{ _field_short_integer, "portal_index" },
	{ _field_terminator }
};

TAG_BLOCK(
	structure_bsp_cluster_seam_index_block,
	sizeof(s_structure_bsp_cluster_seam_index),
	NONE)
{
	{ _field_short_integer, "seam_index" },
	{ _field_terminator }
};

extern s_tag_block_definition mesh_block;

TAG_BLOCK(
	structure_bsp_cluster_block,
	sizeof(s_structure_bsp_cluster),
	NONE)
{
	{ _field_real_bounds, "x_bounds" },
	{ _field_real_bounds, "y_bounds" },
	{ _field_real_bounds, "z_bounds" },
	{ _field_char_integer, "unknown1" },
	{ _field_char_integer, "sky_index" },
	{ _field_char_integer, "camera_effect_index" },
	{ _field_char_integer, "unknown2" },
	{ _field_short_integer, "unknown3" },
	{ _field_short_integer, "unknown4" },
	{ _field_short_integer, "runtime_decal_start_index" },
	{ _field_short_integer, "runtime_decal_entry_count" },
	{ _field_short_integer, "unknown5" },
	{ _field_short_integer, "unknown6" },
	{ _field_short_integer, "unknown7" },
	{ _field_short_integer, "unknown8" },
	{ _field_short_integer, "unknown9" },
	{ _field_short_integer, "unknown10" },
	{ _field_long_integer, "unknown11" },
	{ _field_block, "portals", &structure_bsp_cluster_portal_index_block },
	{ _field_short_block_index, "mesh", &mesh_block },
	{ _field_short_integer, "instance_imposter_cluster_mopp_index" },
	{ _field_block, "seam_indices", &structure_bsp_cluster_seam_index_block },
	{ _field_block, "decorator_grids", nullptr },
	{ _field_long_integer, "unknown12" },
	{ _field_long_integer, "unknown13" },
	{ _field_long_integer, "unknown14" },
	{ _field_long_integer, "unknown15" },
	{ _field_long_integer, "unknown16" },
	{ _field_long_integer, "unknown17" },
	{ _field_block, "unknown18", nullptr },
	{ _field_block, "unknown19", nullptr },
	{ _field_terminator }
};

TAG_BLOCK(
	structure_bsp_sky_owner_cluster_block,
	sizeof(s_structure_bsp_sky_owner_cluster),
	NONE)
{
	{ _field_short_block_index, "owner_cluster", &structure_bsp_cluster_block },
	{ _field_terminator }
};

TAG_ARRAY(
	_field_long_integer,
	structure_bsp_unknown2_array,
	29);

TAG_ARRAY(
	_field_long_integer,
	structure_bsp_unknown3_array,
	15);

TAG_ARRAY(
	_field_long_integer,
	structure_bsp_unknown7_array,
	16);

TAG_BLOCK(
	structure_bsp_instanced_geometry_name_block,
	sizeof(s_structure_bsp_instanced_geometry_name),
	NONE)
{
	{ _field_string_id, "name" },
	{ _field_terminator }
};

TAG_BLOCK(
	structure_bsp_instanced_geometry_name_index_block,
	sizeof(s_structure_bsp_instanced_geometry_name_index),
	NONE)
{
	{ _field_short_block_index, "instance", &structure_bsp_instanced_geometry_name_block},
	{ _field_terminator }
};

TAG_BLOCK(
	structure_bsp_instanced_geometry_subgroup_block,
	sizeof(s_structure_bsp_instanced_geometry_subgroup),
	NONE)
{
	{ _field_real_point3d, "position" },
	{ _field_real, "unknownC" },
	{ _field_short_integer, "unknown10" },
	{ _field_short_integer, "unknown12" },
	{ _field_real, "unknown14" },
	{ _field_real, "unknown18" },
	{ _field_block, "members", &structure_bsp_instanced_geometry_name_index_block },
	{ _field_terminator }
};

TAG_ENUM(
	structure_bsp_instanced_geometry_group_flags_enum,
	k_number_of_structure_bsp_instanced_geometry_group_flags)
{
	{ "visible", _structure_bsp_instanced_geometry_group_visible_bit },
};

TAG_BLOCK(
	structure_bsp_instanced_geometry_subgroup_index_block,
	sizeof(s_structure_bsp_instanced_geometry_subgroup_index),
	NONE)
{
	{ _field_short_block_index, "subgroup", &structure_bsp_instanced_geometry_subgroup_block },
	{ _field_terminator }
};

TAG_BLOCK(
	structure_bsp_instanced_geometry_group_block,
	sizeof(s_structure_bsp_instanced_geometry_group),
	NONE)
{
	{ _field_long_flags, "flags", &structure_bsp_instanced_geometry_group_flags_enum },
	{ _field_block, "members", &structure_bsp_instanced_geometry_subgroup_index_block },
	{ _field_terminator }
};

TAG_GROUP(
	structure_bsp_group,
	k_structure_bsp_group_tag,
	sizeof(s_structure_bsp_definition))
{
	{ _field_struct, "build_identifier", &structure_build_identifier_struct },
	{ _field_struct, "parent_build_identifier", &structure_build_identifier_struct },
	{ _field_long_integer, "import_info_checksum" },
	{ _field_long_integer, "import_version" },
	{ _field_word_flags, "flags", &structure_bsp_definition_flags_enum },
	{ _field_word_flags, "content_policy_flags", &structure_bsp_content_policy_flags_enum },
	{ _field_word_flags, "failed_content_policy_flags", &structure_bsp_content_policy_flags_enum },
	{ _field_short_integer, "unused1" },
	{ _field_block, "seam_identifiers", &structure_seam_mapping_block },
	{ _field_block, "seam_to_edge_mapping", &structure_seam_to_edge_mapping_block },
	{ _field_block, "collision_materials", &structure_collision_material_block },
	{ _field_block, "leaves", &structure_bsp_leaf_block },
	{ _field_block, "unknown1", nullptr },
	{ _field_array, "unknown2", &structure_bsp_unknown2_array },
	{ _field_real_bounds, "world_bounds_x" },
	{ _field_real_bounds, "world_bounds_y" },
	{ _field_real_bounds, "world_bounds_z" },
	{ _field_block, "surfaces", &structure_bsp_surface_block },
	{ _field_block, "planes", &structure_bsp_plane_block },
	{ _field_block, "cluster_portals", &structure_bsp_cluster_portal_block },
	{ _field_block, "detail_objects", &structure_bsp_detail_object_block },
	{ _field_block, "clusters", &structure_bsp_cluster_block },
	{ _field_block, "materials", &geometry_material_block },
	{ _field_block, "sky_owner_cluster", &structure_bsp_sky_owner_cluster_block },
	{ _field_array, "unknown3", &structure_bsp_unknown3_array },
	{ _field_block, "background_sound_environment_palette", nullptr },
	{ _field_data, "unknown4" },
	{ _field_block, "markers", nullptr },
	{ _field_block, "unknown5", nullptr },
	{ _field_block, "unknown6", nullptr },
	{ _field_block, "runtime_decals", nullptr },
	{ _field_block, "environment_object_palette", nullptr },
	{ _field_block, "environment_objects", nullptr },
	{ _field_array, "unknown7", &structure_bsp_unknown7_array },
	{ _field_block, "instanced_geometry_groups", &structure_bsp_instanced_geometry_group_block },
	{ _field_block, "instanced_geometry_subgroups", &structure_bsp_instanced_geometry_subgroup_block },
	{ _field_long_integer, "unknown8" },
	{ _field_long_integer, "unknown9" },
	{ _field_block, "instanced_geometry_instances", &structure_bsp_instanced_geometry_name_block },
	{ _field_tag_reference, "instanced_geometry_imposters" },
	{ _field_block, "decorators", nullptr },
	{ _field_long_integer, "unknown10" },
	{ _field_struct, "decorator_geometry", &render_geometry_struct },
	{ _field_block, "decals", nullptr },
	{ _field_block, "decal_properties", nullptr },
	{ _field_struct, "decal_geometry", &render_geometry_struct },
	{ _field_block, "unknown_sound_clusters_a", nullptr },
	{ _field_block, "transparent_planes", nullptr },
	{ _field_block, "unknown11", nullptr },
	{ _field_block, "collision_mopp_codes", nullptr },
	{ _field_long_integer, "unknown12" },
	{ _field_real_bounds, "collision_bounds_x" },
	{ _field_real_bounds, "collision_bounds_y" },
	{ _field_real_bounds, "collision_bounds_z" },
	{ _field_block, "breakable_surface_mopp_codes", nullptr },
	{ _field_block, "breakable_surface_key_table", nullptr },
	{ _field_block, "unknown13", nullptr },
	{ _field_struct, "render_geometry", &render_geometry_struct },
	{ _field_block, "unknown14", nullptr },
	{ _field_block, "unknown15", nullptr },
	{ _field_block, "unknown16", nullptr },
	{ _field_long_integer, "collision_resource_index" },
	{ _field_long_integer, "unused2" },
	{ _field_long_integer, "pathfinding_resource_index" },
	{ _field_long_integer, "unused3" },
	{ _field_long_integer, "unknown17" },
	{ _field_long_integer, "unknown18" },
	{ _field_terminator }
};
