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
	header->height = resource->height;
	header->width = resource->width;
	header->depth = resource->depth;
	header->mipmap_count = resource->mipmap_count >= 1;

	header->pixel_format.size = sizeof(s_dds_pixel_format);
}
