#pragma once

#include <cseries/cseries.h>
#include <datatypes/flags.h>
#include <datatypes/tag.h>

/* ---------- enumerators */

enum e_dds_format_type
{
	_dds_format_type_rgb,
	_dds_format_type_yuv,
	_dds_format_type_luminance,
	_dds_format_type_alpha,
	_dds_format_type_other,
	k_number_of_dds_format_types
};

enum e_dds_format_flags
{
	_dds_format_alpha_pixels_bit,
	_dds_format_alpha_bit,
	_dds_format_four_cc_bit,
	_dds_format_palette_indexed4_bit,
	_dds_format_palette_indexed_t08_bit,
	_dds_format_palette_indexed8_bit,
	_dds_format_rgb_bit,
	_dds_format_compressed_bit,
	_dds_format_rgb_to_yuv_bit,
	_dds_format_yuv_bit,
	_dds_format_z_buffer_bit,
	_dds_format_palette_indexed1_bit,
	_dds_format_palette_indexed2_bit,
	_dds_format_z_pixels_bit,
	_dds_format_stencil_buffer_bit,
	_dds_format_premultiplied_alpha_bit,
	_dds_format_luminance_bit,
	_dds_format_bump_luminance_bit,
	_dds_format_bump_dudv_bit,
	k_number_of_dds_format_flags
};

enum e_dds_header_flags
{
	_dds_header_caps_bit,
	_dds_header_height_bit,
	_dds_header_width_bit,
	_dds_header_pitch_bit,
	_dds_header_unused4_bit,
	_dds_header_unused5_bit,
	_dds_header_unused6_bit,
	_dds_header_unused7_bit,
	_dds_header_unused8_bit,
	_dds_header_unused9_bit,
	_dds_header_unused10_bit,
	_dds_header_unused11_bit,
	_dds_header_pixel_format_bit,
	_dds_header_unused13_bit,
	_dds_header_unused14_bit,
	_dds_header_unused15_bit,
	_dds_header_unused16_bit,
	_dds_header_mipmap_count_bit,
	_dds_header_unused18_bit,
	_dds_header_linear_size_bit,
	_dds_header_unused20_bit,
	_dds_header_unused21_bit,
	_dds_header_unused22_bit,
	_dds_header_depth_bit,
	k_number_of_dds_header_flags
};

/* ---------- structures */

struct s_dds_pixel_format
{
	ulong size;
	c_flags<e_dds_format_flags, long> flags;
	ulong four_cc;
	long r_bitmask;
	ulong bits_per_pixel;
	long g_bitmask;
	long b_bitmask;
	long a_bitmask;
};
static_assert(sizeof(s_dds_pixel_format) == 0x20);

struct s_dds_header
{
	tag four_cc;
	ulong size;
	c_flags<e_dds_header_flags, long> flags;
	ulong height;
	ulong width;
	ulong pitch_or_linear_size;
	ulong depth;
	ulong mipmap_count;
	ulong reserved1[11];
	s_dds_pixel_format pixel_format;
	ulong caps[4];
	ulong reserved2;
};
static_assert(sizeof(s_dds_header) == 0x80);
