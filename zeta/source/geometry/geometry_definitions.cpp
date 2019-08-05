#include <geometry/geometry_definitions.h>
#include <render/render_methods.h>

/* ---------- definitions */

TAG_ENUM(
    render_geometry_runtime_flags_enum,
	k_number_of_render_geometry_runtime_flags)
{
	{ "geometry_processed", _render_geometry_processed_bit },
	{ "geometry_available", _render_geometry_available_bit },
	{ "geometry_has_valid_budgets", _render_geometry_has_valid_budgets_bit },
	{ "geometry_manual_resource_creation", _render_geometry_manual_resource_creation_bit },
	{ "geometry_keep_raw_geometry", _render_geometry_keep_raw_geometry_bit },
	{ "geometry_dont_use_compressed_vertex_positions", _render_geometry_dont_use_compressed_vertex_positions_bit },
	{ "geometry_pca_animation_table_sorted", _render_geometry_pca_animation_table_sorted_bit },
	{ "geometry_has_dual_quat", _render_geometry_has_dual_quat_bit },
};

TAG_ENUM(
    part_type_enum,
	k_number_of_part_types)
{
	{ "not_drawn", _part_not_drawn },
	{ "opaque_shadow_only", _part_opaque_shadow_only },
	{ "opaque_shadow_casting", _part_opaque_shadow_casting },
	{ "opaque_nonshadowing", _part_opaque_nonshadowing },
	{ "transparent", _part_transparent },
	{ "lightmap_only", _part_lightmap_only },
};

TAG_ENUM(
    specialized_render_type_enum,
	k_number_of_specialized_render_types)
{
	{ "none", _specialized_render_none },
	{ "fail", _specialized_render_fail },
	{ "fur", _specialized_render_fur },
	{ "fur_stencil", _specialized_render_fur_stencil },
	{ "decal", _specialized_render_decal },
	{ "shield", _specialized_render_shield },
	{ "water", _specialized_render_water },
	{ "hologram", _specialized_render_hologram },
	{ "split_lighting", _specialized_render_split_lighting },
	{ "deferred_reflection", _specialized_render_deferred_reflection },
};

TAG_ENUM(
    part_flags_enum,
	k_number_of_part_flags)
{
	{ "is_water_surface", _part_is_water_surface_bit },
	{ "per_vertex_lightmap_part", _part_per_vertex_lightmap_part_bit },
	{ "render_in_z_prepass", _part_render_in_z_prepass_bit },
	{ "can_be_rendered_in_draw_bundles", _part_can_be_rendered_in_draw_bundles_bit },
	{ "draw_cull_distance_medium", _part_draw_cull_distance_medium_bit },
	{ "draw_cull_distance_close", _part_draw_cull_distance_close_bit },
	{ "draw_cull_rendering_shields", _part_draw_cull_rendering_shields_bit },
	{ "unused3", _part_unused3_bit },
	{ "unused4", _part_unused4_bit },
	{ "unused5", _part_unused5_bit },
	{ "transparent_should_output_depth_for_dof", _part_transparent_should_output_depth_for_dof_bit },
	{ "do_not_include_in_static_lightmap", _part_do_not_include_in_static_lightmap_bit },
	{ "do_not_include_in_pvs_generation", _part_do_not_include_in_pvs_generation_bit },
	{ "draw_cull_rendering_active_camo", _part_draw_cull_rendering_active_camo_bit },
};

TAG_ENUM(
    mesh_flags_enum,
	k_number_of_mesh_flags)
{
	{ "has_vertex_color", _mesh_has_vertex_color_bit },
	{ "use_region_index_for_sorting", _mesh_use_region_index_for_sorting_bit },
	{ "can_be_rendered_in_draw_bundles", _mesh_can_be_rendered_in_draw_bundles_bit },
	{ "is_custom_shadow_caster", _mesh_is_custom_shadow_caster_bit },
	{ "is_unindexed", _mesh_is_unindexed_bit },
	{ "mash_should_render_in_z_prepass", _mesh_mash_should_render_in_z_prepass_bit },
	{ "has_water", _mesh_has_water_bit },
	{ "has_decal", _mesh_has_decal_bit },
};

TAG_ENUM(
    prt_type_enum,
	k_number_of_prt_types)
{
	{ "none", _prt_type_none },
	{ "ambient", _prt_type_ambient },
	{ "linear", _prt_type_linear },
	{ "quadratic", _prt_type_quadratic },
};

