#pragma once

#include <cseries/cseries.h>
#include <commands/commands.h>
#include <commands/editing_commands.h>
#include <tag_files/tag_definitions.h>
#include <bitmaps/bitmaps.h>

/* ---------- constants */

enum
{
	k_number_of_bitmap_commands = 4
};

/* ---------- globals */

extern s_command g_bitmap_commands[k_number_of_bitmap_commands];

/* ---------- classes */

class c_bitmap_command_context : public c_editing_command_context
{
public:
	c_bitmap_command_context(
		char const *name,
		s_bitmap_definition *bitmap,
		c_command_context *parent = nullptr);

	s_bitmap_definition *get_bitmap();

protected:
	s_bitmap_definition *m_bitmap;
};

/* ---------- prototypes/BITMAP_COMMANDS.CPP */

bool extract_bitmap_execute(long arg_count, char const **arg_values);
