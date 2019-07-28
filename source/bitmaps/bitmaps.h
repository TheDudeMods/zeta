#pragma once

#include <cseries/cseries.h>
#include <bitmaps/bitmap_definitions.h>
#include <bitmaps/dds.h>

/* ---------- prototypes/BITMAPS.CPP */

void bitmap_image_initialize_dds_header(
	s_bitmap_image *image,
	struct s_dds_header *header);
