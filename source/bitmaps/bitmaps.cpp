#include <bitmaps/bitmaps.h>

/* ---------- private globals */


static struct
{
	e_bitmap_format bitmap_format;
	e_dds_format_type dds_format_type;
	dword four_cc;
	dword rgb_bit_count;
	long r_bitmask;
	long g_bitmask;
	long b_bitmask;
	long a_bitmask;
} g_bitmap_pixel_formats[k_number_of_bitmap_formats] =
{
{
	_bitmap_format_a8,
	_dds_format_type_alpha,
	0, 8, 0, 0, 0, 0xFF
},
{
	_bitmap_format_y8,
	_dds_format_type_luminance,
	0, 8, 0xFF, 0, 0, 0
},
{
	_bitmap_format_ay8,
	_dds_format_type_alpha,
	0, 8, 0, 0, 0, 0xFF
},
{
	_bitmap_format_a8_y8,
	_dds_format_type_rgb,
	0, 16, 0x00FF, 0, 0, 0xFF00
},
{
	_bitmap_format_r5_g6_b5,
	_dds_format_type_rgb,
	0, 16, 0xF800, 0x07E0, 0x001F, 0
},
{
	_bitmap_format_a1_r5_g5_b5,
	_dds_format_type_rgb,
	0, 16, 0x7C00, 0x03E0, 0x001F, 0x8000
},
{
	_bitmap_format_a4_r4_g4_b4,
	_dds_format_type_rgb,
	0, 16, 0x0F00, 0x00F0, 0x000F, 0xF000
},
//
// TODO
//
};

/* ---------- code */

void bitmap_image_initialize_dds_header(
	s_bitmap_image *image,
	s_dds_header *header)
{
	assert(image);
	assert(header);

	header->size = sizeof(s_dds_header);
	
	//
	// TODO
	//
}
