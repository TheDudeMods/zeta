
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

		printf("region \"%s\":\n", region_name);

		auto permutations = g_cache_file->get_page_data<s_render_model_permutation>(region->permutations.address);

		for (auto permutation_index = 0; permutation_index < region->permutations.count; permutation_index++)
		{
			auto permutation = &permutations[permutation_index];
			auto permutation_name = g_cache_file->get_string(permutation->name);

			printf("\tpermutation \"%s\"\n", permutation_name);

			s_mesh *meshes = nullptr;
			permutation->first_mesh.try_resolve(&render_model->geometry.meshes, &meshes);

			for (auto mesh_index = 0; mesh_index < permutation->mesh_count; mesh_index++)
			{
				auto mesh = &meshes[mesh_index];
				auto vertex_definition = vertex_definition_get(mesh->vertex_type);

				if (!vertex_definition)
					continue;

				printf("\t\tmesh %i:\n", mesh_index);

				for (auto vertex_stream_index = 0;
					vertex_stream_index < k_maximum_number_of_vertex_buffers_per_mesh;
					vertex_stream_index++)
				{
					auto vertex_buffer_index = mesh->vertex_buffer_indices[vertex_stream_index];

					if (vertex_buffer_index == NONE)
						continue;

					printf("\t\t\tvertex stream %i\n", vertex_stream_index);

					auto vertex_buffer = geometry_resource.get_data<s_render_geometry_api_vertex_buffer>(
							vertex_buffers[vertex_buffer_index].vertex_buffer.address);

					for (auto vertex_index = 0;
						vertex_index < vertex_buffer->count;
						vertex_index++)
					{
						auto vertex_data = (void*)((char *)geometry_resource.get_data(vertex_buffer->data.address) + (vertex_index * vertex_buffer->vertex_size));
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

							auto position = real_quaternion{ 0.0f, 0.0f, 0.0f, 0.0f };
							auto texcoord = real_vector2d{ 0.0f, 0.0f };

							if (strcmp("POSITION", current_element->SemanticName) == 0)
							{
								printf("%s", "\t\t\t\t");

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

								switch (current_element->Format)
								{
								case DXGI_FORMAT_R32G32B32A32_FLOAT:
								case DXGI_FORMAT_R16G16B16A16_SNORM:
								case DXGI_FORMAT_R8G8B8A8_UNORM:
									printf("x: %f, y: %f, z: %f, w: %f\n", position.i, position.j, position.k, position.w);
									break;

								case DXGI_FORMAT_R32G32B32_FLOAT:
									printf("x: %f, y: %f, z: %f\n", position.i, position.j, position.k);
									break;

								case DXGI_FORMAT_R32G32_FLOAT:
									printf("x: %f, y: %f\n", position.i, position.j);
									break;

								case DXGI_FORMAT_R32_UINT:
									printf("x: %f\n", position.i);
									break;

								default:
									printf("ERROR: vertex element format %i not supported!", current_element->Format);
									break;
								}
							}

							vertex_element_next(vertex_definition, &vertex_element, &vertex_data);
						}
					}
				}
			}
		}
	}

	return true;
}
