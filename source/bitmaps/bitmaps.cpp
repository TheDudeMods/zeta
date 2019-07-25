#include <bitmaps/bitmaps.h>

/* ---------- definitions */

TAG_ENUM(
	bitmap_usage_enum,
	k_number_of_bitmap_usages)
{
	{ "diffuse_map", _bitmap_usage_diffuse_map },
	{ "specular_map", _bitmap_usage_specular_map },
	{ "bump_map", _bitmap_usage_bump_map },
	{ "detail_bump_map", _bitmap_usage_detail_bump_map },
	{ "detail_map", _bitmap_usage_detail_map },
	{ "self_illum_map", _bitmap_usage_self_illum_map },
	{ "change_color_map", _bitmap_usage_change_color_map },
	{ "cube_map", _bitmap_usage_cube_map },
	{ "sprite_additive", _bitmap_usage_sprite_additive },
	{ "sprite_blend", _bitmap_usage_sprite_blend },
	{ "sprite_double_multiply", _bitmap_usage_sprite_double_multiply },
	{ "interface_bitmap", _bitmap_usage_interface_bitmap },
	{ "warp_map", _bitmap_usage_warp_map },
	{ "vector_map", _bitmap_usage_vector_map },
	{ "3d_texture", _bitmap_usage_3d_texture },
	{ "float_map", _bitmap_usage_float_map },
	{ "half_float_map", _bitmap_usage_half_float_map },
	{ "height_map", _bitmap_usage_height_map },
	{ "z_brush_bump_map", _bitmap_usage_z_brush_bump_map },
	{ "z_brush_normal_map", _bitmap_usage_z_brush_normal_map },
	{ "detail_z_brush_bump_map", _bitmap_usage_detail_z_brush_bump_map },
	{ "detail_z_brush_normal_map", _bitmap_usage_detail_z_brush_normal_map },
	{ "blend_map", _bitmap_usage_blend_map },
	{ "palettized", _bitmap_usage_palettized },
	{ "chud_related_bitmap", _bitmap_usage_chud_related_bitmap },
	{ "lightmap_array", _bitmap_usage_lightmap_array },
	{ "water_array", _bitmap_usage_water_array },
	{ "interface_sprite", _bitmap_usage_interface_sprite },
	{ "interface_gradient", _bitmap_usage_interface_gradient },
	{ "material_map", _bitmap_usage_material_map },
	{ "smoke_warp", _bitmap_usage_smoke_warp },
	{ "mux_material_blend_map", _bitmap_usage_mux_material_blend_map },
	{ "cubemap_gel", _bitmap_usage_cubemap_gel },
	{ "lens_flare", _bitmap_usage_lens_flare },
	{ "signed_noise", _bitmap_usage_signed_noise },
	{ "roughness_map", _bitmap_usage_roughness_map },
	{ "normal_map", _bitmap_usage_normal_map },
	{ "color_grading", _bitmap_usage_color_grading },
	{ "detail_normal_map", _bitmap_usage_detail_normal_map },
	{ "diffuse_texture_array", _bitmap_usage_diffuse_texture_array },
	{ "palettized_texture_array", _bitmap_usage_palettized_texture_array },
	{ "uncompressed_palette", _bitmap_usage_uncompressed_palette },
	{ "gobo", _bitmap_usage_gobo },
	{ "flow_map", _bitmap_usage_flow_map },
	{ "linear_control_map_texture_array", _bitmap_usage_linear_control_map_texture_array },
	{ "bump_map_texture_array", _bitmap_usage_bump_map_texture_array },
	{ "detail_map_texture_array", _bitmap_usage_detail_map_texture_array },
	{ "self_illum_map_texture_array", _bitmap_usage_self_illum_map_texture_array },
	{ "sprite_additive_texture_array", _bitmap_usage_sprite_additive_texture_array },
	{ "sprite_blend_texture_array", _bitmap_usage_sprite_blend_texture_array },
	{ "sprite_double_multiply_texture_array", _bitmap_usage_sprite_double_multiply_texture_array },
	{ "warp_map_texture_array", _bitmap_usage_warp_map_texture_array },
	{ "z_brush_normal_map_texture_array", _bitmap_usage_z_brush_normal_map_texture_array },
	{ "z_brush_detail_normal_map_texture_array", _bitmap_usage_z_brush_detail_normal_map_texture_array },
	{ "lens_flare_texture_array", _bitmap_usage_lens_flare_texture_array },
	{ "normal_map_texture_array", _bitmap_usage_normal_map_texture_array },
	{ "detail_normal_map_texture_array", _bitmap_usage_detail_normal_map_texture_array },
	{ "flow_map_texture_array", _bitmap_usage_flow_map_texture_array },
	{ "sprite_normal_map", _bitmap_usage_sprite_normal_map },
};

