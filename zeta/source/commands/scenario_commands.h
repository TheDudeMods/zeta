#pragma once

#include <cseries/cseries.h>
#include <cache/cache_file_tag_resources.h>
#include <scenario/scenario.h>
#include <commands/commands.h>
#include <commands/editing_commands.h>

/* ---------- classes */

class c_scenario_command_context : public c_editing_command_context
{
public:
	c_scenario_command_context(
		char const *name,
		s_scenario *scenario,
		c_cache_file_reach *file,
		c_command_context *parent = nullptr);

	s_scenario *get_scenario();

protected:
	s_scenario *m_scenario;
};

/* ---------- prototypes/RENDER_MODEL_COMMANDS.CPP */

bool extract_rain_render_geometry_execute(long arg_count, char const **arg_values);
bool extract_structure_render_geometry_execute(long arg_count, char const **arg_values);

/* ---------- constants */

extern __declspec(selectany)
s_command const k_scenario_commands[] =
{
	{
		"extract_rain_render_geometry",
		"extract_structure_render_geometry <structure_index> <filename>",
		"Extracts the render_geometry from the structure at the specified index to the provided filename.",
		false,
		extract_rain_render_geometry_execute
	},
	{
		"extract_structure_render_geometry",
		"extract_structure_render_geometry <structure_index> <filename>",
		"Extracts the render_geometry from the structure at the specified index to the provided filename.",
		false,
		extract_structure_render_geometry_execute
	},
};

extern __declspec(selectany)
s_command_set const k_scenario_command_sets[] =
{
	{ NUMBEROF(k_editing_commands), k_editing_commands },
	{ NUMBEROF(k_scenario_commands), k_scenario_commands }
};