TAG_ENUM(
    vertex_type_enum,
	k_number_of_vertex_types)
{
	{ "world", _vertex_type_world },
	{ "rigid", _vertex_type_rigid },
	{ "skinned", _vertex_type_skinned },
	{ "particle_model", _vertex_type_particle_model },
	{ "flat_world", _vertex_type_flat_world },
	{ "flat_rigid", _vertex_type_flat_rigid },
	{ "flat_skinned", _vertex_type_flat_skinned },
	{ "screen", _vertex_type_screen },
	{ "debug", _vertex_type_debug },
	{ "transparent", _vertex_type_transparent },
	{ "particle", _vertex_type_particle },
	{ "contrail", _vertex_type_contrail },
	{ "light_volume", _vertex_type_light_volume },
	{ "chud_simple", _vertex_type_chud_simple },
	{ "chud_fancy", _vertex_type_chud_fancy },
	{ "decorator", _vertex_type_decorator },
	{ "tiny_position", _vertex_type_tiny_position },
	{ "patchy_fog", _vertex_type_patchy_fog },
	{ "water", _vertex_type_water },
	{ "ripple", _vertex_type_ripple },
	{ "implicit", _vertex_type_implicit },
	{ "beam", _vertex_type_beam },
	{ "world_tessellated", _vertex_type_world_tessellated },
	{ "rigid_tessellated", _vertex_type_rigid_tessellated },
	{ "skinned_tessellated", _vertex_type_skinned_tessellated },
	{ "shader_cache", _vertex_type_shader_cache },
	{ "instance_imposter", _vertex_type_instance_imposter },
	{ "object_imposter", _vertex_type_object_imposter },
	{ "rigid_compressed", _vertex_type_rigid_compressed },
	{ "skinned_compressed", _vertex_type_skinned_compressed },
	{ "light_volume_precompiled", _vertex_type_light_volume_precompiled },
	{ "bink", _vertex_type_bink },
};

TAG_ENUM(
    index_buffer_type_enum,
	k_number_of_index_buffer_types)
{
	{ "default", _index_buffer_type_default },
	{ "line_list", _index_buffer_type_line_list },
	{ "line_strip", _index_buffer_type_line_strip },
	{ "triangle_list", _index_buffer_type_triangle_list },
	{ "triangle_patch", _index_buffer_type_triangle_patch },
	{ "triangle_strip", _index_buffer_type_triangle_strip },
	{ "quad_list", _index_buffer_type_quad_list },
	{ "rect_list", _index_buffer_type_rect_list },
};

TAG_ENUM(
    compression_flags_enum,
	k_number_of_compression_flags)
{
	{ "compressed_position", _compressed_position_bit },
	{ "compressed_texcoord", _compressed_texcoord_bit },
	{ "compression_optimized", _compression_optimized_bit },
};

TAG_REFERENCE(
    geometry_render_method_reference,
    1)
{
    k_render_method_group_tag
};

TAG_BLOCK(
    geometry_material_block,
    sizeof(s_geometry_material),
    k_maximum_number_of_materials_per_geometry)
{
	{ _field_tag_reference, "render_method" },
	{ _field_long_integer, "unknown10" },
	{ _field_real, "unknown14" },
	{ _field_real, "unknown18" },
	{ _field_char_integer, "unknown1C" },
	{ _field_char_integer, "unknown1D" },
	{ _field_char_integer, "unknown1E" },
	{ _field_char_integer, "unknown1F" },
	{ _field_real, "unknown20" },
	{ _field_real, "unknown24" },
	{ _field_char_integer, "unknown28" },
	{ _field_char_integer, "unknown29" },
	{ _field_char_integer, "unknown2A" },
	{ _field_char_integer, "unknown2B" },
    { _field_terminator }
};

TAG_ARRAY(
    _field_byte_integer,
    sorting_position_node_indices_array,
    k_number_of_node_indices_per_vertex);

TAG_ARRAY(
    _field_real,
    sorting_position_node_weights_array,
    k_number_of_node_weights_per_vertex);

TAG_BLOCK(
    sorting_position_block,
    sizeof(s_sorting_position),
    k_maximum_number_of_part_sorting_positions_per_mesh)
{
	{ _field_real_plane3d, "plane" },
	{ _field_real_point3d, "position" },
	{ _field_real, "radius" },
	{ _field_array, "node_indices", &sorting_position_node_indices_array },
	{ _field_array, "node_weights", &sorting_position_node_weights_array },
    { _field_terminator }
};

