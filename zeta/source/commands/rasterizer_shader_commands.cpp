#include <commands/rasterizer_shader_commands.h>
#include <cache/cache_files.h>

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>

/* ---------- constants */

enum
{
	k_number_of_rasterizer_shader_commands = 1,
	k_number_of_rasterizer_shader_command_sets = 2
};

/* ---------- globals */

extern s_tag_group_definition pixel_shader_group;
extern s_tag_group_definition vertex_shader_group;

static s_command g_bitmap_commands[k_number_of_rasterizer_shader_commands] =
{
	{
		"extract_shader_files",
		"extract_shader_files <compiled_shader_index> <filename>",
		"Extracts the compiled shaders at the specified index to the provided filename.",
		false,
		extract_shader_files_execute
	}
};

static s_command_set g_bitmap_command_sets[k_number_of_rasterizer_shader_command_sets] =
{
	{ k_number_of_editing_commands, g_editing_commands },
	{ k_number_of_rasterizer_shader_commands, g_bitmap_commands }
};

/* ---------- code */

c_rasterizer_shader_command_context::c_rasterizer_shader_command_context(
	char const *name,
	c_rasterizer_shader *rasterizer_shader,
	s_tag_group_definition *definition,
	c_cache_file_reach *file,
	c_command_context *parent) :
	c_editing_command_context(
		name,
		rasterizer_shader,
		definition,
		file,
		parent),
	m_rasterizer_shader(rasterizer_shader)
{
	m_command_set_count = k_number_of_rasterizer_shader_command_sets;
	m_command_sets = g_bitmap_command_sets;
}

c_rasterizer_shader *c_rasterizer_shader_command_context::get_rasterizer_shader()
{
	return m_rasterizer_shader;
}

c_pixel_shader_command_context::c_pixel_shader_command_context(
	char const *name,
	c_rasterizer_pixel_shader *pixel_shader,
	c_cache_file_reach *file,
	c_command_context *parent) :
	c_rasterizer_shader_command_context(
		name,
		pixel_shader,
		&pixel_shader_group,
		file,
		parent)
{
}

c_vertex_shader_command_context::c_vertex_shader_command_context(
	char const *name,
	c_rasterizer_vertex_shader *vertex_shader,
	c_cache_file_reach *file,
	c_command_context *parent) :
	c_rasterizer_shader_command_context(
		name,
		vertex_shader,
		&vertex_shader_group,
		file,
		parent)
{
}

bool extract_shader_files_execute(
	long arg_count,
	char const **arg_values)
{
	if (arg_count != 3)
		return false;

	auto compiled_shader_index = strtoul(arg_values[0], nullptr, 0);
	auto filename1 = arg_values[1];
	auto filename2 = arg_values[2];

	auto editing_context = dynamic_cast<c_rasterizer_shader_command_context *>(g_command_context);
	auto file = editing_context->get_file();

	if (!editing_context)
	{
		puts("ERROR: invalid command context!");
		return true;
	}

	auto rasterizer_shader = editing_context->get_rasterizer_shader();
	auto compiled_shader = rasterizer_shader->compiled_shaders.get_element(file, compiled_shader_index);

	if (!compiled_shader)
	{
		printf("ERROR: invalid compiled shader index: %ul\n", compiled_shader_index);
		return true;
	}

	printf("%s", "Extracting shader files...");

	auto stream1 = fopen(filename1, "wb");
	fwrite(file->get_tags_section_pointer_from_page_offset<uchar>(compiled_shader->pc_data.address), sizeof(uchar), compiled_shader->pc_data.size, stream1);
	fclose(stream1);

	auto stream2 = fopen(filename2, "wb");
	fwrite(file->get_tags_section_pointer_from_page_offset<uchar>(compiled_shader->unknown2C.address), sizeof(uchar), compiled_shader->unknown2C.size, stream2);
	fclose(stream2);

	printf("%s\n", "done.");

	return true;
}
