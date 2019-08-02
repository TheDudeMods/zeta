
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

	auto filename = arg_values[0];

	auto context = (c_render_model_command_context *)g_command_context;
	auto render_model = context->get_render_model();

	auto geometry_resource = c_cache_file_tag_resource<s_render_geometry_api_resource_definition>(
		render_model->geometry.resource_index);
	
	auto vertex_buffers = geometry_resource.get_data<s_render_geometry_api_vertex_buffer_reference>(
		geometry_resource->vertex_buffers.address);

	auto index_buffers = geometry_resource.get_data<s_render_geometry_api_index_buffer_reference>(
		geometry_resource->index_buffers.address);

	auto compression_info = render_model->geometry.compression_info.count ?
		g_cache_file->get_page_data<s_compression_info>(render_model->geometry.compression_info.address) :
		nullptr;

	auto regions = g_cache_file->get_page_data<s_render_model_region>(render_model->regions.address);

	for (auto region_index = 0; region_index < render_model->regions.count; region_index++)
	{
		auto region = &regions[region_index];
		auto region_name = g_cache_file->get_string(region->name);

		auto permutations = g_cache_file->get_page_data<s_render_model_permutation>(region->permutations.address);

		for (auto permutation_index = 0; permutation_index < region->permutations.count; permutation_index++)
		{
			auto permutation = &permutations[permutation_index];
			auto permutation_name = g_cache_file->get_string(permutation->name);

			s_mesh *meshes = nullptr;
			permutation->first_mesh.try_resolve(&render_model->geometry.meshes, &meshes);

			for (auto mesh_index = 0; mesh_index < permutation->mesh_count; mesh_index++)
			{
				auto mesh = &meshes[mesh_index];
				auto vertex_definition = vertex_definition_get(mesh->vertex_type);

				if (!vertex_definition)
					continue;

				auto vertex_stream_index = 0;
				auto vertex_buffer_index = mesh->vertex_buffer_indices[vertex_stream_index];

				if (vertex_buffer_index == NONE)
					continue;

				auto vertex_buffer = geometry_resource.get_data<s_render_geometry_api_vertex_buffer>(
					vertex_buffers[vertex_buffer_index].vertex_buffer.address);

				for (auto vertex_index = 0;
					vertex_index < vertex_buffer->count;
					vertex_index++)
				{
					auto vertex_data = (void *)((char *)geometry_resource.get_data(vertex_buffer->data.address) + (vertex_index * vertex_buffer->vertex_size));
					auto vertex_element = vertex_definition->elements;

					for (auto vertex_element_index = 0;
						vertex_element_index < vertex_definition->element_count;
						vertex_element_index++)
					{
						auto current_element = (D3D11_INPUT_ELEMENT_DESC *)vertex_element;

						if (current_element->SemanticIndex != vertex_stream_index)
						{
							vertex_element_next(vertex_definition, &vertex_element, nullptr);
							continue;
						}

						if (strcmp("POSITION", current_element->SemanticName) == 0)
						{
							auto position = real_quaternion{ 0.0f, 0.0f, 0.0f, 0.0f };

							switch (current_element->Format)
							{
							case DXGI_FORMAT_R32G32B32A32_FLOAT:
								position.i = ((float *)vertex_data)[0];
								position.j = ((float *)vertex_data)[1];
								position.k = ((float *)vertex_data)[2];
								position.w = ((float *)vertex_data)[3];
								break;

							case DXGI_FORMAT_R32G32B32_FLOAT:
								position.i = ((float *)vertex_data)[0];
								position.j = ((float *)vertex_data)[1];
								position.k = ((float *)vertex_data)[2];
								break;

							case DXGI_FORMAT_R32G32_FLOAT:
								position.i = ((float *)vertex_data)[0];
								position.j = ((float *)vertex_data)[1];
								break;

							case DXGI_FORMAT_R32_UINT:
								position.i = (float)((unsigned long *)vertex_data)[0];
								break;

							case DXGI_FORMAT_R16G16B16A16_SNORM:
								position.i = (float)((short *)vertex_data)[0] / (float)SHRT_MAX;
								position.j = (float)((short *)vertex_data)[1] / (float)SHRT_MAX;
								position.k = (float)((short *)vertex_data)[2] / (float)SHRT_MAX;
								position.w = (float)((short *)vertex_data)[3] / (float)SHRT_MAX;
								break;

							case DXGI_FORMAT_R8G8B8A8_UNORM:
								position.i = (float)((byte *)vertex_data)[0] / (float)UCHAR_MAX;
								position.j = (float)((byte *)vertex_data)[1] / (float)UCHAR_MAX;
								position.k = (float)((byte *)vertex_data)[2] / (float)UCHAR_MAX;
								position.w = (float)((byte *)vertex_data)[3] / (float)UCHAR_MAX;
								break;

							default:
								printf("ERROR: vertex element format %i not supported!", current_element->Format);
								break;
							}

							if (compression_info)
							{
								position.i *= compression_info->position_upper.x - (compression_info->position_lower.x * 2);
								position.j *= compression_info->position_upper.y - (compression_info->position_lower.y * 2);
								position.k *= compression_info->position_upper.z - (compression_info->position_lower.z * 2);
							}

							printf("v %f %f %f\n", position.i, position.j, position.k);
						}

						if (strcmp("NORMAL", current_element->SemanticName) == 0)
						{
							auto normal = real_quaternion{ 0.0f, 0.0f, 0.0f, 0.0f };

							switch (current_element->Format)
							{
							case DXGI_FORMAT_R32G32B32A32_FLOAT:
								normal.i = ((float *)vertex_data)[0];
								normal.j = ((float *)vertex_data)[1];
								normal.k = ((float *)vertex_data)[2];
								normal.w = ((float *)vertex_data)[3];
								break;

							case DXGI_FORMAT_R32G32B32_FLOAT:
								normal.i = ((float *)vertex_data)[0];
								normal.j = ((float *)vertex_data)[1];
								normal.k = ((float *)vertex_data)[2];
								break;

							case DXGI_FORMAT_R32G32_FLOAT:
								normal.i = ((float *)vertex_data)[0];
								normal.j = ((float *)vertex_data)[1];
								break;

							case DXGI_FORMAT_R32_UINT:
								normal.i = (float)((unsigned long *)vertex_data)[0];
								break;

							case DXGI_FORMAT_R16G16B16A16_SNORM:
								normal.i = (float)((short *)vertex_data)[0] / (float)SHRT_MAX;
								normal.j = (float)((short *)vertex_data)[1] / (float)SHRT_MAX;
								normal.k = (float)((short *)vertex_data)[2] / (float)SHRT_MAX;
								normal.w = (float)((short *)vertex_data)[3] / (float)SHRT_MAX;
								break;

							case DXGI_FORMAT_R8G8B8A8_UNORM:
								normal.i = (float)((byte *)vertex_data)[0] / (float)UCHAR_MAX;
								normal.j = (float)((byte *)vertex_data)[1] / (float)UCHAR_MAX;
								normal.k = (float)((byte *)vertex_data)[2] / (float)UCHAR_MAX;
								normal.w = (float)((byte *)vertex_data)[3] / (float)UCHAR_MAX;
								break;

							default:
								printf("ERROR: vertex element format %i not supported!", current_element->Format);
								break;
							}

							if (compression_info)
							{
								normal.i *= compression_info->position_upper.x - (compression_info->position_lower.x * 2);
								normal.j *= compression_info->position_upper.y - (compression_info->position_lower.y * 2);
								normal.k *= compression_info->position_upper.z - (compression_info->position_lower.z * 2);
							}

							printf("vn %f %f %f\n", normal.i, normal.j, normal.k);
						}

						if (strcmp("TEXCOORD", current_element->SemanticName) == 0)
						{
							auto texcoord = real_quaternion{ 0.0f, 0.0f, 0.0f, 0.0f };

							switch (current_element->Format)
							{
							case DXGI_FORMAT_R32G32B32A32_FLOAT:
								texcoord.i = ((float *)vertex_data)[0];
								texcoord.j = ((float *)vertex_data)[1];
								texcoord.k = ((float *)vertex_data)[2];
								texcoord.w = ((float *)vertex_data)[3];
								break;

							case DXGI_FORMAT_R32G32B32_FLOAT:
								texcoord.i = ((float *)vertex_data)[0];
								texcoord.j = ((float *)vertex_data)[1];
								texcoord.k = ((float *)vertex_data)[2];
								break;

							case DXGI_FORMAT_R32G32_FLOAT:
								texcoord.i = ((float *)vertex_data)[0];
								texcoord.j = ((float *)vertex_data)[1];
								break;

							case DXGI_FORMAT_R32_UINT:
								texcoord.i = (float)((unsigned long *)vertex_data)[0];
								break;

							case DXGI_FORMAT_R16G16B16A16_SNORM:
								texcoord.i = (float)((short *)vertex_data)[0] / (float)SHRT_MAX;
								texcoord.j = (float)((short *)vertex_data)[1] / (float)SHRT_MAX;
								texcoord.k = (float)((short *)vertex_data)[2] / (float)SHRT_MAX;
								texcoord.w = (float)((short *)vertex_data)[3] / (float)SHRT_MAX;
								break;

							case DXGI_FORMAT_R8G8B8A8_UNORM:
								texcoord.i = (float)((byte *)vertex_data)[0] / (float)UCHAR_MAX;
								texcoord.j = (float)((byte *)vertex_data)[1] / (float)UCHAR_MAX;
								texcoord.k = (float)((byte *)vertex_data)[2] / (float)UCHAR_MAX;
								texcoord.w = (float)((byte *)vertex_data)[3] / (float)UCHAR_MAX;
								break;

							default:
								printf("ERROR: vertex element format %i not supported!", current_element->Format);
								break;
							}

							if (compression_info)
							{
								texcoord.i *= compression_info->position_upper.x - (compression_info->position_lower.x * 2);
								texcoord.j *= compression_info->position_upper.y - (compression_info->position_lower.y * 2);
								texcoord.k *= compression_info->position_upper.z - (compression_info->position_lower.z * 2);
							}

							printf("vt %f %f\n", texcoord.i, texcoord.j);
						}

						vertex_element_next(vertex_definition, &vertex_element, &vertex_data);
					}
				}

				auto index_stream_index = 0;
				auto index_buffer_index = mesh->index_buffer_indices[index_stream_index];

				if (index_buffer_index == NONE)
					continue;

				auto index_buffer = geometry_resource.get_data<s_render_geometry_api_index_buffer>(
					index_buffers[index_buffer_index].index_buffer.address);

				printf("g %s_%s_%i\n", region_name, permutation_name, mesh_index);

				for (auto index_index = 0;
					index_index < (index_buffer->data.size / 2);
					index_index++)
				{
					auto index_data = (word *)((char *)geometry_resource.get_data(index_buffer->data.address) + (index_index * 2));
					printf("f %i/%i/%i %i/%i/%i %i/%i/%i\n",
						index_data[0] + 1, index_data[0] + 1, index_data[0] + 1,
						index_data[1] + 1, index_data[1] + 1, index_data[1] + 1,
						index_data[2] + 1, index_data[2] + 1, index_data[2] + 1);
				}
			}
		}
	}

	return true;
}
