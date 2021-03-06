
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

#define WIN32_LEAN_AND_MEAN
#include <d3d11.h>

#include <commands/render_model_commands.h>

extern s_tag_group render_model_group;

/* ---------- code */

c_render_model_command_context::c_render_model_command_context(
	char const *name,
	s_render_model_definition *render_model,
	c_cache_file_reach *file,
	c_command_context *parent) :
	c_editing_command_context(
		name,
		render_model,
		&render_model_group,
		file,
		parent),
	m_render_model(render_model)
{
	m_command_set_count = NUMBEROF(k_render_model_command_sets);
	m_command_sets = k_render_model_command_sets;
}

s_render_model_definition *c_render_model_command_context::get_render_model()
{
	return m_render_model;
}

long mesh_stream_to_obj_file(
	c_cache_file_reach *file,
	c_cache_file_reach_tag_resource<s_render_geometry_api_resource_definition> &geometry_resource,
	long base_index,
	s_compression_info *compression_info,
	char const *mesh_name,
	s_mesh *mesh,
	FILE *obj_stream,
	real_point3d offset)
{
	auto parts = &mesh->parts;
	auto subparts = &mesh->subparts;

	auto vertex_buffers = geometry_resource.get_data<s_render_geometry_api_vertex_buffer_reference>(
		geometry_resource->vertex_buffers.address);

	auto index_buffers = geometry_resource.get_data<s_render_geometry_api_index_buffer_reference>(
		geometry_resource->index_buffers.address);

	long vertex_buffer_index = NONE;

	for (auto stream_index = 0; stream_index < 5; stream_index++)
	{
		auto index = mesh->vertex_buffer_indices[stream_index];

		if (index != NONE)
		{
			vertex_buffer_index = index;
			break;
		}
	}

	if (vertex_buffer_index == NONE)
		return 0;

	long index_buffer_index = NONE;

	for (auto stream_index = 0; stream_index < 2; stream_index++)
	{
		auto index = mesh->index_buffer_indices[stream_index];

		if (index != NONE)
		{
			index_buffer_index = index;
			break;
		}
	}

	if (index_buffer_index == NONE)
		return 0;

	auto vertex_buffer = geometry_resource.get_data<s_render_geometry_api_vertex_buffer>(
		vertex_buffers[vertex_buffer_index].vertex_buffer.address);

	auto vertex_data = geometry_resource.get_data<char>(
		vertex_buffer->data.address);

	auto index_buffer = geometry_resource.get_data<s_render_geometry_api_index_buffer>(
		index_buffers[index_buffer_index].index_buffer.address);

	auto indices = geometry_resource.get_data<short>(
		index_buffer->data.address);

	if (vertex_data == nullptr)
		return 0;

	if (vertex_buffer->format != _vertex_buffer_type_world &&
		vertex_buffer->format != _vertex_buffer_type_rigid &&
		vertex_buffer->format != _vertex_buffer_type_skinned)
		return 0;

	if (index_buffer->format != _index_buffer_type_triangle_list &&
		index_buffer->format != _index_buffer_type_triangle_strip)
		return 0;

	for (auto i = 0; i < vertex_buffer->count; i++)
	{
		auto v = (float *)&vertex_data[(i * vertex_buffer->vertex_size) + 0];
		auto x = v[0], y = v[1], z = v[2];

		if (compression_info && compression_info->flags.test(_compressed_position_bit))
		{
			auto x_length = (compression_info->position_x.upper - compression_info->position_x.lower);
			if (x_length != 0.0f)
				x = x * x_length + compression_info->position_x.lower;

			auto y_length = (compression_info->position_y.upper - compression_info->position_y.lower);
			if (y_length != 0.0f)
				y = y * y_length + compression_info->position_y.lower;

			auto z_length = (compression_info->position_z.upper - compression_info->position_z.lower);
			if (z_length != 0.0f)
				z = z * z_length + compression_info->position_z.lower;
		}

		fprintf(obj_stream, "v %.6f %.6f %.6f\n", x + offset.x, z + offset.z, y + offset.y);
	}

	for (auto i = 0; i < vertex_buffer->count; i++)
	{
		auto vn = (short *)&vertex_data[(i * vertex_buffer->vertex_size) + 20];
		auto x = (float)vn[0] / (float)SHRT_MAX;
		auto y = (float)vn[1] / (float)SHRT_MAX;
		auto z = (float)vn[2] / (float)SHRT_MAX;

		fprintf(obj_stream, "vn %.6f %.6f %.6f\n", x, z, y);
	}

	for (auto i = 0; i < vertex_buffer->count; i++)
	{
		auto vt = (ushort *)&vertex_data[(i * vertex_buffer->vertex_size) + 16];
		auto u = (float)vt[0] / (float)USHRT_MAX;
		auto v = (float)vt[1] / (float)USHRT_MAX;

		if (compression_info && compression_info->flags.test(_compressed_texcoord_bit))
		{
			auto u_length = (compression_info->texcoord_u.upper - compression_info->texcoord_u.lower);
			if (u_length != 0)
				u = u * u_length + compression_info->texcoord_u.lower;

			auto v_length = (compression_info->texcoord_v.upper - compression_info->texcoord_v.lower);
			if (v_length != 0)
				v = 1.0f - (v * v_length + compression_info->texcoord_v.lower);
		}

		fprintf(obj_stream, "vt %.6f %.6f\n", u, v);
	}

	for (auto part_index = 0; part_index < mesh->parts.count; part_index++)
	{
		s_part *part = nullptr;
		if (!parts->try_get_element(file, part_index, &part))
			continue;

		auto part_indices = &indices[part->index_start];

		fprintf(obj_stream, "g %s_part%i\n", mesh_name, part_index);

		switch (index_buffer->format.operator e_index_buffer_type())
		{
		case _index_buffer_type_triangle_list:
			for (auto i = 0; i < part->index_count; i += 3)
			{
				auto a = part_indices[i + 0] + base_index;
				auto b = part_indices[i + 1] + base_index;
				auto c = part_indices[i + 2] + base_index;

				if (a != b && a != c && b != c)
					fprintf(obj_stream, "f %i/%i/%i %i/%i/%i %i/%i/%i\n", a, a, a, b, b, b, c, c, c);
			}
			break;

		case _index_buffer_type_triangle_strip:
		{
			auto triangle_count = part->index_count - 2;

			auto f_indices = new ushort[(ulonglong)triangle_count * 3];
			short f_prev[2] = { part_indices[0], part_indices[1] };

			part_indices += 2;

			for (auto i = 0; i < triangle_count; i++)
			{
				auto index = part_indices[i];

				if (i % 2 == 0)
				{
					f_indices[(i * 3) + 0] = f_prev[0];
					f_indices[(i * 3) + 1] = f_prev[1];
				}
				else
				{
					f_indices[(i * 3) + 0] = f_prev[1];
					f_indices[(i * 3) + 1] = f_prev[0];
				}

				f_indices[(i * 3) + 2] = index;
				f_prev[0] = f_prev[1];
				f_prev[1] = index;
			}

			for (auto i = 0; i < (triangle_count * 3); i += 3)
			{
				auto a = f_indices[i + 0] + base_index;
				auto b = f_indices[i + 1] + base_index;
				auto c = f_indices[i + 2] + base_index;

				if (a != b && a != c && b != c)
					fprintf(obj_stream, "f %i/%i/%i %i/%i/%i %i/%i/%i\n", a, a, a, b, b, b, c, c, c);
			}

			delete[] f_indices;
			break;
		}

		default:
			puts("ERROR: unsupported index buffer type!");
			break;
		}
	}

	return vertex_buffer->count;
}

