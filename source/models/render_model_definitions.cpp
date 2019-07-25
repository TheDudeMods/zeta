#include <models/render_model_definitions.h>

extern s_tag_block_definition mesh_block;
extern s_tag_block_definition geometry_material_block;
extern s_struct_definition render_geometry_struct;

/* ---------- definitions */

TAG_ENUM(
    render_model_flags_enum,
	k_number_of_render_model_flags)
{
	{ "is_hologram", _render_model_is_hologram_bit },
	{ "has_water", _render_model_has_water_bit },
	{ "has_node_maps", _render_model_has_node_maps_bit },
	{ "lod_regions_enabled", _render_model_lod_regions_enabled_bit },
	{ "has_split_lighting", _render_model_has_split_lighting_bit },
	{ "has_depth_peeling", _render_model_has_depth_peeling_bit },
	{ "has_custom_shadow_meshes", _render_model_has_custom_shadow_meshes_bit },
	{ "has_deferred_reflections", _render_model_has_deferred_reflections_bit },
	{ "is_hologram_lofi", _render_model_is_hologram_lofi_bit },
	{ "has_mid_distance_cull_parts", _render_model_has_mid_distance_cull_parts_bit },
	{ "has_close_distance_cull_parts", _render_model_has_close_distance_cull_parts_bit },
};

TAG_ENUM(
    render_model_marker_flags_enum,
	k_number_of_render_model_marker_flags)
{
	{ "has_node_relative_direction", _render_model_marker_has_node_relative_direction_bit },
};

TAG_ARRAY(
    _field_long_integer,
    render_model_permutation_instance_masks_array,
    k_number_of_render_model_permutation_instance_bitvectors);

TAG_BLOCK(
    render_model_permutation_block,
    sizeof(s_render_model_permutation),
    k_maximum_number_of_render_model_permutations)
{
	{ _field_string_id, "name" },
	{ _field_short_block_index, "first_mesh", &mesh_block },
	{ _field_short_integer, "mesh_count" },
	{ _field_array, "instance_masks", &render_model_permutation_instance_masks_array },
    { _field_terminator }
};

TAG_BLOCK(
    render_model_region_block,
    sizeof(s_render_model_region),
    k_maximum_number_of_render_model_regions)
{
    { _field_string_id, "name" },
    { _field_block, "permutations", &render_model_permutation_block },
    { _field_terminator }
};

TAG_BLOCK(
    render_model_node_block,
    sizeof(s_render_model_node),
    k_maximum_number_of_render_model_nodes)
{
	{ _field_string_id, "name" },
	{ _field_short_block_index, "parent_node", &render_model_node_block },
	{ _field_short_block_index, "first_child_node", &render_model_node_block },
	{ _field_short_block_index, "next_sibling_node", &render_model_node_block },
	{ _field_short_block_index, "import_node", &render_model_node_block },
	{ _field_real_point3d, "default_translation" },
	{ _field_real_quaternion, "default_rotation" },
	{ _field_real_matrix4x3, "inverse_matrix" },
	{ _field_real, "distance_from_parent" },
    { _field_terminator }
};

TAG_BLOCK(
    render_model_instance_placement_block,
    sizeof(s_render_model_instance_placement),
    k_maximum_number_of_render_model_instance_placements)
{
	{ _field_string_id, "name" },
	{ _field_long_block_index, "node", &render_model_node_block },
	{ _field_real_matrix4x3, "inverse_matrix" },
    { _field_terminator }
};

TAG_BLOCK(
    render_model_marker_block,
    sizeof(s_render_model_marker),
    k_maximum_number_of_render_model_markers)
{
	{ _field_char_block_index, "region", &render_model_region_block },
	{ _field_char_block_index, "permutation", &render_model_permutation_block },
	{ _field_char_block_index, "node", &render_model_node_block },
	{ _field_byte_flags, "flags", &render_model_marker_flags_enum },
	{ _field_real_point3d, "translation" },
	{ _field_real_quaternion, "rotation" },
	{ _field_real, "scale" },
	{ _field_real_vector3d, "direction" },
    { _field_terminator }
};

TAG_BLOCK(
    render_model_marker_group_block,
    sizeof(s_render_model_marker_group),
    k_maximum_number_of_render_model_marker_groups)
{
    { _field_string_id, "name" },
    { _field_block, "markers", &render_model_marker_block },
    { _field_terminator }
};

TAG_BLOCK(
    instance_node_map_mapping_block,
    sizeof(s_instance_node_map_mapping),
    k_maximum_number_of_render_model_nodes)
{
	{ _field_short_integer, "instance_node_map_region_node_index" },
    { _field_terminator }
};

TAG_BLOCK(
    render_model_unknown1_block,
    sizeof(s_render_model_unknown1),
    NONE)
{
	{ _field_real, "unknown0" },
	{ _field_real, "unknown4" },
	{ _field_real, "unknown8" },
	{ _field_real, "unknownC" },
	{ _field_real, "unknown10" },
	{ _field_real, "unknown14" },
	{ _field_real, "unknown18" },
    { _field_terminator }
};

