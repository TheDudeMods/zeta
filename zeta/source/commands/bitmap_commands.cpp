#include <commands/bitmap_commands.h>
#include <cache/cache_files.h>
#include <cache/cache_file_tag_resources.h>

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>

/* ---------- constants */

enum
{
	k_number_of_bitmap_commands = 1,
	k_number_of_bitmap_command_sets = 2
};

/* ---------- globals */

extern s_tag_group bitmap_group;

static s_command g_bitmap_commands[k_number_of_bitmap_commands] =
{
	{
		"extract_bitmap",
		"extract_bitmap <image_index> <filename>",
		"Extracts the bitmap image at the specified index to the provided filename.",
		false,
		extract_bitmap_execute
	}
};

static s_command_set g_bitmap_command_sets[k_number_of_bitmap_command_sets] =
{
	{ k_number_of_editing_commands, g_editing_commands },
	{ k_number_of_bitmap_commands, g_bitmap_commands }
};

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
	m_command_set_count = k_number_of_bitmap_command_sets;
	m_command_sets = g_bitmap_command_sets;
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
	auto filename = arg_values[1];

	auto editing_context = dynamic_cast<c_bitmap_command_context *>(g_command_context);
	auto file = editing_context->get_file();

	if (!editing_context)
	{
		puts("ERROR: invalid command context!");
		return true;
	}

	auto bitmap = editing_context->get_bitmap();

	s_bitmap_image *image = nullptr;
	if (!bitmap->images.try_get_element(file, image_index, &image) || !image)
	{
		printf("ERROR: Invalid image index: %ul\n", image_index);
		return true;
	}

	s_bitmap_resource_info *resource_info = nullptr;
	if (!bitmap->resources.try_get_element(file, image_index, &resource_info) || !resource_info)
	{
		printf("ERROR: Invalid image index: %ul\n", image_index);
		return true;
	}

	c_cache_file_reach_tag_resource<s_bitmap_texture_interop_resource> bitmap_resource(file, resource_info->resource_index);
	auto image_resource = (s_bitmap_texture_resource *)bitmap_resource.get_data(bitmap_resource->bitmap.address);

	s_dds_header dds_header;
	bitmap_image_initialize_dds_header(image, image_resource, &dds_header);

	FILE *stream = fopen(arg_values[1], "wb+");
	fwrite(&dds_header, sizeof(s_dds_header), 1, stream);
	fwrite(bitmap_resource.get_data(), image->pixel_data_length, 1, stream);
	fclose(stream);

	printf("Wrote \"%s\" successfully.\n", arg_values[1]);

	return true;
}
