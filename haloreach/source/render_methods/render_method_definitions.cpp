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

TAG_PAD(
	_field_long_integer,
	render_method_postprocess_useless_padding,
	1);

TAG_BLOCK(
	render_method_postprocess_definition_block,
	sizeof(s_render_method_postprocess_definition),
	NONE)
{
	{ _field_tag_reference, "base_template", nullptr }, // TODO
	{ _field_block, "shader_maps", nullptr }, // TODO
	{ _field_block, "arguments", nullptr }, // TODO
	{ _field_block, "unknown1", nullptr }, // TODO
	{ _field_long_integer, "unknown2" },
	{ _field_block, "unknown3", nullptr }, // TODO
	{ _field_block, "unknown4", nullptr }, // TODO
	{ _field_block, "unknown5", nullptr }, // TODO
	{ _field_block, "functions", nullptr }, // TODO
	{ _field_long_integer, "unknown6" },
	{ _field_long_integer, "unknown7" },
	{ _field_real, "unknown8" },
	{ _field_short_integer, "unknown9" },
	{ _field_short_integer, "unknown10" },
	{ _field_short_integer, "unknown11" },
	{ _field_short_integer, "unknown12" },
	{ _field_short_integer, "unknown13" },
	{ _field_short_integer, "unknown14" },
	{ _field_short_integer, "unknown15" },
	{ _field_short_integer, "unknown16" },
	{ _field_short_integer, "unknown17" },
	{ _field_short_integer, "unknown18" },
	{ _field_short_integer, "unknown19" },
	{ _field_short_integer, "unknown20" },
	{ _field_short_integer, "unknown21" },
	{ _field_short_integer, "unknown22" },
	{ _field_short_integer, "unknown23" },
	{ _field_short_integer, "unknown24" },
	{ _field_short_integer, "unknown25" },
	{ _field_short_integer, "unknown26" },
	{ _field_short_integer, "unknown27" },
	{ _field_short_integer, "unknown28" },
	{ _field_short_integer, "unknown29" },
	{ _field_short_integer, "unknown30" },
	{ _field_short_integer, "unknown31" },
	{ _field_short_integer, "unknown32" },
	{ _field_short_integer, "unknown33" },
	{ _field_short_integer, "unknown34" },
	{ _field_short_integer, "unknown35" },
	{ _field_short_integer, "unknown36" },
	{ _field_long_integer, "resource_index" },
	{ _field_pad, "", &render_method_postprocess_useless_padding },
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
