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
		"extract_bitmap <image_index> <out_filename>",
		"Extracts the bitmap image_definition at the specified index to the provided out_filename.",
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
	auto out_filename = arg_values[1];

	auto bitmap_context = g_command_context->get_context<c_bitmap_command_context>();
	auto cache_file = bitmap_context->get_file();

	if (!bitmap_context)
	{
		puts("ERROR: invalid command context!");
		return true;
	}

	auto bitmap = bitmap_context->get_bitmap();

	if (!bitmap)
	{
		printf("ERROR: bitmap definition is null!");
		return true;
	}

	auto image_definition = bitmap->images.get_element(cache_file, image_index);
	auto image_resource_handle = bitmap->resources.get_element(cache_file, image_index);

	if (!image_definition || !image_resource_handle)
	{
		printf("ERROR: Invalid image_definition index: %ul\n", image_index);
		return true;
	}

	auto bitmap_resource = c_cache_file_reach_tag_resource<s_bitmap_texture_interop_resource>(
		cache_file, image_resource_handle->resource_index);

	auto image_resource = bitmap_resource.get_data<s_bitmap_texture_resource>(
		bitmap_resource->bitmap.address);

	s_dds_header dds_header;
	bitmap_image_initialize_dds_header(image_definition, image_resource, &dds_header);

	FILE *stream = fopen(arg_values[1], "wb+");
	
	fwrite(&dds_header, sizeof(s_dds_header), 1, stream);
	
	fwrite(
		bitmap_resource.get_data<char>() + image_definition->pixel_data_offset,
		bitmap_resource.get_data_length(), // <--- TODO: find better length
		sizeof(char),
		stream);

	fclose(stream);

	printf("Wrote \"%s\" successfully.\n", arg_values[1]);

	return true;
}
