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
	{
		"list_resource_tag_metrics",
		"list_resource_tag_metrics <filename>",
		"Lists all tags that reference a resource within the given cache file.",
		true,
		list_resource_tag_metrics_execute
	},
	{
		"save_cache_file",
		"save_cache_file",
		"Saves the changes to the current cache file.",
		true,
		save_cache_file_execute
	}
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
	auto header = file->get_header();
	auto tags_header = file->get_tags_header();

	tag group_tag = NONE;

	if (arg_count > 0)
	{
		for (auto i = 0; i < tags_header->groups.count; i++)
		{
			auto group = file->get_tag_group(i);

			if (csstrcmp(arg_values[0], file->get_string(group->name)) == 0)
			{
				group_tag = group->group_tags[0];
				break;
			}
		}

		if (group_tag == NONE && !field_parse(file, _field_tag, "group_tag", nullptr, &group_tag, 1, &arg_values[0]))
		{
			printf("ERROR: failed to parse group: %s\n", arg_values[0]);
			return true;
		}
	}

	auto filter = arg_count > 1 ? arg_values[1] : nullptr;

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
			printf("[Index: 0x%04lX, Identifier: 0x%04lX, Offset: 0x%llX] %s.%s\n",
				i,
				instance->identifier,
				cache_file_header->memory_buffer_offset + file->get_page_offset(instance->address),
				tag_name_length == 0 ? "<unnamed>" : tag_name,
				file->get_string(group->name));
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

	auto group_definition = tag_group_definition_get(group->group_tags[0]);
	if (!group_definition)
	{
		char tag_string[5];
		printf("ERROR: tag group definition not found for group tag '%s'!\n", tag_to_string(group->group_tags[0], tag_string));
		return true;
	}

	c_static_string<256> tag_group_string;
	c_static_string<256> tag_name_string;

	auto tag_name = file->get_tag_name(reference.index & k_uint16_max);
	auto separator = csstrrchr((char *)tag_name, '\\');
	
	if (separator)
		tag_name = separator + 1;

	sprintf(tag_name_string.get_buffer(), "(0x%04lX) %s.%s",
		reference.index & k_uint16_max,
		tag_name,
		file->get_string(group->name));

	auto tag_definition = file->get_tag_definition<void>(reference.index & k_uint16_max);

	switch (group->group_tags[0])
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
	s_cache_file_tag_group *group = nullptr;

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

	auto gestalt_definition_index = c_tag_iterator<k_cache_file_resource_gestalt_group_tag>(file).next();
	auto gestalt = file->get_tag_definition<s_cache_file_resource_gestalt>(gestalt_definition_index);

	auto layout_table_definition_index = c_tag_iterator<k_cache_file_resource_layout_table_group_tag>(file).next();
	auto layout_table = file->get_tag_definition<s_cache_file_resource_layout_table>(layout_table_definition_index);

	auto tag_resources = file->get_tags_section_pointer_from_page_offset<s_cache_file_tag_resource>(gestalt->tag_resources.address);

	for (auto i = 0; i < gestalt->tag_resources.count; i++)
	{
		auto tag_resource = &tag_resources[i];

		if (group && !group->is_in_group(tag_resource->parent_tag.group_tag))
			continue;

		s_cache_file_resource_segment *segment = nullptr;
		if (!tag_resource->segment_index.try_resolve(file, &layout_table->segments, &segment))
			continue;

		s_cache_file_resource_page *primary_page = nullptr;
		if (segment->primary_page.try_resolve(file, &layout_table->pages, &primary_page))
			if (primary_page->block_offset == NONE)
				primary_page = nullptr;

		s_cache_file_resource_page *secondary_page = nullptr;
		if (segment->secondary_page.try_resolve(file, &layout_table->pages, &secondary_page))
			if (secondary_page->block_offset == NONE)
				secondary_page = nullptr;

		auto page = secondary_page ? secondary_page : primary_page;
		if (!page || !page->shared_cache_file) continue;

		auto location = page->shared_cache_file.resolve(file, &layout_table->physical_locations);

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

bool list_resource_tag_metrics_execute(
	long arg_count,
	char const **arg_values)
{
	if (arg_count != 1)
		return false;

	auto file = g_command_context->get_file();

	s_tag_iterator iterator;
	tag_iterator_initialize(&iterator, k_cache_file_resource_gestalt_group_tag);
	tag_iterator_next(file, &iterator);

	if (iterator.index == NONE)
		return false;

	auto zone = file->get_tag_definition<s_cache_file_resource_gestalt>(iterator.index);

	if (!zone)
		return false;

	tag_iterator_initialize(&iterator, k_cache_file_resource_layout_table_group_tag);
	tag_iterator_next(file, &iterator);

	if (iterator.index == NONE)
		return false;

	auto play = file->get_tag_definition<s_cache_file_resource_layout_table>(iterator.index);

	if (!play)
		return false;

	for (auto i = 0; i < zone->tag_resources.count; i++)
	{
		auto tag_resource = zone->tag_resources.get_element(file, i);

		auto segment = tag_resource->segment_index.resolve(file, &play->segments);

		if (!segment)
			continue;

		auto primary_page = segment->primary_page.resolve(file, &play->pages);
		auto secondary_page = segment->secondary_page.resolve(file, &play->pages);

		auto should_print = false;

		if (primary_page)
		{
			if (primary_page->shared_cache_file != (short)NONE)
			{
				auto shared_cache_file = primary_page->shared_cache_file.resolve(file, &play->physical_locations);
				
				if (shared_cache_file && csstrstr(shared_cache_file->path, "campaign.map"))
					should_print = true;
			}
		}
		
		if (!should_print && secondary_page)
		{
			if (secondary_page->shared_cache_file != (short)NONE)
			{
				auto shared_cache_file = secondary_page->shared_cache_file.resolve(file, &play->physical_locations);

				if (shared_cache_file && csstrstr(shared_cache_file->path, "campaign.map"))
					should_print = true;
			}
		}

		if (should_print)
		{
			auto instance = file->get_tag_instance(i);

			if (!instance || !instance->address || instance->group_index == NONE)
				continue;

			auto tag_name = file->get_tag_name(i);
			auto tag_name_length = csstrlen(tag_name);

			auto group = file->get_tag_group(instance->group_index);
			auto cache_file_header = file->get_header();

			printf("[Index: 0x%04lX, Identifier: 0x%04lX, Offset: 0x%llX] %s.%s\n",
				i,
				instance->identifier,
				cache_file_header->memory_buffer_offset + file->get_page_offset(instance->address),
				tag_name_length == 0 ? "<unnamed>" : tag_name,
				file->get_string(group->name));
		}
	}

	return true;
}

bool save_cache_file_execute(
	long arg_count,
	char const **arg_values)
{
	if (arg_count != 0)
		return false;

	auto file = g_command_context->get_file();
	auto header = file->get_header();

	auto stream = fopen(file->get_filename(), "rb+");

	long tags_section_offset, tags_section_size;

	auto tags_section_buffer =
		file->get_section_buffer(_cache_file_section_tags, &tags_section_offset, &tags_section_size);

	fseek(stream, tags_section_offset, SEEK_SET);
	fwrite(tags_section_buffer, 1, tags_section_size, stream);

	auto pos = ftell(stream);

	fclose(stream);

	return true;
}