TAG_ENUM(
	bitmap_flags_enum,
	k_number_of_bitmap_flags)
{
	{ "is_tiled", _bitmap_is_tiled_bit },
	{ "use_less_blurry_bump_map", _bitmap_use_less_blurry_bump_map_bit },
	{ "dither_when_compressing", _bitmap_dither_when_compressing_bit },
	{ "generate_random_sprites", _bitmap_generate_random_sprites_bit },
	{ "using_tag_interop_and_tag_resource", _bitmap_using_tag_interop_and_tag_resource_bit },
	{ "ignore_alpha_channel", _bitmap_ignore_alpha_channel_bit },
	{ "alpha_channel_stores_transparency", _bitmap_alpha_channel_stores_transparency_bit },
	{ "preserve_alpha_channel_in_mipmaps_for_alpha_test", _bitmap_preserve_alpha_channel_in_mipmaps_for_alpha_test_bit },
	{ "only_use_on_demand", _bitmap_only_use_on_demand_bit },
	{ "generate_tight_bounds", _bitmap_generate_tight_bounds_bit },
	{ "tight_bounds_from_alpha_channel", _bitmap_tight_bounds_from_alpha_channel_bit },
	{ "do_not_generate_required_section", _bitmap_do_not_generate_required_section_bit },
	{ "unused", _bitmap_unused_bit },
	{ "apply_max_resolution_after_slicing", _bitmap_apply_max_resolution_after_slicing_bit },
	{ "generate_black_point_tight_bounds", _bitmap_generate_black_point_tight_bounds_bit },
	{ "pre_filter_cubemaps", _bitmap_pre_filter_cubemaps_bit },
};

TAG_ENUM(
	bitmap_curve_mode_enum,
	k_number_of_bitmap_curve_modes)
{
	{ "choose_best", _bitmap_curve_mode_choose_best },
	{ "force_fast", _bitmap_curve_mode_force_fast },
	{ "force_pretty", _bitmap_curve_mode_force_pretty },
};

TAG_ENUM(
	bitmap_curve_enum,
	k_number_of_bitmap_curves)
{
	{ "unknown", _bitmap_curve_unknown },
	{ "xrgb", _bitmap_curve_xrgb },
	{ "gamma2", _bitmap_curve_gamma2 },
	{ "linear", _bitmap_curve_linear },
	{ "offset_log", _bitmap_curve_offset_log },
	{ "srgb", _bitmap_curve_srgb },
	{ "709", _bitmap_curve_709 },
};

TAG_ENUM(
	bitmap_usage_flags_enum,
	k_number_of_bitmap_usage_flags)
{
	{ "ignore_curve_override", _bitmap_usage_ignore_curve_override_bit },
	{ "dont_allow_size_optimization", _bitmap_usage_dont_allow_size_optimization_bit },
	{ "swap_axes", _bitmap_usage_swap_axes_bit },
	{ "pre_filter_cubemaps", _bitmap_usage_pre_filter_cubemaps_bit },
};

