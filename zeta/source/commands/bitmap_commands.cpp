#include <commands/bitmap_commands.h>
#include <cache/cache_files.h>
#include <cache/cache_file_tag_resources.h>

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>

extern s_tag_group bitmap_group;

/* ---------- code */

c_bitmap_command_context::c_bitmap_command_context(
	char const *name,
	s_bitmap_definition *bitmap,
	c_cache_file_reach *file,
	c_command_context *parent) :
	c_editing_command_context(
		name,
		bitmap,
		&bitmap_group,
		file,
		parent),
	m_bitmap(bitmap)
{
	m_command_set_count = NUMBEROF(k_bitmap_command_sets);
	m_command_sets = k_bitmap_command_sets;
}

s_bitmap_definition *c_bitmap_command_context::get_bitmap()
{
	return m_bitmap;
}

bool extract_bitmap_execute(
	long arg_count,
	char const ** arg_values)
{
	if (arg_count != 2)
		return false;

	auto image_index = strtoul(arg_values[0], nullptr, 0);
	auto out_filename = arg_values[1];

	auto bitmap_context = g_command_context->get_context<c_bitmap_command_context>();

	if (!bitmap_context)
	{
		puts("ERROR: invalid command context!");
		return true;
	}

	auto cache_file = bitmap_context->get_file();
	auto bitmap = bitmap_context->get_bitmap();
	auto image_definition = bitmap->images.get_element(cache_file, image_index);
	auto image_resource_handle = bitmap->resources.get_element(cache_file, image_index);

	if (!image_definition || !image_resource_handle)
	{
		printf("ERROR: invalid image_definition index: %ul\n", image_index);
		return true;
	}

	auto bitmap_resource = c_cache_file_reach_tag_resource<s_bitmap_texture_interop_resource>(
		cache_file, image_resource_handle->resource_index);

	auto image_resource = bitmap_resource.get_data<s_bitmap_texture_resource>(
		bitmap_resource->bitmap.address);

	s_dds_header dds_header;
	bitmap_image_initialize_dds_header(image_definition, &dds_header);

	FILE *stream = fopen(arg_values[1], "wb+");
	
	fwrite(&dds_header, sizeof(s_dds_header), 1, stream);
	
	auto bitmap_resource_length = bitmap_resource.get_data_length();
	auto predicted_resource_length = bitmap_image_get_resource_length(image_definition);

	fwrite(
		bitmap_resource.get_data<char>() + image_definition->pixel_data_offset,
		predicted_resource_length,
		sizeof(char),
		stream);

	fclose(stream);

	printf("Wrote \"%s\" successfully.\n", arg_values[1]);

	return true;
}

bool inject_bitmap_execute(
	long arg_count,
	char const **arg_values)
{
	if (arg_count != 2)
		return false;

	auto image_index = strtoul(arg_values[0], nullptr, 0);
	auto filename = arg_values[1];

	auto bitmap_context = g_command_context->get_context<c_bitmap_command_context>();

	if (!bitmap_context)
	{
		puts("ERROR: invalid command context!");
		return true;
	}

	auto cache_file = bitmap_context->get_file();
	auto bitmap = bitmap_context->get_bitmap();
	auto image_definition = bitmap->images.get_element(cache_file, image_index);

	if (!image_definition)
	{
		printf("ERROR: invalid image_definition index: %ul\n", image_index);
		return true;
	}

	/* ------ read the dds file */

	auto dds_stream = fopen(filename, "rb+");

	fseek(dds_stream, 0, SEEK_END);
	auto dds_data_length = ftell(dds_stream) - sizeof(s_dds_header);

	fseek(dds_stream, 0, SEEK_SET);

	s_dds_header dds_header;
	fread(&dds_header, sizeof(s_dds_header), 1, dds_stream);

	auto dds_data = new uchar[dds_data_length];
	fread(dds_data, sizeof(uchar), dds_data_length, dds_stream);

	fclose(dds_stream);

	/* ------ build a new resource */

	//
	// TODO: build new resource
	//

	/* ------ update the bitmap image */

	//
	// TODO: update bitmap image
	//

	/* ------ cleanup */

	delete[] dds_data;

	return true;
}
