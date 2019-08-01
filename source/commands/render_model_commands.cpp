
#define WIN32_LEAN_AND_MEAN
#include <d3d11.h>

#include <cache/cache_file_tag_resources.h>
#include <commands/render_model_commands.h>
#include <geometry/geometry_definitions.h>

/* ---------- constants */

enum
{
	k_number_of_render_model_commands = 1,
	k_number_of_render_model_command_sets = 2
};

/* ---------- globals */

extern s_tag_group_definition render_model_group;

s_command g_render_model_commands[k_number_of_render_model_commands] =
{
	{
		"extract_render_model",
		"extract_render_model <filename>",
		"Extracts the current render_model to the provided filename.",
		false,
		extract_render_model_execute
	}
};

static s_command_set g_render_model_command_sets[k_number_of_render_model_command_sets] =
{
	{ k_number_of_editing_commands, g_editing_commands },
	{ k_number_of_render_model_commands, g_render_model_commands }
};

/* ---------- code */

c_render_model_command_context::c_render_model_command_context(
	char const *name,
	s_render_model_definition *render_model,
	c_command_context *parent) :
	c_editing_command_context(
		name,
		render_model,
		&render_model_group,
		parent),
	m_render_model(render_model)
{
	m_command_set_count = k_number_of_render_model_command_sets;
	m_command_sets = g_render_model_command_sets;
}

s_render_model_definition *c_render_model_command_context::get_render_model()
{
	return m_render_model;
}

bool extract_render_model_execute(
	long arg_count,
	char const **arg_values)
{
	if (arg_count != 1)
		return false;

	auto context = (c_render_model_command_context *)g_command_context;
	auto filename = arg_values[0];
	
	auto render_model = context->get_render_model();
	auto geometry_resource = c_cache_file_tag_resource<s_render_geometry_api_resource_definition>(render_model->geometry.resource_index);
	auto vertex_buffers = geometry_resource.get_data<s_render_geometry_api_vertex_buffer_reference>(geometry_resource->vertex_buffers.address);
	auto index_buffers = geometry_resource.get_data<s_render_geometry_api_index_buffer_reference>(geometry_resource->index_buffers.address);

	for (auto i = 0; i < geometry_resource->vertex_buffers.count; i++)
	{
		auto vertex_buffer = geometry_resource.get_data<s_render_geometry_api_vertex_buffer>(vertex_buffers[i].vertex_buffer.address);
		auto vertex_definition = vertex_definition_get((e_vertex_type)(vertex_buffer->format - 1));
		auto vertex_element = vertex_definition->elements;
		auto vertex_data = geometry_resource.get_data(vertex_buffer->data.address);

		for (auto j = 0; j < vertex_buffer->count; j++)
		{
			for (auto x = 0; x < vertex_definition->element_count; vertex_element_next(vertex_definition, &vertex_element, &vertex_data), x++)
			{
				auto current_element = (D3D11_INPUT_ELEMENT_DESC *)vertex_element;

				if (strcmp("POSITION", current_element->SemanticName) != 0)
					continue;

				switch (current_element->Format)
				{
				case DXGI_FORMAT_R32G32B32A32_FLOAT:
					printf("x: %f, y: %f, z: %f, w: %f\n",
						((float *)vertex_data)[0],
						((float *)vertex_data)[1],
						((float *)vertex_data)[2],
						((float *)vertex_data)[3]);
					break;

				case DXGI_FORMAT_R32G32B32_FLOAT:
					printf("x: %f, y: %f, z: %f\n",
						((float *)vertex_data)[0],
						((float *)vertex_data)[1],
						((float *)vertex_data)[2]);
					break;

				case DXGI_FORMAT_R32G32_FLOAT:
					printf("x: %f, y: %f\n",
						((float *)vertex_data)[0],
						((float *)vertex_data)[1]);
					break;

				case DXGI_FORMAT_R32_UINT:
					printf("x: %ul\n",
						((unsigned long *)vertex_data)[0]);
					break;

				case DXGI_FORMAT_R16G16B16A16_SNORM:
					printf("x: %f, y: %f, z: %f, w: %f\n",
						(float)((short *)vertex_data)[0] / (float)SHRT_MAX,
						(float)((short *)vertex_data)[1] / (float)SHRT_MAX,
						(float)((short *)vertex_data)[2] / (float)SHRT_MAX,
						(float)((short *)vertex_data)[3] / (float)SHRT_MAX);
					break;

				case DXGI_FORMAT_R8G8B8A8_UNORM:
					printf("x: %f, y: %f, z: %f, w: %f\n",
						(float)((byte *)vertex_data)[0] / (float)UCHAR_MAX,
						(float)((byte *)vertex_data)[1] / (float)UCHAR_MAX,
						(float)((byte *)vertex_data)[2] / (float)UCHAR_MAX,
						(float)((byte *)vertex_data)[3] / (float)UCHAR_MAX);
					break;

				default:
					printf("ERROR: vertex element format %i not supported!", current_element->Format);
					break;
				}
			}
		}
	}

	return true;
}
