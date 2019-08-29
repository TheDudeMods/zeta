#pragma once

#include <cseries/cseries.h>
#include <tag_files/tag_groups.h>
#include <math/function_definitions.h>

/* ---------- constants */

enum
{
    k_render_method_group_tag = 'rm  ',
	k_render_method_shader_group_tag = 'rmsh',
};

/* ---------- types */

struct s_render_method_option_reference
{
	short index;
};
static_assert(sizeof(s_render_method_option_reference) == 0x2);

struct s_render_method_import_data
{
	// TODO
};

struct s_render_method_animated_parameter
{
	// TODO
};

struct s_render_method_postprocess_definition
{
	// TODO
};

struct s_render_method_unknown
{
	// TODO
};

/* ---------- classes */

class c_render_method
{
public:
	s_tag_reference base_render_method;
	s_tag_reference unknown10;
	c_tag_block<s_render_method_option_reference> options;
	c_tag_block<s_render_method_import_data> import_data;
	c_tag_block<s_render_method_postprocess_definition> postprocess_definitions;
	long unknown54;
	long unknown58;
	c_tag_block<s_render_method_unknown> unknown5C;
	c_enum<e_function_variable_type, char> input_variable;
	c_enum<e_function_variable_type, char> range_variable;
	c_enum<e_function_output_modifier, char> output_modifier;
	c_enum<e_function_variable_type, char> output_modifier_input;
	real runtime_m_constant_value;
	long runtime_m_index;
};
static_assert(sizeof(c_render_method) == 0x64);

class c_render_method_shader : public c_render_method
{
public:
	string_id material_name;
};
static_assert(sizeof(c_render_method_shader) == sizeof(c_render_method) + 0x4);
