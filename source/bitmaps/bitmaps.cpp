#include <bitmaps/bitmaps.h>

/* ---------- code */

void bitmap_texture_initialize_dds_header(
	s_bitmap_image *image,
	s_bitmap_texture_resource *resource,
	s_dds_header *header)
{
	assert(resource);
	assert(header);

	header->signature = k_dds_signature;
	header->size = sizeof(s_dds_header);
	
	header->flags =
		FLAG(_dds_header_caps_bit) |
		FLAG(_dds_header_pixel_format_bit) |
		FLAG(_dds_header_height_bit) |
		FLAG(_dds_header_width_bit) |
		((resource->mipmap_count > 1) ? FLAG(_dds_header_mipmap_count_bit) : 0) |
		((resource->depth > 1) ? FLAG(_dds_header_depth_bit) : 0);

	header->height = resource->height;
	header->width = resource->width;
	header->depth = resource->depth;
	header->mipmap_count = resource->mipmap_count >= 1;

	header->pixel_format.size = sizeof(s_dds_pixel_format);

	switch (resource->type.operator e_bitmap_type())
	{
	case _bitmap_type_2d_texture:
		header->depth = 0;
		if (header->mipmap_count = (resource->mipmap_count > 0))
		{
			header->mipmap_count = resource->mipmap_count + 1;
			header->flags |= FLAG(_dds_header_mipmap_count_bit);
			header->caps[0] |= 0x400008; // mipmaps|complex
		}
		break;

	case _bitmap_type_3d_texture:
	case _bitmap_type_array:
		//
		// TODO
		//
		break;

	case _bitmap_type_cube_map:
		//
		// TODO
		//
		break;
	}

	switch (image->format.operator e_bitmap_format())
	{
	case _bitmap_format_a8:
	case _bitmap_format_ay8:
	case _bitmap_format_y8:
	case _bitmap_format_p8:
		header->pixel_format.bits_per_pixel = 8;
		break;

	case _bitmap_format_a8_y8:
	case _bitmap_format_r5_g6_b5:
	case _bitmap_format_a1_r5_g5_b5:
	case _bitmap_format_a4_r4_g4_b4:
	case _bitmap_format_a4_r4_g4_b4_font:
	case _bitmap_format_v8_u8:
		header->pixel_format.bits_per_pixel = 16;
		break;

	case _bitmap_format_a8_r8_g8_b8:
	case _bitmap_format_x8_r8_g8_b8:
	case _bitmap_format_q8_w8_v8_u8:
	case _bitmap_format_a2_r10_g10_b10:
	case _bitmap_format_v16_u16:
		header->pixel_format.bits_per_pixel = 32;
		break;

	case _bitmap_format_rgbfp16:
		header->pixel_format.bits_per_pixel = 48;
		break;

	case _bitmap_format_a16_b16_g16_r16:
	case _bitmap_format_a16_b16_g16_r16_f:
		header->pixel_format.bits_per_pixel = 64;
		break;

	case _bitmap_format_rgbfp32:
		header->pixel_format.bits_per_pixel = 96;
		break;

	case _bitmap_format_argbfp32:
	case _bitmap_format_a32_b32_g32_r32_f:
		header->pixel_format.bits_per_pixel = 128;
		break;
	}

	if (image->flags & FLAG(_bitmap_image_compressed_bit))
	{
		header->flags |= FLAG(_dds_header_linear_size_bit);

		auto block_size = 0;

		switch (image->format.operator e_bitmap_format())
		{
		case _bitmap_format_dxt1:
			block_size = 8;
			break;

		case _bitmap_format_dxt3:
		case _bitmap_format_dxt3a_alpha:
		case _bitmap_format_dxt3a_mono:
		case _bitmap_format_reach_dxt3a_alpha:
		case _bitmap_format_reach_dxt3a_mono:
		case _bitmap_format_dxt5:
		case _bitmap_format_dxt5a:
		case _bitmap_format_dxt5a_alpha:
		case _bitmap_format_dxt5a_mono:
		case _bitmap_format_reach_dxt5a_alpha:
		case _bitmap_format_reach_dxt5a_mono:
		case _bitmap_format_dxn:
		case _bitmap_format_ctx1:
			block_size = 16;
			break;

		default:
			block_size = NONE;
			break;
		}

		auto block_dimension = 0;

		switch (image->format.operator e_bitmap_format())
		{
		case _bitmap_format_dxt5a_mono:
		case _bitmap_format_dxt5a_alpha:
		case _bitmap_format_dxt1:
		case _bitmap_format_ctx1:
		case _bitmap_format_dxt5a:
		case _bitmap_format_dxt3a_alpha:
		case _bitmap_format_dxt3a_mono:
			block_dimension = 4;
			break;
		case _bitmap_format_dxt3:
		case _bitmap_format_dxt5:
		case _bitmap_format_dxn:
		case _bitmap_format_dxn_mono_alpha:
			block_dimension = 4;
			break;
		case _bitmap_format_ay8:
		case _bitmap_format_y8:
		case _bitmap_format_a8:
		case _bitmap_format_a8_y8:
		case _bitmap_format_a16_b16_g16_r16_f:
		case _bitmap_format_a32_b32_g32_r32_f:
		case _bitmap_format_a4_r4_g4_b4:
		case _bitmap_format_a1_r5_g5_b5:
		case _bitmap_format_a8_r8_g8_b8:
		case _bitmap_format_x8_r8_g8_b8:
		case _bitmap_format_v8_u8:
		case _bitmap_format_r5_g6_b5:
			block_dimension = 1;
			break;

		default:
			block_dimension = NONE;
			break;
		}

		auto nearest_width = block_dimension * ((header->height + (block_dimension - 1)) / block_dimension);
		auto nearest_height = block_dimension * ((header->width + (block_dimension - 1)) / block_dimension);

		header->pitch_or_linear_size = (nearest_width * nearest_height / 16) * block_size;

		header->pixel_format.flags |= FLAG(_dds_format_compressed_bit);
		
		switch (image->format.operator e_bitmap_format())
		{
		case _bitmap_format_dxt5:
			header->pixel_format.flags |= FLAG(_dds_format_four_cc_bit);
			header->pixel_format.four_cc = 0x35545844;
			break;

		case _bitmap_format_dxt3:
			header->pixel_format.flags |= FLAG(_dds_format_four_cc_bit);
			header->pixel_format.four_cc = 0x33545844;
			break;

		case _bitmap_format_dxt1:
			header->pixel_format.flags |= FLAG(_dds_format_four_cc_bit);
			header->pixel_format.four_cc = 0x31545844;
			break;

		case _bitmap_format_dxn:
			header->pixel_format.flags |= FLAG(_dds_format_four_cc_bit);
			header->pixel_format.four_cc = 0x32495441;
			break;

		default:
			printf("ERROR: unsupported bitmap format!\n");
			abort();
			break;
		}
	}
	else
	{
		header->flags |= FLAG(_dds_header_pitch_bit);
		header->pitch_or_linear_size = (header->width * header->pixel_format.bits_per_pixel + 7) / 8;

		header->pixel_format.flags |= FLAG(_dds_format_rgb_bit);

		switch (image->format.operator e_bitmap_format())
		{
		case _bitmap_format_a8:
		case _bitmap_format_ay8:
			header->pixel_format.a_bitmask = 0xFF;
			header->pixel_format.flags |= FLAG(_dds_format_alpha_bit);
			break;

		case _bitmap_format_y8:
			header->pixel_format.r_bitmask = 0xFF;
			header->pixel_format.flags |= FLAG(_dds_format_luminance_bit);
			break;

		case _bitmap_format_a8_y8:
			header->pixel_format.flags |= FLAG(_dds_format_rgb_bit);
			header->pixel_format.r_bitmask = 0x00FF; header->pixel_format.a_bitmask = 0xFF00;
			break;

		case _bitmap_format_r5_g6_b5:
			header->pixel_format.flags |= FLAG(_dds_format_rgb_bit);
			header->pixel_format.r_bitmask = 0xF800; header->pixel_format.g_bitmask = 0x07E0; header->pixel_format.b_bitmask = 0x001F;
			break;

		case _bitmap_format_a1_r5_g5_b5:
			header->pixel_format.flags |= FLAG(_dds_format_rgb_bit);
			header->pixel_format.r_bitmask = 0x7C00; header->pixel_format.g_bitmask = 0x03E0; header->pixel_format.b_bitmask = 0x001F; header->pixel_format.a_bitmask = 0x8000;
			break;

		case _bitmap_format_a4_r4_g4_b4:
			header->pixel_format.flags |= FLAG(_dds_format_rgb_bit);
			header->pixel_format.r_bitmask = 0xF000; header->pixel_format.g_bitmask = 0x0F00; header->pixel_format.b_bitmask = 0x00F0; header->pixel_format.a_bitmask = 0x000F;
			break;

		case _bitmap_format_a4_r4_g4_b4_font:
			header->pixel_format.flags |= FLAG(_dds_format_rgb_bit);
			header->pixel_format.r_bitmask = 0xF000; header->pixel_format.g_bitmask = 0x0F00; header->pixel_format.b_bitmask = 0x00F0; header->pixel_format.a_bitmask = 0x000F;
			break;

		case _bitmap_format_a8_r8_g8_b8:
			header->pixel_format.flags |= FLAG(_dds_format_rgb_bit);
			header->pixel_format.r_bitmask = 0x00FF0000; header->pixel_format.g_bitmask = 0x0000FF00; header->pixel_format.b_bitmask = 0x000000FF; header->pixel_format.a_bitmask = 0xFF000000;
			break;

		case _bitmap_format_x8_r8_g8_b8:
			header->pixel_format.flags |= FLAG(_dds_format_rgb_bit);
			header->pixel_format.r_bitmask = 0x00FF0000; header->pixel_format.g_bitmask = 0x0000FF00; header->pixel_format.b_bitmask = 0x000000FF;
			break;

		case _bitmap_format_v8_u8:
			header->pixel_format.r_bitmask = 0xFF00; header->pixel_format.g_bitmask = 0x00FF;
			header->pixel_format.flags |= FLAG(_dds_format_bump_dudv_bit);
			break;

		case _bitmap_format_a32_b32_g32_r32_f:
			header->pixel_format.flags |= FLAG(_dds_format_four_cc_bit);
			header->pixel_format.four_cc = 0x74;
			break;

		case _bitmap_format_a16_b16_g16_r16_f:
			header->pixel_format.flags |= FLAG(_dds_format_four_cc_bit);
			header->pixel_format.four_cc = 0x71;
			break;

		default:
			printf("ERROR: unsupported bitmap format!\n");
			abort();
			break;
		}
	}
}
