#include <cache/cache_files.h>
#include <commands/editing_commands.h>
#include <math/integer_math.h>
#include <math/real_math.h>
#include <tag_files/tag_groups.h>

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>

/* ---------- code */

c_editing_command_context::c_editing_command_context(
	char const *name,
	void *address,
	s_struct_definition *definition,
	c_cache_file_reach *file,
	c_command_context *parent) :
	c_command_context(
		name,
		NUMBEROF(k_editing_command_sets),
		k_editing_command_sets,
		file,
		parent),
	m_address(address),
	m_definition(definition)
{
}

void *c_editing_command_context::get_address()
{
	return m_address;
}

s_struct_definition *c_editing_command_context::get_definition()
{
	return m_definition;
}

bool list_fields_execute(
	long arg_count,
	char const **arg_values)
{
	if (arg_count > 1)
		return false;

	auto editing_context = dynamic_cast<c_editing_command_context *>(g_command_context);
	auto file = editing_context->get_file();

	if (!editing_context)
	{
		puts("ERROR: invalid command context!");
		return true;
	}

	auto address = editing_context->get_address();
	auto definition = editing_context->get_definition();

	struct_print(file, definition, address, arg_count == 1 ? arg_values[0] : nullptr);
	
	return true;
}

bool set_field_execute(
	long arg_count,
	char const **arg_values)
{
	if (arg_count < 2)
		return false;

	auto field_name = arg_values[0];

	auto editing_context = dynamic_cast<c_editing_command_context *>(g_command_context);
	auto file = editing_context->get_file();

	if (!editing_context)
	{
		puts("ERROR: invalid command context!");
		return true;
	}

	auto address = editing_context->get_address();
	auto definition = editing_context->get_definition();

	auto field = struct_get_field(definition, field_name, &address);

	if (!field)
	{
		printf("ERROR: no field named '%s' found in '%s' struct!\n", field_name, definition->name);
		return true;
	}

	if (!field_parse(file, field->type, field->name, field->definition, address, arg_count - 1, &arg_values[1]))
	{
		printf("ERROR: failed to parse '%s' field value!\n", field->name);
		return false;
	}

	field_print(file, field->type, field->name, field->definition, address);

	return true;
}

bool edit_block_execute(
	long arg_count,
	char const **arg_values)
{
	if (arg_count < 1)
		return false;

	auto field_name = arg_values[0];

	auto editing_context = dynamic_cast<c_editing_command_context *>(g_command_context);
	auto file = editing_context->get_file();

	if (!editing_context)
	{
		puts("ERROR: invalid command context!");
		return true;
	}

	auto address = editing_context->get_address();
	auto definition = editing_context->get_definition();

	auto field = struct_get_field(definition, field_name, &address);

	if (!field)
	{
		printf("ERROR: %s does not contain a field named \"%s\"!\n",
			definition->name, field_name);
		return true;
	}

	c_static_string<256> context_name;

	switch (field->type)
	{
	case _field_block:
	{
		if (arg_count != 2)
			return false;
		
		auto block = (s_tag_block *)address;
		auto block_definition = (s_tag_block_definition *)field->definition;

		auto index = csstrcmp(arg_values[1], "*") != 0 ?
			(long)strtoul(arg_values[1], nullptr, 0) :
			block->count - 1;

		if (index < 0 || index >= block->count)
		{
			printf("ERROR: invalid %s index: %i (valid range: 0-%i)\n",
				block_definition->name, index, block->count);
			return true;
		}

		address = file->get_tags_section_pointer_from_page_offset<char>(block->address) + ((ulonglong)index * (ulonglong)block_definition->size);
		sprintf(context_name.get_buffer(), "%s[%u]", field->name, index);
		break;
	}

	case _field_struct:
	{
		if (arg_count != 1)
			return false;

		sprintf(context_name.get_buffer(), "%s", field->name);
		break;
	}

	default:
		printf("ERROR: cannot edit '%s' field in '%s'!\n", field->name, definition->name);
		return false;
	}

	g_command_context = new c_editing_command_context(
		context_name.get_buffer(),
		address,
		(s_struct_definition *)field->definition,
		file,
		g_command_context);

	return true;
}