TAG_PADDING(
    _field_short_integer,
    part_post_budget_vertex_count_padding,
    1);

TAG_BLOCK(
    part_block,
    sizeof(s_part),
    k_maximum_number_of_parts_per_mesh)
{
	{ _field_short_block_index, "material_index", &geometry_material_block },
	{ _field_short_block_index, "transparent_sorting_index", &sorting_position_block },
	{ _field_long_integer, "index_start" },
	{ _field_long_integer, "index_count" },
	{ _field_short_integer, "subpart_start" },
	{ _field_short_integer, "subpart_count" },
	{ _field_char_enum, "part_type", &part_type_enum },
	{ _field_char_enum, "specialized_render", &specialized_render_type_enum },
	{ _field_word_flags, "part_flags", &part_flags_enum },
	{ _field_word_integer, "budget_vertex_count" },
	{ _field_padding, "post_budget_vertex_count_padding", &part_post_budget_vertex_count_padding },
    { _field_terminator }
};

TAG_BLOCK(
    subpart_block,
    sizeof(s_subpart),
    k_maximum_number_of_subparts_per_mesh)
{
	{ _field_long_integer, "index_start" },
	{ _field_long_integer, "index_count" },
	{ _field_short_block_index, "part", &part_block },
	{ _field_word_integer, "budget_vertex_count" },
	{ _field_dword_integer, "analytical_light_index" },
    { _field_terminator }
};

TAG_BLOCK(
    instance_bucket_instance_block,
    sizeof(s_instance_bucket_instance),
    k_maximum_number_of_instance_bucket_instances_per_geometry)
{
	{ _field_short_integer, "instance_index" },
    { _field_terminator }
};

extern s_tag_block_definition mesh_block;

TAG_BLOCK(
    instance_bucket_block,
    sizeof(s_instance_bucket),
    k_maximum_number_of_instance_buckets_per_geometry)
{
	{ _field_short_block_index, "mesh", &mesh_block },
	{ _field_short_integer, "definition_index" },
	{ _field_block, "instances", &instance_bucket_instance_block },
    { _field_terminator }
};

TAG_BLOCK(
	water_instance_start_block,
	sizeof(s_water_instance_start),
	k_maximum_number_of_water_indices_per_geometry)
{
	{ _field_short_integer, "value" },
	{ _field_terminator }
};

TAG_ARRAY(
	_field_short_integer,
	mesh_vertex_buffer_indices_array,
	k_maximum_number_of_vertex_buffers_per_mesh);

TAG_ARRAY(
	_field_short_integer,
	mesh_index_buffer_indices_array,
	k_maximum_number_of_index_buffers_per_mesh);

TAG_BLOCK(
	mesh_block,
	sizeof(s_mesh),
	k_maximum_number_of_meshes_per_geometry)
{
	{ _field_block, "parts", &part_block },
	{ _field_block, "subparts", &subpart_block },
	{ _field_array, "vertex_buffer_indices", &mesh_vertex_buffer_indices_array },
	{ _field_array, "index_buffer_indices", &mesh_index_buffer_indices_array },
	{ _field_byte_flags, "mesh_flags", &mesh_flags_enum },
	{ _field_char_integer, "rigid_node_index" },
	{ _field_char_enum, "vertex_type", &vertex_type_enum },
	{ _field_char_integer, "use_dual_quat" },
	{ _field_char_enum, "prt_type", &prt_type_enum },
	{ _field_char_enum, "index_buffer_type", &index_buffer_type_enum },
	{ _field_char_integer, "unknown33" },
	{ _field_block, "instance_buckets", &instance_bucket_block },
	{ _field_block, "water_instance_start", &water_instance_start_block },
	{ _field_long_integer, "unknown4C" },
	{ _field_long_integer, "unknown50" },
	{ _field_long_integer, "unknown54" },
	{ _field_long_integer, "unknown58" },
	{ _field_terminator }
};

TAG_PADDING(
	_field_short_block_index,
	compression_info_post_flags_padding,
	1);

TAG_PADDING(
	_field_long_integer,
	compression_info_post_bounds_padding,
	2);

TAG_BLOCK(
	compression_info_block,
	sizeof(s_compression_info),
	k_maximum_number_of_compressions_per_geometry)
{
	{ _field_word_flags, "flags", &compression_flags_enum },
	{ _field_padding, "post_flags_padding", &compression_info_post_flags_padding },
	{ _field_real_point3d, "position_lower" },
	{ _field_real_point3d, "position_upper" },
	{ _field_real_point2d, "texcoord_lower" },
	{ _field_real_point2d, "texcoord_upper" },
	{ _field_padding, "post_bounds_padding", &compression_info_post_bounds_padding },
	{ _field_terminator }
};

