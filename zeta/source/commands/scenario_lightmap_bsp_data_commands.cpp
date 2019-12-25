
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

#define WIN32_LEAN_AND_MEAN
#include <d3d11.h>

#include <commands/scenario_lightmap_bsp_data_commands.h>
#include <commands/render_model_commands.h>
#include <tag_files/tag_files.h>
#include <structures/structure_bsp_definitions.h>

extern s_tag_group scenario_lightmap_bsp_data_group;

/* ---------- code */

c_scenario_lightmap_bsp_data_command_context::c_scenario_lightmap_bsp_data_command_context(
	char const *name,
	s_scenario_lightmap_bsp_data *scenario_lightmap_bsp_data,
	c_cache_file_reach *file,
	c_command_context *parent) :
	c_editing_command_context(
		name,
		scenario_lightmap_bsp_data,
		&scenario_lightmap_bsp_data_group,
		file,
		parent),
	m_scenario_lightmap_bsp_data(scenario_lightmap_bsp_data)
{
	m_command_set_count = NUMBEROF(k_scenario_lightmap_bsp_data_command_sets);
	m_command_sets = k_scenario_lightmap_bsp_data_command_sets;
}

s_scenario_lightmap_bsp_data *c_scenario_lightmap_bsp_data_command_context::get_scenario_lightmap_bsp_data()
{
	return m_scenario_lightmap_bsp_data;
}

bool extract_lightmap_render_geometry_execute(
	long arg_count,
	char const **arg_values)
{
	if (arg_count != 1)
		return false;

	auto filename = arg_values[0];

	FILE *obj_stream = nullptr;
	fopen_s(&obj_stream, filename, "wb+");

	auto context = dynamic_cast<c_scenario_lightmap_bsp_data_command_context *>(g_command_context);
	auto file = context->get_file();

	if (!context)
	{
		puts("ERROR: invalid command context!");
		return true;
	}

	// TODO: hmmm
	auto structure_bsp = file->get_tag_definition<s_structure_bsp_definition>(
		c_tag_iterator<k_structure_bsp_group_tag>(file).next());

	auto scenario_lightmap_bsp_data = context->get_scenario_lightmap_bsp_data();

	auto geometry_resource = c_cache_file_reach_tag_resource<s_render_geometry_api_resource_definition>(
		file, scenario_lightmap_bsp_data->render_geometry.resource_index);

	auto compression_info = scenario_lightmap_bsp_data->render_geometry.compression_info.count ?
		file->get_tags_section_pointer_from_page_offset<s_compression_info>(
			scenario_lightmap_bsp_data->render_geometry.compression_info.address) :
		nullptr;

	auto base_index = 1;

	for (auto cluster_index = 0;
		cluster_index < structure_bsp->clusters.count;
		cluster_index++)
	{
		auto cluster = structure_bsp->clusters.get_element(file, cluster_index);
		if (!cluster) continue;

		auto mesh = cluster->mesh.resolve(file, &scenario_lightmap_bsp_data->render_geometry.meshes);
		if (!mesh) continue;

		char mesh_name[256];
		csnzprintf(mesh_name, 256, "cluster%i", cluster_index);

		base_index += mesh_stream_to_obj_file(
			file,
			geometry_resource,
			base_index,
			compression_info,
			mesh_name,
			mesh,
			obj_stream);
	}

	for (auto instanced_geometry_group_index = 0;
		instanced_geometry_group_index < structure_bsp->instanced_geometry_groups.count;
		instanced_geometry_group_index++)
	{
		// TODO
	}

	fclose(obj_stream);

	return true;
}
