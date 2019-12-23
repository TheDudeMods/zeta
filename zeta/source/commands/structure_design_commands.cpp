
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

#define WIN32_LEAN_AND_MEAN
#include <d3d11.h>

#include <commands/structure_design_commands.h>
#include <commands/render_model_commands.h>

extern s_tag_group structure_design_group;

/* ---------- code */

c_structure_design_command_context::c_structure_design_command_context(
	char const *name,
	s_structure_design_definition *structure_design,
	c_cache_file_reach *file,
	c_command_context *parent) :
	c_editing_command_context(
		name,
		structure_design,
		&structure_design_group,
		file,
		parent),
	m_structure_design(structure_design)
{
	m_command_set_count = NUMBEROF(k_structure_design_command_sets);
	m_command_sets = k_structure_design_command_sets;
}

s_structure_design_definition *c_structure_design_command_context::get_structure_design()
{
	return m_structure_design;
}

bool extract_rain_geometry_execute(
	long arg_count,
	char const **arg_values)
{
	if (arg_count != 1)
		return false;

	auto filename = arg_values[0];

	FILE *obj_stream = nullptr;
	fopen_s(&obj_stream, filename, "wb+");

	auto context = dynamic_cast<c_structure_design_command_context *>(g_command_context);
	auto file = context->get_file();

	if (!context)
	{
		puts("ERROR: invalid command context!");
		return true;
	}

	auto structure_design = context->get_structure_design();

	auto geometry_resource = c_cache_file_reach_tag_resource<s_render_geometry_api_resource_definition>(
		file, structure_design->render_geometry.resource_index);

	auto vertex_buffers = geometry_resource.get_data<s_render_geometry_api_vertex_buffer_reference>(
		geometry_resource->vertex_buffers.address);

	auto index_buffers = geometry_resource.get_data<s_render_geometry_api_index_buffer_reference>(
		geometry_resource->index_buffers.address);

	auto compression_info = structure_design->render_geometry.compression_info.count ?
		file->get_tags_section_pointer_from_page_offset<s_compression_info>(
			structure_design->render_geometry.compression_info.address) :
		nullptr;

	auto base_index = 1;

	for (auto instance_index = 0;
		instance_index < structure_design->instanced_geometry_instances.count;
		instance_index++)
	{
		auto instance = structure_design->instanced_geometry_instances.get_element(file, instance_index);
		if (!instance) continue;

		auto mesh = instance->mesh.resolve(file, &structure_design->render_geometry.meshes);

		char mesh_name[256];
		csnzprintf(mesh_name, 256, "%s", file->get_string(instance->name));

		base_index += mesh_stream_to_obj_file(
			file,
			geometry_resource,
			vertex_buffers,
			index_buffers,
			base_index,
			compression_info,
			mesh_name,
			mesh,
			obj_stream,
			instance->world_bounding_sphere_center);
	}

	fclose(obj_stream);

	return true;
}