bool extract_render_model_execute(
	long arg_count,
	char const **arg_values)
{
	if (arg_count != 1)
		return false;

	auto filename = arg_values[0];

	FILE *obj_stream = nullptr;
	fopen_s(&obj_stream, filename, "wb+");

	auto context = dynamic_cast<c_render_model_command_context *>(g_command_context);
	auto file = context->get_file();

	if (!context)
	{
		puts("ERROR: invalid command context!");
		return true;
	}

	auto render_model = context->get_render_model();
	auto render_model_name = file->get_string(render_model->name);

	auto geometry_resource = c_cache_file_reach_tag_resource<s_render_geometry_api_resource_definition>(
		file, render_model->geometry.resource_index);
	
	auto compression_info = render_model->geometry.compression_info.count ?
		file->get_tags_section_pointer_from_page_offset<s_compression_info>(
			render_model->geometry.compression_info.address) :
		nullptr;

	auto regions = file->get_tags_section_pointer_from_page_offset<s_render_model_region>(
		render_model->regions.address);

	auto base_index = 1;

	for (auto region_index = 0; region_index < render_model->regions.count; region_index++)
	{
		auto region = &regions[region_index];
		
		char region_name_buf[256];
		auto region_name = csnzprintf(region_name_buf, 256, "%s", file->get_string(region->name));

		auto permutations = file->get_tags_section_pointer_from_page_offset<s_render_model_permutation>(
			region->permutations.address);

		for (auto permutation_index = 0; permutation_index < region->permutations.count; permutation_index++)
		{
			auto permutation = &permutations[permutation_index];

			char permutation_name_buf[256];
			auto permutation_name = csnzprintf(permutation_name_buf, 256, "%s", file->get_string(permutation->name));

			s_mesh *meshes = nullptr;
			permutation->first_mesh.try_resolve(file, &render_model->geometry.meshes, &meshes);

			for (auto mesh_index = 0; mesh_index < permutation->mesh_count; mesh_index++)
			{
				char mesh_name[256];
				csnzprintf(mesh_name, 256, "%s_%s_mesh%i", region_name, permutation_name, mesh_index);

				base_index += mesh_stream_to_obj_file(
					file,
					geometry_resource,
					base_index,
					compression_info,
					mesh_name,
					&meshes[mesh_index],
					obj_stream);
			}
		}
	}

	fclose(obj_stream);

	return true;
}
