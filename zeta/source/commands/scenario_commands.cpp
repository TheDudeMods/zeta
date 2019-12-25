
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

#define WIN32_LEAN_AND_MEAN
#include <d3d11.h>

#include <commands/scenario_commands.h>
#include <commands/render_model_commands.h>
#include <tag_files/tag_files.h>
#include <scenario/structure_lightmap_definitions.h>
#include <structures/structure_bsp_definitions.h>

extern s_tag_group scenario_group;

/* ---------- code */

c_scenario_command_context::c_scenario_command_context(
	char const *name,
	s_scenario *scenario,
	c_cache_file_reach *file,
	c_command_context *parent) :
	c_editing_command_context(
		name,
		scenario,
		&scenario_group,
		file,
		parent),
	m_scenario(scenario)
{
	m_command_set_count = NUMBEROF(k_scenario_command_sets);
	m_command_sets = k_scenario_command_sets;
}

s_scenario *c_scenario_command_context::get_scenario()
{
	return m_scenario;
}

bool extract_rain_render_geometry_execute(
	long arg_count,
	char const **arg_values)
{
	if (arg_count != 1)
		return false;

	auto filename = arg_values[0];

	FILE *obj_stream = nullptr;
	fopen_s(&obj_stream, filename, "wb+");

	auto context = dynamic_cast<c_scenario_command_context *>(g_command_context);
	auto file = context->get_file();

	if (!context)
	{
		puts("ERROR: invalid command context!");
		return true;
	}

	auto scenario = context->get_scenario();

	auto structure_design_reference = scenario->structure_designs.get_element(file, 0);

	auto structure_design = file->get_tag_definition<s_structure_design_definition>(
		structure_design_reference->structure_design.index);

	auto geometry_resource = c_cache_file_reach_tag_resource<s_render_geometry_api_resource_definition>(
		file, structure_design->render_geometry.resource_index);

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

bool extract_structure_render_geometry_execute(
	long arg_count,
	char const **arg_values)
{
	if (arg_count != 2)
		return false;

	auto structure_index = strtoul(arg_values[0], nullptr, 0);
	auto filename = arg_values[1];

	FILE *obj_stream = nullptr;
	fopen_s(&obj_stream, filename, "wb+");

	auto context = dynamic_cast<c_scenario_command_context *>(g_command_context);
	auto file = context->get_file();

	if (!context)
	{
		puts("ERROR: invalid command context!");
		return true;
	}

	auto scenario = context->get_scenario();

	auto lightmap = file->get_tag_definition<s_scenario_lightmap>(
		scenario->lightmap.index);

	auto structure_bsp_reference = scenario->structure_bsps.get_element(file, structure_index);
	
	auto structure_bsp = file->get_tag_definition<s_structure_bsp_definition>(
		structure_bsp_reference->structure_bsp.index);

	auto tag_resources = c_cache_file_reach_tag_resource<s_structure_bsp_tag_resources>(
		file, structure_bsp->tag_resources_index);

	auto cache_file_tag_resources = c_cache_file_reach_tag_resource<s_structure_bsp_cache_file_tag_resources>(
		file, structure_bsp->cache_file_tag_resources_index);

	auto instanced_geometry_definitions = tag_resources.get_data<s_structure_bsp_instanced_geometry_definition>(
		tag_resources->instanced_geometry_definitions.address);

	auto instanced_geometry_instances = cache_file_tag_resources.get_data<s_structure_bsp_resource_instanced_geometry_instance>(
		cache_file_tag_resources->instanced_geometry_instances.address);

	auto instance1 = &instanced_geometry_instances[1];
	auto instance2 = &instanced_geometry_instances[2];
	auto instance3 = &instanced_geometry_instances[3];

	auto structure_design_reference = scenario->structure_designs.get_element(file, 0);

	auto structure_design = file->get_tag_definition<s_structure_design_definition>(
		structure_design_reference->structure_design.index);

	auto lightmap_data_reference = lightmap->lightmap_data_references.get_element(file, structure_index);

	auto lightmap_data = file->get_tag_definition<s_scenario_lightmap_bsp_data>(
		lightmap_data_reference->lightmap_data.index);

	auto geometry_resource = c_cache_file_reach_tag_resource<s_render_geometry_api_resource_definition>(
		file, lightmap_data->render_geometry.resource_index);

	auto base_index = 1;

	for (auto cluster_index = 0;
		cluster_index < structure_bsp->clusters.count;
		cluster_index++)
	{
		auto cluster = structure_bsp->clusters.get_element(file, cluster_index);
		if (!cluster) continue;

		auto mesh = cluster->mesh.resolve(file, &lightmap_data->render_geometry.meshes);
		if (!mesh) continue;

		char mesh_name[256];
		csnzprintf(mesh_name, 256, "cluster%i", cluster_index);

		base_index += mesh_stream_to_obj_file(
			file,
			geometry_resource,
			base_index,
			nullptr,
			mesh_name,
			mesh,
			obj_stream);
	}

	for (auto instanced_geometry_instance_index = 0;
		instanced_geometry_instance_index < cache_file_tag_resources->instanced_geometry_instances.count;
		instanced_geometry_instance_index++)
	{
		auto instanced_geometry_instance = &instanced_geometry_instances[instanced_geometry_instance_index];
		auto instanced_geometry_definition = &instanced_geometry_definitions[instanced_geometry_instance->instance_definition.operator short()];

		auto mesh = instanced_geometry_definition->mesh.resolve(file, &lightmap_data->render_geometry.meshes);
		auto compression = instanced_geometry_definition->compression.resolve(file, &lightmap_data->render_geometry.compression_info);
		if (!mesh) continue;

		char mesh_name[256];
		csnzprintf(mesh_name, 256, "instance%i", instanced_geometry_instance_index);

		base_index += mesh_stream_to_obj_file(
			file,
			geometry_resource,
			base_index,
			compression,
			mesh_name,
			mesh,
			obj_stream,
			instanced_geometry_instance->matrix.position);
	}

	fclose(obj_stream);

	return true;
}