TAG_BLOCK(
	geometry_unknown1_block,
	sizeof(s_geometry_unknown1),
	NONE)
{
	{ _field_short_integer, "unknown0" },
	{ _field_short_integer, "unknown2" },
	{ _field_data, "unknown4" },
	{ _field_terminator }
};

TAG_BLOCK(
	geometry_unknown3_block,
	sizeof(s_geometry_unknown3),
	NONE)
{
	{ _field_short_integer, "unknown0" },
	{ _field_terminator }
};

TAG_BLOCK(
	geometry_unknown2_block,
	sizeof(s_geometry_unknown2),
	NONE)
{
	{ _field_data, "unknown0" },
	{ _field_block, "unknown14", &geometry_unknown3_block },
	{ _field_terminator }
};

TAG_BLOCK(
	node_map_char_block,
	sizeof(s_node_map_char),
	NONE)
{
	{ _field_char_integer, "node_index" },
	{ _field_terminator }
};

TAG_BLOCK(
	per_mesh_node_map_block,
	sizeof(s_per_mesh_node_map),
	NONE)
{
	{ _field_block, "node_map", &node_map_char_block },
	{ _field_terminator }
};

TAG_BLOCK(
	per_mesh_subpart_visibility_block,
	sizeof(s_per_mesh_subpart_visibility),
	NONE)
{
	{ _field_block, "bounding_sphere", &sorting_position_block },
	{ _field_terminator }
};

TAG_BLOCK(
	per_instance_lod_datum_index_block,
	sizeof(s_per_instance_lod_datum_index),
	NONE)
{
	{ _field_long_integer, "index" },
	{ _field_terminator }
};

TAG_BLOCK(
	per_instance_lod_data_block,
	sizeof(s_per_instance_lod_data),
	NONE)
{
	{ _field_block, "indices", &per_instance_lod_datum_index_block },
	{ _field_short_integer, "vertex_buffer_index" },
	{ _field_short_integer, "char_definition_index" },
	{ _field_terminator }
};

TAG_BLOCK(
	geometry_unknown4_block,
	sizeof(s_geometry_unknown4),
	NONE)
{
	{ _field_long_integer, "index" },
	{ _field_terminator }
};

TAG_BLOCK(
	water_bounding_box_block,
	sizeof(s_water_bounding_box),
	NONE)
{
	{ _field_short_block_index, "mesh", &mesh_block },
	{ _field_short_block_index, "part", &part_block },
	{ _field_real_point3d, "position_lower" },
	{ _field_real_point3d, "position_upper" },
	{ _field_terminator }
};

TAG_PADDING(
	_field_long_integer,
	render_geometry_post_resource_index_padding,
	1);

TAG_BLOCK(
	mesh_resource_group_block,
	sizeof(s_mesh_resource_group),
	NONE)
{
	{ _field_dword_integer, "address" },
	{ _field_terminator }
};

TAG_STRUCT(
	render_geometry_struct,
	sizeof(s_render_geometry))
{
	{ _field_long_flags, "runtime_flags", &render_geometry_runtime_flags_enum },
	{ _field_block, "meshes", &mesh_block },
	{ _field_block, "compression_info", &compression_info_block },
	{ _field_block, "part_sorting_position", &sorting_position_block },
	{ _field_block, "unknown28", &geometry_unknown1_block },
	{ _field_block, "unknown34" },
	{ _field_block, "unknown40", &geometry_unknown2_block },
	{ _field_block, "per_mesh_node_map", &per_mesh_node_map_block },
	{ _field_block, "per_mesh_subpart_visibility", &per_mesh_subpart_visibility_block },
	{ _field_block, "unknown64" },
	{ _field_block, "per_instance_lod_data", &per_instance_lod_data_block },
	{ _field_block, "unknown7C", &geometry_unknown4_block },
	{ _field_block, "water_bounding_box", &water_bounding_box_block },
	{ _field_datum_index, "resource_index" },
	{ _field_padding, "post_resource_index_padding", &render_geometry_post_resource_index_padding },
	{ _field_block, "mesh_resource_groups", &mesh_resource_group_block },
	{ _field_terminator }
};