TAG_ENUM(
	bitmap_slicer_mode_enum,
	k_number_of_bitmap_slicer_modes)
{
	{ "automatically_determine_slicer", _bitmap_slicer_mode_automatically_determine_slicer },
	{ "no_slicing", _bitmap_slicer_mode_no_slicing },
	{ "color_plate_slicer", _bitmap_slicer_mode_color_plate_slicer },
	{ "cube_map_slicer", _bitmap_slicer_mode_cube_map_slicer },
	{ "color_grading_slicer", _bitmap_slicer_mode_color_grading_slicer },
};

TAG_ENUM(
	bitmap_dicer_flags_enum,
	k_number_of_bitmap_dicer_flags)
{
	{ "convert_plate_color_key_to_alpha_channel", _bitmap_dicer_convert_plate_color_key_to_alpha_channel_bit },
	{ "rotate_cube_map_to_match_direct_x_format", _bitmap_dicer_rotate_cube_map_to_match_direct_x_format_bit },
	{ "shrink_elements_to_smallest_non_zero_alpha_region", _bitmap_dicer_shrink_elements_to_smallest_non_zero_alpha_region_bit },
	{ "shrink_elements_to_smallest_non_zero_color_and_alpha_region", _bitmap_dicer_shrink_elements_to_smallest_non_zero_color_and_alpha_region_bit },
	{ "unsigned_to_signed_scale_and_bias", _bitmap_dicer_unsigned_to_signed_scale_and_bias_bit },
	{ "color_grading_s_rgb_correction", _bitmap_dicer_color_grading_s_rgb_correction_bit },
	{ "color_grading_rec709_correction", _bitmap_dicer_color_grading_rec709_correction_bit },
};

TAG_ENUM(
	bitmap_packer_mode_enum,
	k_number_of_bitmap_packer_modes)
{
	{ "no_packing", _bitmap_packer_mode_no_packing },
	{ "sprite_pack", _bitmap_packer_mode_sprite_pack },
	{ "sprite_pack_if_needed", _bitmap_packer_mode_sprite_pack_if_needed },
	{ "3d_pack", _bitmap_packer_mode_3d_pack },
};

TAG_ENUM(
	bitmap_packer_flags_enum,
	k_number_of_bitmap_packer_flags)
{
	{ "shrink_sprite_texture_pages_tightly_to_content", _bitmap_packer_shrink_sprite_texture_pages_tightly_to_content_bit },
};

TAG_ENUM(
	bitmap_type_enum,
	k_number_of_bitmap_types)
{
	{ "2d_texture", _bitmap_type_2d_texture },
	{ "3d_texture", _bitmap_type_3d_texture },
	{ "cube_map", _bitmap_type_cube_map },
	{ "array", _bitmap_type_array },
};

TAG_ENUM(
	bitmap_smallest_mip_enum,
	k_number_of_bitmap_smallest_mips)
{
	{ "1_pixel", _bitmap_smallest_mip_1_pixel },
	{ "2_pixel", _bitmap_smallest_mip_2_pixel },
	{ "4_pixel", _bitmap_smallest_mip_4_pixel },
	{ "8_pixel", _bitmap_smallest_mip_8_pixel },
	{ "16_pixel", _bitmap_smallest_mip_16_pixel },
	{ "32_pixel", _bitmap_smallest_mip_32_pixel },
	{ "64_pixel", _bitmap_smallest_mip_64_pixel },
	{ "128_pixel", _bitmap_smallest_mip_128_pixel },
	{ "256_pixel", _bitmap_smallest_mip_256_pixel },
	{ "512_pixel", _bitmap_smallest_mip_512_pixel },
	{ "1024_pixel", _bitmap_smallest_mip_1024_pixel },
};

TAG_ENUM(
	bitmap_downsample_filter_enum,
	k_number_of_bitmap_downsample_filters)
{
	{ "point_sampled", _bitmap_downsample_filter_point_sampled },
	{ "box", _bitmap_downsample_filter_box },
	{ "blackman", _bitmap_downsample_filter_blackman },
	{ "lanczos", _bitmap_downsample_filter_lanczos },
	{ "nuttall", _bitmap_downsample_filter_nuttall },
	{ "blackman_harris", _bitmap_downsample_filter_blackman_harris },
	{ "blackman_nuttall", _bitmap_downsample_filter_blackman_nuttall },
	{ "flat_top", _bitmap_downsample_filter_flat_top },
	{ "extreme", _bitmap_downsample_filter_extreme },
};