TAG_BLOCK(
    render_model_unknown2_block,
    sizeof(s_render_model_unknown2),
    NONE)
{
	{ _field_real, "unknown0" },
	{ _field_real, "unknown4" },
	{ _field_real, "unknown8" },
	{ _field_real, "unknownC" },
	{ _field_real, "unknown10" },
	{ _field_real, "unknown14" },
	{ _field_real, "unknown18" },
	{ _field_real, "unknown1C" },
	{ _field_real, "unknown20" },
	{ _field_real, "unknown24" },
	{ _field_real, "unknown28" },
	{ _field_real, "unknown2C" },
	{ _field_real, "unknown30" },
	{ _field_real, "unknown34" },
	{ _field_real, "unknown38" },
	{ _field_real, "unknown3C" },
	{ _field_real, "unknown40" },
	{ _field_real, "unknown44" },
	{ _field_real, "unknown48" },
	{ _field_real, "unknown4C" },
	{ _field_real, "unknown50" },
	{ _field_real, "unknown54" },
	{ _field_real, "unknown58" },
	{ _field_real, "unknown5C" },
	{ _field_real, "unknown60" },
	{ _field_real, "unknown64" },
	{ _field_real, "unknown68" },
	{ _field_real, "unknown6C" },
	{ _field_real, "unknown70" },
	{ _field_real, "unknown74" },
	{ _field_real, "unknown78" },
	{ _field_real, "unknown7C" },
	{ _field_real, "unknown80" },
	{ _field_real, "unknown84" },
	{ _field_real, "unknown88" },
	{ _field_real, "unknown8C" },
	{ _field_real, "unknown90" },
	{ _field_real, "unknown94" },
	{ _field_real, "unknown98" },
	{ _field_real, "unknown9C" },
	{ _field_real, "unknownA0" },
	{ _field_real, "unknownA4" },
	{ _field_real, "unknownA8" },
	{ _field_real, "unknownAC" },
	{ _field_real, "unknownB0" },
	{ _field_real, "unknownB4" },
	{ _field_real, "unknownB8" },
	{ _field_real, "unknownBC" },
	{ _field_real, "unknownC0" },
	{ _field_real, "unknownC4" },
	{ _field_real, "unknownC8" },
	{ _field_real, "unknownCC" },
	{ _field_real, "unknownD0" },
	{ _field_real, "unknownD4" },
	{ _field_real, "unknownD8" },
	{ _field_real, "unknownDC" },
	{ _field_real, "unknownE0" },
	{ _field_real, "unknownE4" },
	{ _field_real, "unknownE8" },
	{ _field_real, "unknownEC" },
	{ _field_real, "unknownF0" },
	{ _field_real, "unknownF4" },
	{ _field_real, "unknownF8" },
	{ _field_real, "unknownFC" },
	{ _field_real, "unknown100" },
	{ _field_real, "unknown104" },
	{ _field_real, "unknown108" },
	{ _field_real, "unknown10C" },
	{ _field_real, "unknown110" },
	{ _field_real, "unknown114" },
	{ _field_real, "unknown118" },
	{ _field_real, "unknown11C" },
	{ _field_real, "unknown120" },
	{ _field_real, "unknown124" },
	{ _field_real, "unknown128" },
	{ _field_real, "unknown12C" },
	{ _field_real, "unknown130" },
	{ _field_real, "unknown134" },
	{ _field_real, "unknown138" },
	{ _field_real, "unknown13C" },
	{ _field_real, "unknown140" },
	{ _field_real, "unknown144" },
	{ _field_real, "unknown148" },
	{ _field_real, "unknown14C" },
    { _field_terminator }
};

TAG_BLOCK(
    default_node_orientation_block,
    sizeof(s_default_node_orientation),
    k_maximum_number_of_render_model_nodes)
{
	{ _field_real_quaternion, "default_rotation" },
	{ _field_real_point3d, "default_translation" },
	{ _field_real, "default_scale" },
    { _field_terminator }
};

TAG_ARRAY(
    _field_real,
    render_model_unknowns_array,
    74);

TAG_GROUP(
    render_model_group,
    k_render_model_group_tag,
    sizeof(s_render_model_definition))
{
	{ _field_string_id, "name" },
	{ _field_word_flags, "flags", &render_model_flags_enum },
	{ _field_word_integer, "version" },
	{ _field_long_integer, "runtime_import_info_checksum" },
	{ _field_block, "regions", &render_model_region_block },
	{ _field_long_integer, "unknown18" },
	{ _field_long_block_index, "instance_mesh", &mesh_block },
	{ _field_block, "instance_placements", &render_model_instance_placement_block },
	{ _field_long_integer, "node_list_checksum" },
	{ _field_block, "nodes", &render_model_node_block },
	{ _field_block, "marker_groups", &render_model_marker_group_block },
	{ _field_block, "materials", &geometry_material_block },
	{ _field_block, "errors" },
	{ _field_real, "dont_draw_over_camera_cosine_angle" },
	{ _field_struct, "geometry", &render_geometry_struct },
	{ _field_block, "node_map_mapping", &instance_node_map_mapping_block },
	{ _field_block, "unknown1", &render_model_unknown1_block },
	{ _field_array, "unknowns", &render_model_unknowns_array },
	{ _field_block, "unknown2", &render_model_unknown2_block },
	{ _field_block, "runtime_node_orientations", &default_node_orientation_block },
    { _field_terminator }
};
