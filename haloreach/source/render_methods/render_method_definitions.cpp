#include <render_methods/render_method_definitions.h>

extern s_enum_definition function_variable_type_enum;
extern s_enum_definition function_output_modifier_enum;

TAG_REFERENCE(
	render_method_reference,
	1)
{
	k_render_method_group_tag
};

TAG_BLOCK(
	render_method_option_reference_block,
	sizeof(s_render_method_option_reference),
	NONE)
{
	{ _field_short_integer, "index" },
	{ _field_terminator }
};

TAG_BLOCK(
	render_method_import_data_block,
	sizeof(s_render_method_import_data),
	NONE)
{
	{ _field_explanation, "TODO: define render_method_import_data_block" },
	{ _field_terminator }
};

TAG_BLOCK(
	render_method_animated_parameter_block,
	sizeof(s_render_method_animated_parameter),
	NONE)
{
	{ _field_explanation, "TODO: define render_method_animated_parameter_block" },
	{ _field_terminator }
};

TAG_BLOCK(
	render_method_postprocess_definition_block,
	sizeof(s_render_method_postprocess_definition),
	NONE)
{
	{ _field_explanation, "TODO: define render_method_postprocess_block" },
	{ _field_terminator }
};

TAG_BLOCK(
	render_method_unknown_block,
	sizeof(s_render_method_unknown),
	NONE)
{
	{ _field_explanation, "TODO: define render_method_unknown_block" },
	{ _field_terminator }
};

TAG_GROUP(
	render_method_group,
	k_render_method_group_tag,
	sizeof(c_render_method))
{
	{ _field_tag_reference, "base_render_method", &render_method_reference },
	{ _field_tag_reference, "unknown10", &render_method_reference },
	{ _field_block, "options", &render_method_option_reference_block },
	{ _field_block, "import_data", &render_method_import_data_block },
	{ _field_block, "postprocess_definitions", &render_method_postprocess_definition_block },
	{ _field_long_integer, "unknown54" },
	{ _field_long_integer, "unknown58" },
	{ _field_block, "unknown5C", &render_method_unknown_block },
	{ _field_char_enum, "input_variable", &function_variable_type_enum },
	{ _field_char_enum, "range_variable", &function_variable_type_enum },
	{ _field_char_enum, "output_modifier", &function_output_modifier_enum },
	{ _field_char_enum, "output_modifier_input", &function_variable_type_enum },
	{ _field_real, "runtime_m_constant_value" },
	{ _field_long_integer, "runtime_m_index" },
	{ _field_terminator }
};

TAG_GROUP(
	render_method_shader_group,
	k_render_method_shader_group_tag,
	sizeof(c_render_method_shader) - sizeof(c_render_method),
	&render_method_group)
{
	{ _field_string_id, "material_name" },
	{ _field_terminator }
};
