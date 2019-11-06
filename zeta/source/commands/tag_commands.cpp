#include <bitmaps/bitmaps.h>
#include <tag_files/tag_files.h>
#include <cache/cache_file_tag_resources.h>
#include <commands/bitmap_commands.h>
#include <commands/editing_commands.h>
#include <commands/rasterizer_shader_commands.h>
#include <commands/render_model_commands.h>
#include <commands/tag_commands.h>

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>

/* ---------- constants */

enum
{
	k_number_of_tag_command_sets = 1
};

/* ---------- globals */

s_command g_tag_commands[k_number_of_tag_commands] =
{
	{
		"list_tags",
		"list_tags [group_tag] [filter]",
		"Lists all tags instances of the specified group.",
		true,
		list_tags_execute
	},
	{
		"edit_tag",
		"edit_tag <tag_handle>",
		"Opens the specified tag instance for editing.",
		false,
		edit_tag_execute
	},
	{
		"file_offset",
		"file_offset <page_address>",
		"Lists the file offset for a page address.",
		true,
		file_offset_execute
	},
	{
		"list_local_resource_tags",
		"list_local_resource_tags <group_tag>",
		"Lists all resource-owning tags instances of the specified group within the current cache file.",
		true,
		list_local_resource_tags_execute
	},
};

static s_command_set g_tag_command_sets[k_number_of_tag_command_sets] =
{
	{ k_number_of_tag_commands, g_tag_commands }
};

/* ---------- code */

c_command_context *create_tag_command_context(
	c_cache_file_reach *file,
	c_command_context *parent)
{
	 return new c_command_context("tags", k_number_of_tag_command_sets, g_tag_command_sets, file, parent);
}

bool list_tags_execute(
	long arg_count,
	char const **arg_values)
{
	if (arg_count > 2)
		return false;

	auto file = g_command_context->get_file();

	tag group_tag = NONE;
	
	if (arg_count > 0 && !field_parse(file, _field_tag, "group_tag", nullptr, &group_tag, 1, &arg_values[0]))
	{
		printf("ERROR: failed to parse group: %s\n", arg_values[0]);
		return true;
	}

	auto filter = arg_count > 1 ? arg_values[1] : nullptr;

	auto tags_header = file->get_tags_header();

	for (auto i = 0; i < tags_header->instances.count; i++)
	{
		auto instance = file->get_tag_instance(i);

		if (!instance || !instance->address || instance->group_index == NONE)
			continue;

		auto tag_name = file->get_tag_name(i);
		auto tag_name_length = csstrlen(tag_name);

		if (filter && !csstrstr((char *)tag_name, filter))
			continue;

		auto group = file->get_tag_group(instance->group_index);
		auto cache_file_header = file->get_header();

		if (group_tag == NONE || group->is_in_group(group_tag))
		{
			char group_string[5];

			auto tags_section_offset =
				cache_file_header->interop.offset_masks[_cache_file_section_tags] +
				cache_file_header->interop.sections[_cache_file_section_tags].address;

			printf("[Index: 0x%04lX, Identifier: 0x%04lX, Offset: 0x%llX] %s.%s\n",
				i,
				instance->identifier,
				tags_section_offset + file->get_page_offset(instance->address),
				tag_name_length == 0 ? "<unnamed>" : tag_name,
				tag_to_string(group->tags[0], group_string));
		}
	}

	return true;
}

