#pragma once

#include <cseries/cseries.h>
#include <cache/cache_file_tag_resources.h>
#include <models/render_model_definitions.h>
#include <geometry/geometry_definitions.h>
#include <commands/commands.h>
#include <commands/editing_commands.h>

/* ---------- classes */

class c_render_model_command_context : public c_editing_command_context
{
public:
	c_render_model_command_context(
		char const *name,
		s_render_model_definition *render_model,
		c_cache_file_reach *file,
		c_command_context *parent = nullptr);

	s_render_model_definition *get_render_model();

protected:
	s_render_model_definition *m_render_model;
};

/* ---------- prototypes/RENDER_MODEL_COMMANDS.CPP */

long mesh_stream_to_obj_file(
	c_cache_file_reach *file,
	c_cache_file_reach_tag_resource<s_render_geometry_api_resource_definition> &geometry_resource,
	long base_index,
	s_compression_info *compression_info,
	char const *mesh_name,
	s_mesh *mesh,
	FILE *obj_stream,
	real_point3d offset = real_point3d());

bool extract_render_model_execute(long arg_count, char const **arg_values);

/* ---------- constants */

extern __declspec(selectany)
s_command const k_render_model_commands[] =
{
	{
		"extract_render_model",
		"extract_render_model <filename>",
		"Extracts the current render_model to the provided filename.",
		false,
		extract_render_model_execute
	}
};

extern __declspec(selectany)
s_command_set const k_render_model_command_sets[] =
{
	{ NUMBEROF(k_editing_commands), k_editing_commands },
	{ NUMBEROF(k_render_model_commands), k_render_model_commands }
};
