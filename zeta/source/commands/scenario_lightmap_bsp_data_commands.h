#pragma once
#pragma once

#include <cseries/cseries.h>
#include <cache/cache_file_tag_resources.h>
#include <scenario/structure_lightmap_definitions.h>
#include <commands/commands.h>
#include <commands/editing_commands.h>

#include <cstdio>

/* ---------- classes */

class c_scenario_lightmap_bsp_data_command_context : public c_editing_command_context
{
public:
	c_scenario_lightmap_bsp_data_command_context(
		char const *name,
		s_scenario_lightmap_bsp_data *scenario_lightmap_bsp_data,
		c_cache_file_reach *file,
		c_command_context *parent = nullptr);

	s_scenario_lightmap_bsp_data *get_scenario_lightmap_bsp_data();

protected:
	s_scenario_lightmap_bsp_data *m_scenario_lightmap_bsp_data;
};

/* ---------- prototypes/RENDER_MODEL_COMMANDS.CPP */

bool extract_lightmap_render_geometry_execute(long arg_count, char const **arg_values);

/* ---------- constants */

extern __declspec(selectany)
s_command const k_scenario_lightmap_bsp_data_commands[] =
{
	{
		"extract_lightmap_render_geometry",
		"extract_lightmap_render_geometry <filename>",
		"Extracts the current scenario_lightmap_bsp_data render_geometry to the provided filename.",
		false,
		extract_lightmap_render_geometry_execute
	}
};

extern __declspec(selectany)
s_command_set const k_scenario_lightmap_bsp_data_command_sets[] =
{
	{ NUMBEROF(k_editing_commands), k_editing_commands },
	{ NUMBEROF(k_scenario_lightmap_bsp_data_commands), k_scenario_lightmap_bsp_data_commands }
};
