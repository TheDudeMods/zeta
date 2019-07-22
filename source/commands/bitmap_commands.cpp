#include <commands/bitmap_commands.h>
#include <cache/cache_files.h>

/* ---------- constants */

enum
{
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

	auto resource_entry = &editing_context->get_bitmap()->resources[image_index];
	char *resource_data = nullptr;
	
	g_cache_file->tag_resource_try_and_get(resource_entry->resource_index, NONE, (void **)&resource_data);

	return true;
}
