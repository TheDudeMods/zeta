#pragma once

#include <cseries/cseries.h>
#include <commands/commands.h>
#include <commands/editing_commands.h>
#include <rasterizer/rasterizer_shader_definitions.h>

/* ---------- classes */

class c_rasterizer_shader_command_context :
	public c_editing_command_context
{
public:
	c_rasterizer_shader_command_context(
		char const *name,
		c_rasterizer_shader *rasterizer_shader,
		s_tag_group *definition,
		c_cache_file_reach *file,
		c_command_context *parent = nullptr);

	c_rasterizer_shader *get_rasterizer_shader();

protected:
	c_rasterizer_shader *m_rasterizer_shader;
};

class c_pixel_shader_command_context :
	public c_rasterizer_shader_command_context
{
public:
	c_pixel_shader_command_context(
		char const *name,
		c_rasterizer_pixel_shader *pixel_shader,
		c_cache_file_reach *file,
		c_command_context *parent = nullptr);
};

class c_vertex_shader_command_context :
	public c_rasterizer_shader_command_context
{
public:
	c_vertex_shader_command_context(
		char const *name,
		c_rasterizer_vertex_shader *vertex_shader,
		c_cache_file_reach *file,
		c_command_context *parent = nullptr);
};

/* ---------- prototypes/RASTERIZER_SHADER_COMMANDS.CPP */

bool extract_shader_files_execute(long arg_count, char const **arg_values);

/* ---------- constants */

extern __declspec(selectany)
s_command const k_rasterizer_shader_commands[] =
{
	{
		"extract_shader_files",
		"extract_shader_files <compiled_shader_index> <filename>",
		"Extracts the compiled shaders at the specified index to the provided filename.",
		false,
		extract_shader_files_execute
	}
};

extern __declspec(selectany)
s_command_set const k_rasterizer_shader_command_sets[] =
{
	{ NUMBEROF(k_editing_commands), k_editing_commands },
	{ NUMBEROF(k_rasterizer_shader_commands), k_rasterizer_shader_commands }
};
