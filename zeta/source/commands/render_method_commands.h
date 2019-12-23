#pragma once

#include <cseries/cseries.h>
#include <commands/commands.h>
#include <commands/editing_commands.h>
#include <tag_files/tag_definitions.h>
#include <render_methods/render_method_definitions.h>

/* ---------- classes */

class c_render_method_command_context : public c_editing_command_context
{
public:
	c_render_method_command_context(
		char const *name,
		c_render_method *render_method,
		c_cache_file_reach *file,
		c_command_context *parent = nullptr);

	c_render_method *get_render_method();

protected:
	c_render_method *m_render_method;
};

/* ---------- prototypes/BITMAP_COMMANDS.CPP */

bool extract_render_method_constants_execute(long arg_count, char const **arg_values);

/* ---------- constants */

extern __declspec(selectany)
s_command const k_render_method_commands[] =
{
	{
		"extract_render_method_constants",
		"extract_render_method_constants [out_filename]",
		"Extracts the render_method constants to the provided out_filename (if provided).",
		false,
		extract_render_method_constants_execute
	}
};

extern __declspec(selectany)
s_command_set const k_render_method_command_sets[] =
{
	{ NUMBEROF(k_editing_commands), k_editing_commands },
	{ NUMBEROF(k_render_method_commands), k_render_method_commands }
};
