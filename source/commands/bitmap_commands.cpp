#include <commands/bitmap_commands.h>
#include <cache/cache_files.h>
#include <cache/cache_file_tag_resources.h>

/* ---------- constants */

enum
{
	k_number_of_bitmap_commands = 1,
	k_number_of_bitmap_command_sets = 2
};

/* ---------- globals */

extern s_tag_group_definition bitmap_group;

s_command g_bitmap_commands[k_number_of_bitmap_commands] =
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
	c_command_context *parent) :
	c_editing_command_context(
		name,
		bitmap,
		&bitmap_group,
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

	auto editing_context = (c_bitmap_command_context *)g_command_context;

	auto address = editing_context->get_address();
	auto definition = editing_context->get_definition();

	auto bitmap = editing_context->get_bitmap();

	auto image_entry = &bitmap->images[image_index];
	auto resource_entry = &bitmap->resources[image_index];

	auto bitmap_resource_definition = g_cache_file->tag_resource_definition_get<s_bitmap_texture_interop_resource>(
		resource_entry->resource_index);

	long resource_length = 0;
	byte *resource_data = nullptr;

	if (!g_cache_file->tag_resource_try_and_get(resource_entry->resource_index, &resource_length, (void **)&resource_data))
	{
		printf("ERROR: failed to retrieve tag resource 0x%08lX!\n", resource_entry->resource_index);
		return true;
	}

	c_cache_file_tag_resource<s_bitmap_texture_interop_resource> resource(bitmap_resource_definition, resource_data);
	auto bitmap_resource = (s_bitmap_texture_resource *)resource.get_address(bitmap_resource_definition->bitmap.address);

	s_dds_header dds_header;
	bitmap_texture_initialize_dds_header(image_entry, bitmap_resource, &dds_header);

	FILE *stream = fopen(arg_values[1], "wb+");
	fwrite(&dds_header, sizeof(s_dds_header), 1, stream);
	fwrite(resource.get_address(bitmap_resource->data.address), bitmap_resource->data.size, 1, stream);
	fclose(stream);

	printf("Wrote \"%s\" successfully.\n", arg_values[1]);

	if (resource_data)
		delete[] resource_data;

	return true;
}