bool edit_tag_execute(
	long arg_count,
	char const **arg_values)
{
	if (arg_count != 1)
		return false;

	auto file = g_command_context->get_file();

	s_tag_reference reference;
	field_parse(file, _field_tag_reference, "reference", nullptr, &reference, arg_count, arg_values);

	auto instance = file->get_tag_instance(reference.index & k_uint16_max);
	if (!instance || !instance->address || instance->group_index == NONE)
	{
		printf("ERROR: tag instance 0x%04lX is null!", reference.index & k_uint16_max);
		return true;
	}

	auto group = file->get_tag_group(instance->group_index);
	if (!group)
	{
		printf("ERROR: failed to get tag group of tag instance 0x%04lX!", reference.index & k_uint16_max);
		return true;
	}

	auto group_definition = tag_group_definition_get(group->tags[0]);
	if (!group_definition)
	{
		char tag_string[5];
		printf("ERROR: tag group definition not found for group tag '%s'!\n", tag_to_string(group->tags[0], tag_string));
		return true;
	}

	c_static_string<256> tag_name_string;

	auto tag_name = file->get_tag_name(reference.index & k_uint16_max);
	auto group_name = file->get_string(group->name);
	
	auto separator = csstrrchr((char *)tag_name, '\\');
	
	if (separator)
		tag_name = separator + 1;

	sprintf(tag_name_string.get_buffer(), "(0x%04lX) %s.%s", reference.index & k_uint16_max, tag_name, group_name);

	auto tag_definition = file->get_tag_definition<void>(reference.index & k_uint16_max);

	switch (group->tags[0])
	{
	case k_bitmap_group_tag:
		g_command_context = new c_bitmap_command_context(
			tag_name_string.get_buffer(),
			(s_bitmap_definition *)tag_definition,
			file,
			g_command_context);
		break;

	case k_pixel_shader_group_tag:
		g_command_context = new c_pixel_shader_command_context(
			tag_name_string.get_buffer(),
			(c_rasterizer_pixel_shader *)tag_definition,
			file,
			g_command_context);
		break;

	case k_render_model_group_tag:
		g_command_context = new c_render_model_command_context(
			tag_name_string.get_buffer(),
			(s_render_model_definition *)tag_definition,
			file,
			g_command_context);
		break;

	case k_vertex_shader_group_tag:
		g_command_context = new c_vertex_shader_command_context(
			tag_name_string.get_buffer(),
			(c_rasterizer_vertex_shader *)tag_definition,
			file,
			g_command_context);
		break;

	default:
		g_command_context = new c_editing_command_context(
			tag_name_string.get_buffer(),
			tag_definition,
			group_definition,
			file,
			g_command_context);
		break;
	}

	return true;
}

bool file_offset_execute(
	long arg_count,
	char const **arg_values)
{
	if (arg_count != 1)
		return false;

	auto file = g_command_context->get_file();

	auto value = strtoul(arg_values[0], nullptr, 0);
	auto cache_file_header = file->get_header();

	printf("File Offset: 0x%llX\n", cache_file_header->memory_buffer_offset + file->get_page_offset(value));

	return true;
}

bool list_local_resource_tags_execute(
	long arg_count,
	char const **arg_values)
{
	if (arg_count > 1)
		return false;

	auto file = g_command_context->get_file();

	tag group_tag = NONE;
	s_tag_group *group = nullptr;

	if (arg_count != 0)
	{
		if (!field_parse(file, _field_tag, "group_tag", nullptr, &group_tag, 1, &arg_values[0]))
		{
			printf("ERROR: failed to parse group: %s\n", arg_values[0]);
			return true;
		}

		group = file->get_tag_group(file->find_tag_group(group_tag));
	}

	auto cache_file_header = file->get_header();
	auto zone_index = c_tag_iterator<k_cache_file_resource_gestalt_group_tag>(file).next();
	auto zone = file->get_tag_definition<s_cache_file_resource_gestalt>(zone_index);

	auto tag_resources = file->get_page_data<s_cache_file_tag_resource>(zone->tag_resources.address);

	for (auto i = 0; i < zone->tag_resources.count; i++)
	{
		auto tag_resource = &tag_resources[i];

		if (group && !group->is_in_group(tag_resource->parent_tag.group_tag))
			continue;

		s_cache_file_resource_segment *segment = nullptr;
		if (!tag_resource->segment_index.try_resolve(file, &zone->layout_table.segments, &segment))
			continue;

		s_cache_file_resource_page *primary_page = nullptr;
		if (segment->primary_page.try_resolve(file, &zone->layout_table.pages, &primary_page))
			if (primary_page->block_offset == NONE)
				primary_page = nullptr;

		s_cache_file_resource_page *secondary_page = nullptr;
		if (segment->secondary_page.try_resolve(file, &zone->layout_table.pages, &secondary_page))
			if (secondary_page->block_offset == NONE)
				secondary_page = nullptr;

		auto page = secondary_page ? secondary_page : primary_page;
		if (!page || !page->shared_cache_file) continue;

		auto location = page->shared_cache_file.resolve(file, &zone->layout_table.physical_locations);

		auto instance = file->get_tag_instance(tag_resource->parent_tag.index);

		auto tag_name = file->get_tag_name(tag_resource->parent_tag.index);
		auto tag_name_length = csstrlen(tag_name);
		auto tag_group = file->get_tag_group(instance->group_index);

		printf("[Index: 0x%04lX, Identifier: 0x%04lX, Offset: 0x%llX] %s.%s\n",
			i,
			instance->identifier,
			cache_file_header->memory_buffer_offset + file->get_page_offset(instance->address),
			tag_name_length == 0 ? "<unnamed>" : tag_name,
			file->get_string(tag_group->name));
	}

	return true;
}
