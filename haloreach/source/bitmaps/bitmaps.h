#pragma once

#include <cseries/cseries.h>
#include <bitmaps/bitmap_definitions.h>
#include <bitmaps/dds.h>

/* ---------- prototypes/BITMAPS.CPP */

void bitmap_image_initialize_dds_header(
	s_bitmap_image *image,
	s_dds_header *header);

void bitmap_image_apply_dds_header(
	s_bitmap_image *image,
	s_dds_header *header);

long bitmap_image_get_virtual_width(
	s_bitmap_image *image);

long bitmap_image_get_virtual_height(
	s_bitmap_image *image);

long bitmap_image_get_resource_length(
	s_bitmap_image *image);

long bitmap_image_get_block_size(
	s_bitmap_image *image);
