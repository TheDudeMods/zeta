#include <bitmaps/bitmaps.h>

/* ---------- code */

void bitmap_image_initialize_dds_header(
	s_bitmap_image *image,
	s_dds_header *header)
{
	assert(image);
	assert(header);

	csmemset(header, 0, sizeof(s_dds_header));

	header->four_cc = ' SDD';
	header->size = sizeof(s_dds_header);
	
	header->flags =
		FLAG(_dds_header_caps_bit) |
		FLAG(_dds_header_height_bit) |
		FLAG(_dds_header_width_bit) |
		FLAG(_dds_header_pixel_format_bit);

	header->height = image->height;
	header->width = image->width;

	if (image->format == _bitmap_format_a8_r8_g8_b8)
	{
		header->flags.set(_dds_header_pitch_bit, true);
		header->pitch_or_linear_size = header->width * 4;
	}
	else
	{
		header->flags.set(_dds_header_linear_size_bit, true);
		header->pitch_or_linear_size = bitmap_image_get_resource_length(image);
	}

	header->pixel_format.size = sizeof(s_dds_pixel_format);

	switch (image->format.operator e_bitmap_format())
	{
	case _bitmap_format_a8_r8_g8_b8:
		header->pixel_format.flags.set(_dds_format_rgb_bit, true);
		header->pixel_format.flags.set(_dds_format_alpha_pixels_bit, true);
		break;

	case _bitmap_format_dxt1:
		header->pixel_format.flags.set(_dds_format_four_cc_bit, true);
		header->pixel_format.four_cc = '1TXD';
		break;

	case _bitmap_format_dxt3:
		header->pixel_format.flags.set(_dds_format_four_cc_bit, true);
		header->pixel_format.four_cc = '3TXD';
		break;

	case _bitmap_format_dxt5:
		header->pixel_format.flags.set(_dds_format_four_cc_bit, true);
		header->pixel_format.four_cc = '5TXD';
		break;
	}

	if (image->format == _bitmap_format_a8_r8_g8_b8)
	{
		header->pixel_format.bits_per_pixel = 32;
		header->pixel_format.r_bitmask = 0x00FF0000;
		header->pixel_format.g_bitmask = 0x0000FF00;
		header->pixel_format.b_bitmask = 0x000000FF;
		header->pixel_format.a_bitmask = 0xFF000000;
	}
	else
	{
		header->pixel_format.bits_per_pixel = 0;
		header->pixel_format.r_bitmask = 0;
		header->pixel_format.g_bitmask = 0;
		header->pixel_format.b_bitmask = 0;
		header->pixel_format.a_bitmask = 0;
	}

	header->caps[0] = 0;
	header->caps[0] = FLAG(12);
}

void bitmap_image_apply_dds_header(
	s_bitmap_image *image,
	s_dds_header *header)
{
	assert(image);
	assert(header);

	image->height = header->height;
	image->width = header->width;

	if (!header->pixel_format.flags.test(_dds_format_four_cc_bit) &&
		header->pixel_format.flags.test(_dds_format_rgb_bit) &&
		header->pixel_format.flags.test(_dds_format_alpha_pixels_bit))
	{
		image->format = _bitmap_format_a8_r8_g8_b8;
	}
	else if (header->pixel_format.flags.test(_dds_format_four_cc_bit))
	{
		switch (header->pixel_format.four_cc)
		{
		case '1TXD':
			image->format = _bitmap_format_dxt1;
			break;

		case '3TXD':
			image->format = _bitmap_format_dxt3;
			break;

		case '5TXD':
			image->format = _bitmap_format_dxt5;
			break;
		}
	}
}

long bitmap_image_get_virtual_width(
	s_bitmap_image *image)
{
	long value = 0;

	switch (image->format.operator e_bitmap_format())
	{
	case _bitmap_format_a8:
	case _bitmap_format_y8:
	case _bitmap_format_ay8:
	case _bitmap_format_a8_y8:
	case _bitmap_format_a8_r8_g8_b8:
	case _bitmap_format_a4_r4_g4_b4:
	case _bitmap_format_r5_g6_b5:
		value = 32;
		break;

	default:
		value = 128;
		break;
	}

	return (image->width % value == 0) ? image->width : image->width + (value - (image->width % value));
}

long bitmap_image_get_virtual_height(
	s_bitmap_image *image)
{
	long value = 0;

	switch (image->format.operator e_bitmap_format())
	{
	case _bitmap_format_a8:
	case _bitmap_format_y8:
	case _bitmap_format_ay8:
	case _bitmap_format_a8_y8:
	case _bitmap_format_a8_r8_g8_b8:
	case _bitmap_format_a4_r4_g4_b4:
	case _bitmap_format_r5_g6_b5:
		value = 32;
		break;

	default:
		value = 128;
		break;
	}

	return (image->height % value == 0) ? image->height : image->height + (value - (image->height % value));
}

long bitmap_image_get_resource_length(
	s_bitmap_image *image)
{
	long length = 0;

	auto virtual_width = bitmap_image_get_virtual_width(image);
	auto virtual_height = bitmap_image_get_virtual_height(image);

	switch (image->format.operator e_bitmap_format())
	{
	case _bitmap_format_ctx1:
	case _bitmap_format_dxt1:
	case _bitmap_format_dxt3a_mono:
	case _bitmap_format_dxt3a_alpha:
	case _bitmap_format_dxt5a:
	case _bitmap_format_dxt5a_mono:
	case _bitmap_format_dxt5a_alpha:
		length = virtual_width * virtual_height / 2;
		break;

	case _bitmap_format_a8:
	case _bitmap_format_y8:
	case _bitmap_format_ay8:
	case _bitmap_format_dxt3:
	case _bitmap_format_dxt5:
	case _bitmap_format_dxn:
	case _bitmap_format_dxn_mono_alpha:
	case _bitmap_format_a4_r4_g4_b4_font:
		length = virtual_width / virtual_height;
		break;

	case _bitmap_format_a4_r4_g4_b4:
	case _bitmap_format_a1_r5_g5_b5:
	case _bitmap_format_a8_y8:
	case _bitmap_format_r5_g6_b5:
		length = virtual_width * virtual_height * 2;
		break;

	case _bitmap_format_a8_r8_g8_b8:
	case _bitmap_format_x8_r8_g8_b8:
		length = virtual_width * virtual_height * 4;
		break;

	case _bitmap_format_unused_1e:
		length = virtual_width * virtual_height * 8;
		break;
	}

	if (image->type == _bitmap_type_cube_map)
		length *= 6;

	return length;
}

long bitmap_image_get_block_size(
	s_bitmap_image *image)
{
	return NONE;
}
