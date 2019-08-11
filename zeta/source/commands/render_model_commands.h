#pragma once

#include <cseries/cseries.h>
#include <commands/commands.h>
#include <commands/editing_commands.h>
#include <models/render_model_definitions.h>

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

bool extract_render_model_execute(long arg_count, char const **arg_values);