TAG_ENUM(
	bitmap_downsample_flags_enum,
	k_number_of_bitmap_downsample_flags)
{
	{ "sprites_color_bleed_in_zero_alpha_regions", _bitmap_downsample_filter_sprites_color_bleed_in_zero_alpha_regions_bit },
	{ "pre_multiply_alpha_before_downsampling", _bitmap_downsample_filter_pre_multiply_alpha_before_downsampling_bit },
	{ "post_divide_alpha_after_downsampling", _bitmap_downsample_filter_post_divide_alpha_after_downsampling_bit },
	{ "height_map_convert_to_bump_map", _bitmap_downsample_filter_height_map_convert_to_bump_map_bit },
	{ "detail_map_fade_to_gray", _bitmap_downsample_filter_detail_map_fade_to_gray_bit },
	{ "signed_gt_unsigned_scale_and_bias", _bitmap_downsample_filter_signed_gt_unsigned_scale_and_bias_bit },
	{ "illum_map_fade_to_black", _bitmap_downsample_filter_illum_map_fade_to_black_bit },
	{ "z_bump_scale_by_height_and_renormalize", _bitmap_downsample_filter_z_bump_scale_by_height_and_renormalize_bit },
	{ "cubemap_fix_seams", _bitmap_downsample_filter_cubemap_fix_seams_bit },
	{ "calculate_specular_power", _bitmap_downsample_filter_calculate_specular_power_bit },
	{ "downsample_bumps_in_angular_space", _bitmap_downsample_filter_downsample_bumps_in_angular_space_bit },
	{ "standard_orientation_of_normals_in_angular_space_and_renormalize", _bitmap_downsample_filter_standard_orientation_of_normals_in_angular_space_and_renormalize_bit },
	{ "generate_rgb_luminance_into_alpha_channel", _bitmap_downsample_filter_generate_rgb_luminance_into_alpha_channel_bit },
};

TAG_ENUM(
	bitmap_swizzle_enum,
	k_number_of_bitmap_swizzles)
{
	{ "default", _bitmap_swizzle_default },
	{ "source_red_channel", _bitmap_swizzle_source_red_channel },
	{ "source_green_channel", _bitmap_swizzle_source_green_channel },
	{ "source_blue_channel", _bitmap_swizzle_source_blue_channel },
	{ "source_alpha_channel", _bitmap_swizzle_source_alpha_channel },
	{ "set_to_1_0", _bitmap_swizzle_set_to_1_0 },
	{ "set_to_0_0", _bitmap_swizzle_set_to_0_0 },
	{ "set_to_0_5", _bitmap_swizzle_set_to_0_5 },
	{ "random", _bitmap_swizzle_random },
};

TAG_BLOCK(
	bitmap_usage_block,
	sizeof(s_bitmap_usage),
	k_maximum_number_of_bitmap_usages)
{
	{ _field_real, "source_gamma" },
	{ _field_long_enum, "bitmap_curve", &bitmap_curve_enum },
	{ _field_byte_flags, "flags", &bitmap_usage_flags_enum },
	{ _field_char_enum, "slicer", &bitmap_slicer_mode_enum },
	{ _field_byte_flags, "dicer_flags", &bitmap_dicer_flags_enum },
	{ _field_char_enum, "packer", &bitmap_packer_mode_enum },
	{ _field_byte_flags, "packer_flags", &bitmap_packer_flags_enum },
	{ _field_char_enum, "type", &bitmap_type_enum },
	{ _field_char_integer, "mipmap_limit" },
	{ _field_char_enum, "smallest_mip", &bitmap_smallest_mip_enum },
	{ _field_char_enum, "downsample_filter", &bitmap_downsample_filter_enum },
	{ _field_char_integer, "filter_radius_bias" },
	{ _field_word_flags, "downsample_flags", &bitmap_downsample_flags_enum },
	{ _field_real_rgb_color, "sprite_background_color" },
	{ _field_char_enum, "swizzle_red", &bitmap_swizzle_enum },
	{ _field_char_enum, "swizzle_green", &bitmap_swizzle_enum },
	{ _field_char_enum, "swizzle_blue", &bitmap_swizzle_enum },
	{ _field_char_enum, "swizzle_alpha", &bitmap_swizzle_enum },
	{ _field_long_integer, "format" },
	{ _field_terminator }
};

