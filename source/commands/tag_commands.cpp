#include <bitmaps/bitmaps.h>
#include <commands/bitmap_commands.h>
#include <commands/editing_commands.h>
#include <commands/render_model_commands.h>
#include <commands/tag_commands.h>

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
		"list_tags <group_tag>",
		"Lists all tags instances of the specified group.",
		true,
		list_tags_execute
	},
	{
		"edit_tag",
		"edit_tag <tag_index> [filter]",
		"Opens the specified tag instance for editing.",
		false,
		edit_tag_execute
	}
};

static s_command_set g_tag_command_sets[k_number_of_tag_command_sets] =
{
	{ k_number_of_tag_commands, g_tag_commands }
};

/* ---------- code */

c_command_context *create_tag_command_context(
	c_command_context *parent)
{
	 return new c_command_context("tags", k_number_of_tag_command_sets, g_tag_command_sets, parent);
}

bool list_tags_execute(
	long arg_count,
	char const **arg_values)
{
	if (arg_count < 1 || arg_count > 2)
		return false;

	tag group_tag = NONE;
	
	if (!field_parse(_field_tag, "group_tag", nullptr, &group_tag, 1, &arg_values[0]))
	{
		printf("ERROR: failed to parse group: %s\n", arg_values[0]);
		return true;
	}

	auto filter = arg_count > 1 ? arg_values[1] : nullptr;

	auto tags_header = g_cache_file->get_tags_header();

	for (auto i = 0; i < tags_header->tag_count; i++)
	{
		auto instance = g_cache_file->get_tag_instance(i);

		if (!instance || !instance->address || instance->group_index == NONE)
			continue;

		auto tag_name = g_cache_file->get_tag_name(i);
		auto tag_name_length = strlen(tag_name);

		if (filter && !strstr(tag_name, filter))
			continue;

		auto group = g_cache_file->get_tag_group(instance->group_index);
		auto cache_file_header = g_cache_file->get_header();

		if (group->is_in_group(group_tag))
			printf("[Index: 0x%04lX, Offset: 0x%llX] %s.%s\n",
				i,
				cache_file_header->memory_buffer_offset + g_cache_file->get_page_offset(instance->address),
				tag_name_length == 0 ? "<unnamed>" : tag_name,
				g_cache_file->get_string(group->name));
	}

	return true;
}

bool edit_tag_execute(
	long arg_count,
	char const **arg_values)
{
	if (arg_count != 1)
		return false;

	s_tag_reference reference;
	field_parse(_field_tag_reference, "reference", nullptr, &reference, arg_count, arg_values);

	auto instance = g_cache_file->get_tag_instance(reference.index & k_word_maximum);

	if (!instance || !instance->address || instance->group_index == NONE)
	{
		printf("ERROR: tag instance 0x%04lX is null!", reference.index & k_word_maximum);
		return true;
	}

	auto group = g_cache_file->get_tag_group(instance->group_index);

	if (!group)
	{
		printf("ERROR: failed to get tag group of tag instance 0x%04lX!", reference.index & k_word_maximum);
		return true;
	}

	auto group_definition = tag_group_definition_get(group->tags[0]);

	if (!group_definition)
	{
		char tag_string[5];
		printf("ERROR: tag group definition not found for group tag '%s'!\n", tag_to_string(group->tags[0], tag_string));
		return true;
	}

	long_string tag_name_string;

	auto tag_name = g_cache_file->get_tag_name(reference.index & k_word_maximum);
	auto group_name = g_cache_file->get_string(group->name);
	
	auto separator = strrchr(tag_name, '\\');
	
	if (separator)
		tag_name = separator + 1;

	sprintf(tag_name_string.ascii, "(0x%04lX) %s.%s", reference.index & k_word_maximum, tag_name, group_name);

	auto tag_definition = g_cache_file->get_tag_definition<void>(reference.index & k_word_maximum);

	switch (group->tags[0])
	{
	case k_bitmap_group_tag:
		g_command_context = new c_bitmap_command_context(
			tag_name_string.ascii,
			(s_bitmap_definition *)tag_definition,
			g_command_context);

	case k_render_model_group_tag:
		g_command_context = new c_render_model_command_context(
			tag_name_string.ascii,
			(s_render_model_definition *)tag_definition,
			g_command_context);
		break;

	default:
		g_command_context = new c_editing_command_context(
			tag_name_string.ascii,
			tag_definition,
			group_definition,
			g_command_context);
		break;
	}

	return true;
}
