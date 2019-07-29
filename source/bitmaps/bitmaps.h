#pragma once

#include <cseries/cseries.h>
#include <bitmaps/bitmap_definitions.h>
#include <bitmaps/dds.h>

/* ---------- prototypes/BITMAPS.CPP */

void bitmap_texture_initialize_dds_header(
	s_bitmap_image *image,
	s_bitmap_texture_resource *resource,
	struct s_dds_header *header);