TAG_ENUM(
	bitmap_image_flags_enum,
	k_number_of_bitmap_image_flags)
{
	{ "power_of_two_dimensions", _bitmap_image_power_of_two_dimensions_bit },
	{ "compressed", _bitmap_image_compressed_bit },
	{ "palettized", _bitmap_image_palettized_bit },
	{ "swizzled", _bitmap_image_swizzled_bit },
	{ "linear", _bitmap_image_linear_bit },
	{ "v16u16", _bitmap_image_v16u16_bit },
	{ "mip_map_debug_level", _bitmap_image_mip_map_debug_level_bit },
	{ "prefer_stutter", _bitmap_image_prefer_stutter_bit },
	{ "unknown8", _bitmap_image_unknown8_bit },
	{ "always_on", _bitmap_image_always_on_bit },
	{ "unknown10", _bitmap_image_unknown10_bit },
	{ "unknown11", _bitmap_image_unknown11_bit },
	{ "interlaced", _bitmap_image_interlaced_bit },
	{ "unknown13", _bitmap_image_unknown13_bit },
	{ "unknown14", _bitmap_image_unknown14_bit },
	{ "unknown15", _bitmap_image_unknown15_bit },
};

TAG_ENUM(
	bitmap_more_image_flags_enum,
	k_number_of_bitmap_more_image_flags)
{
	{ "xbox360_medium_resolution_offset_is_valid", _bitmap_image_xbox360_medium_resolution_offset_is_valid_bit },
	{ "xbox360_memory_spacing", _bitmap_image_xbox360_memory_spacing_bit },
	{ "xbox360_byte_order", _bitmap_image_xbox360_byte_order_bit },
	{ "xbox360_tiled_texture", _bitmap_image_xbox360_tiled_texture_bit },
	{ "xbox360_created_correctly", _bitmap_image_xbox360_created_correctly_bit },
	{ "xbox360_high_resolution_offset_is_valid", _bitmap_image_xbox360_high_resolution_offset_is_valid_bit },
	{ "xbox360_use_interleaved_textures", _bitmap_image_xbox360_use_interleaved_textures_bit },
	{ "xbox360_use_on_demand_only", _bitmap_image_xbox360_use_on_demand_only_bit },
};

TAG_BLOCK(
	bitmap_image_block,
	sizeof(s_bitmap_image),
	k_maximum_number_of_bitmap_images)
{
	{ _field_short_integer, "width" },
	{ _field_short_integer, "height" },
	{ _field_char_integer, "depth" },
	{ _field_byte_flags, "more_flags", &bitmap_more_image_flags_enum },
	{ _field_char_enum, "type", &bitmap_type_enum },
	{ _field_char_integer, "four_times_log2_size" },
	{ _field_short_integer, "format" },
	{ _field_word_flags, "flags", &bitmap_image_flags_enum },
	{ _field_point2d, "registration_point" },
	{ _field_char_integer, "mipmap_count" },
	{ _field_char_enum, "curve", &bitmap_curve_enum },
	{ _field_char_integer, "unknown12" },
	{ _field_char_integer, "interleaved_texture_index" },
	{ _field_long_integer, "pixels_offset" },
	{ _field_long_integer, "pixels_count" },
	{ _field_long_integer, "unknown1C" },
	{ _field_char_integer, "unknown20" },
	{ _field_char_integer, "unknown21" },
	{ _field_char_integer, "unknown22" },
	{ _field_char_integer, "unknown23" },
	{ _field_long_integer, "unknown24" },
	{ _field_long_integer, "unknown28" },
	{ _field_terminator }
};

