#pragma once

#include <cseries/cseries.h>
#include <commands/commands.h>
#include <commands/editing_commands.h>
#include <tag_files/tag_definitions.h>
#include <bitmaps/bitmaps.h>
#include <bitmaps/bitmap_definitions.h>

/* ---------- classes */

class c_bitmap_command_context : public c_editing_command_context
{
public:
	c_bitmap_command_context(
		char const *name,
		s_bitmap_definition *bitmap,
		c_cache_file_reach *file,
		c_command_context *parent = nullptr);

	s_bitmap_definition *get_bitmap();

protected:
	s_bitmap_definition *m_bitmap;
};

/* ---------- prototypes/BITMAP_COMMANDS.CPP */

bool extract_bitmap_execute(long arg_count, char const **arg_values);
bool inject_bitmap_execute(long arg_count, char const **arg_values);

/* ---------- constants */

extern __declspec(selectany)
s_command const k_bitmap_commands[] =
{
	{
		"extract_bitmap",
		"extract_bitmap <image_index> <out_filename>",
		"Extracts the bitmap image_definition at the specified index to the provided out_filename.",
		false,
		extract_bitmap_execute
	},
	{
		"inject_bitmap",
		"inject_bitmap <image_index> <filename>",
		"Injects the image file to the bitmap image_definition at the specified index.",
		false,
		extract_bitmap_execute
	}
};

extern __declspec(selectany)
s_command_set const k_bitmap_command_sets[] =
{
	{ NUMBEROF(k_editing_commands), k_editing_commands },
	{ NUMBEROF(k_bitmap_commands), k_bitmap_commands }
};
