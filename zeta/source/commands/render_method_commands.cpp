#include <tag_files/tag_groups.h>
#include <tag_files/tag_resource_internals.h>
#include <cache/cache_file_tag_resources.h>
#include <commands/render_method_commands.h>

#include <cstdio>

extern s_tag_group render_method_group;

/* ---------- code */

extern s_tag_group render_method_group;

c_render_method_command_context::c_render_method_command_context(
	char const *name,
	c_render_method *render_method,
	c_cache_file_reach *file,
	c_command_context *parent) :
	c_editing_command_context(
		name,
		render_method,
		&render_method_group,
		file,
		parent),
	m_render_method(render_method)
{
	m_command_set_count = NUMBEROF(k_render_method_command_sets);
	m_command_sets = k_render_method_command_sets;
}

c_render_method *c_render_method_command_context::get_render_method()
{
	return m_render_method;
}

struct s_constant_buffer_parameter_data
{
	s_tag_data data;
};
static_assert(sizeof(s_constant_buffer_parameter_data) == 0x14);

struct s_constant_buffer_pool_definition
{
	c_tag_resource_structure<s_constant_buffer_parameter_data> parameters;
};
static_assert(sizeof(s_constant_buffer_pool_definition) == 0xC);

struct s_constant_buffer_definition
{
	c_tag_block<s_constant_buffer_pool_definition> pool;
};
static_assert(sizeof(s_constant_buffer_definition) == 0xC);

struct s_constant_buffer_parameters
{
	real value1;
	real value2;
	real value3;
	real value4;
};
static_assert(sizeof(s_constant_buffer_parameters) == 0x10);

bool extract_render_method_constants_execute(
	long arg_count,
	char const **arg_values)
{
	if (arg_count > 1)
		return false;

	auto render_method_context = g_command_context->get_context<c_render_method_command_context>();
	auto cache_file = render_method_context->get_file();

	if (!render_method_context)
	{
		puts("ERROR: invalid render_method command context!");
		return true;
	}

	auto render_method = render_method_context->get_render_method();

	if (!render_method)
	{
		printf("ERROR: render_method definition is null!");
		return true;
	}

	auto postprocess_definition = render_method->postprocess_definitions.get_element(cache_file, 0);

	auto constant_buffer_resource = c_cache_file_reach_tag_resource<s_constant_buffer_definition>(
		cache_file, postprocess_definition->resource_index);

	auto constant_buffer_unknowns = constant_buffer_resource.get_data<s_constant_buffer_pool_definition>(
		constant_buffer_resource->pool.address);

	for (auto i = 0; i < constant_buffer_resource->pool.count; i++)
	{
		auto parameter_data = constant_buffer_resource.get_data<s_constant_buffer_parameter_data>(
			constant_buffer_unknowns[i].parameters.address);

		auto parameters = constant_buffer_resource.get_data<s_constant_buffer_parameters>(
			parameter_data->data.address);

		if (!parameters) continue;
	}

	return true;
}