TAG_PADDING(
	_field_short_integer,
	bitmap_sequence_sprite_post_bitmap_index_padding,
	3);

TAG_BLOCK(
	bitmap_sequence_sprite_block,
	sizeof(s_bitmap_sequence_sprite),
	k_maximum_number_of_bitmap_sequence_sprites)
{
	{ _field_short_block_index, "bitmap_index", &bitmap_image_block },
	{ _field_padding, "post_bitmap_index_padding", &bitmap_sequence_sprite_post_bitmap_index_padding },
	{ _field_real, "left" },
	{ _field_real, "right" },
	{ _field_real, "top" },
	{ _field_real, "bottom" },
	{ _field_real_point2d, "registration_point" },
	{ _field_terminator }
};

TAG_PADDING(
	_field_long_integer,
	bitmap_sequence_post_bitmap_count_padding,
	4);

TAG_BLOCK(
	bitmap_sequence_block,
	sizeof(s_bitmap_sequence),
	k_maximum_number_of_bitmap_sequences)
{
	{ _field_short_string, "name" },
	{ _field_short_integer, "first_bitmap_index" },
	{ _field_short_integer, "bitmap_count" },
	{ _field_padding, "post_bitmap_count_padding", &bitmap_sequence_post_bitmap_count_padding },
	{ _field_block, "sprites", &bitmap_sequence_sprite_block },
	{ _field_terminator }
};

TAG_BLOCK(
	bitmap_tight_bounds_block,
	sizeof(s_bitmap_tight_bounds),
	k_maximum_number_of_bitmap_tight_bounds)
{
	{ _field_real, "u" },
	{ _field_real, "v" },
	{ _field_terminator }
};

TAG_PADDING(
	_field_long_integer,
	bitmap_resource_info_post_resource_index_padding,
	1);

TAG_BLOCK(
	bitmap_resource_info_block,
	sizeof(s_bitmap_resource_info),
	k_maximum_number_of_bitmap_images)
{
	{ _field_datum_index, "resource_index" },
	{ _field_padding, "post_resource_index_padding", &bitmap_resource_info_post_resource_index_padding },
	{ _field_terminator }
};

TAG_GROUP(
	bitmap_group,
	k_bitmap_group_tag,
	sizeof(s_bitmap_definition))
{
	{ _field_long_enum, "usage", &bitmap_usage_enum },
	{ _field_word_flags, "flags", &bitmap_flags_enum },
	{ _field_short_integer, "sprite_spacing" },
	{ _field_real, "bump_map_height" },
	{ _field_real, "fade_factor" },
	{ _field_real, "blur" },
	{ _field_real, "mipmap_blur" },
	{ _field_char_enum, "curve_mode", &bitmap_curve_mode_enum },
	{ _field_char_integer, "max_mipmap_level" },
	{ _field_short_integer, "max_resolution" },
	{ _field_short_integer, "atlas" },
	{ _field_short_integer, "force_bitmap_format" },
	{ _field_real, "tight_bounds_threshold" },
	{ _field_block, "usage_override", &bitmap_usage_block },
	{ _field_block, "manual_sequences", &bitmap_sequence_block },
	{ _field_block, "tight_bounds", &bitmap_tight_bounds_block },
	{ _field_data, "source_data" },
	{ _field_data, "processed_pixel_data" },
	{ _field_block, "sequences", &bitmap_sequence_block },
	{ _field_block, "images", &bitmap_image_block },
	{ _field_data, "xenon_processed_pixel_data" },
	{ _field_block, "xenon_images", &bitmap_image_block },
	{ _field_block, "resources", &bitmap_resource_info_block },
	{ _field_block, "interleaved_resources", &bitmap_resource_info_block },
	{ _field_terminator }
};
