#pragma once

#include <cseries/cseries.h>
#include <cache/cache_file_tag_resources.h>
#include <structures/structure_bsp_definitions.h>
#include <commands/commands.h>
#include <commands/editing_commands.h>

#include <cstdio>

/* ---------- classes */

class c_structure_design_command_context : public c_editing_command_context
{
public:
	c_structure_design_command_context(
		char const *name,
		s_structure_design_definition *structure_design,
		c_cache_file_reach *file,
		c_command_context *parent = nullptr);

	s_structure_design_definition *get_structure_design();

protected:
	s_structure_design_definition *m_structure_design;
};

/* ---------- prototypes/RENDER_MODEL_COMMANDS.CPP */

bool extract_rain_geometry_execute(long arg_count, char const **arg_values);

/* ---------- constants */

extern __declspec(selectany)
s_command const k_structure_design_commands[] =
{
	{
		"extract_rain_geometry",
		"extract_rain_geometry <filename>",
		"Extracts the current structure_design to the provided filename.",
		false,
		extract_rain_geometry_execute
	}
};

extern __declspec(selectany)
s_command_set const k_structure_design_command_sets[] =
{
	{ NUMBEROF(k_editing_commands), k_editing_commands },
	{ NUMBEROF(k_structure_design_commands), k_structure_design_commands }
};
