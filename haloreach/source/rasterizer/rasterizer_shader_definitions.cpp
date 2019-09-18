#include <rasterizer/rasterizer_shader_definitions.h>

/* ---------- definitions */

TAG_BLOCK(
	rasterizer_shader_draw_mode_block,
	sizeof(s_rasterizer_shader_draw_mode),
	NONE)
{
	{ _field_byte_integer, "offset" },
	{ _field_byte_integer, "count" },
	{ _field_terminator }
};

TAG_ENUM(
	rasterizer_shader_register_type_enum,
	k_number_of_rasterizer_shader_register_types)
{
	{ "boolean", _rasterizer_shader_register_boolean },
	{ "integer", _rasterizer_shader_register_integer },
	{ "vector", _rasterizer_shader_register_vector },
	{ "sampler", _rasterizer_shader_register_sampler },
};

TAG_BLOCK(
	rasterizer_shader_constant_block,
	sizeof(s_rasterizer_shader_constant),
	NONE)
{
	{ _field_string_id, "name" },
	{ _field_word_integer, "register_index" },
	{ _field_byte_integer, "register_count" },
	{ _field_char_enum, "register_type", &rasterizer_shader_register_type_enum },
	{ _field_terminator }
};

TAG_BLOCK(
	rasterizer_compiled_shader_block,
	sizeof(s_rasterizer_compiled_shader),
	NONE)
{
	{ _field_long_integer, "unknown0" },
	{ _field_data, "xbox_data" },
	{ _field_data, "pc_data" },
	{ _field_block, "xbox_constants", &rasterizer_shader_constant_block },
	{ _field_long_integer, "unknown38" },
	{ _field_block, "pc_constants", &rasterizer_shader_constant_block },
	{ _field_long_integer, "unknown48" },
	{ _field_long_integer, "unknown4C" },
	{ _field_long_integer, "global_cache_shader_index" },
	{ _field_dword_integer, "address" },
	{ _field_terminator }
};

TAG_GROUP(
	rasterizer_shader_group,
	NONE,
	sizeof(c_rasterizer_shader))
{
	{ _field_long_integer, "unknown0" },
	{ _field_block, "draw_modes", &rasterizer_shader_draw_mode_block },
	{ _field_long_integer, "unknown10" },
	{ _field_block, "compiled_shaders", &rasterizer_compiled_shader_block },
	{ _field_terminator }
};

TAG_GROUP(
	pixel_shader_group,
	k_pixel_shader_group_tag,
	sizeof(c_rasterizer_pixel_shader) - sizeof(c_rasterizer_shader),
	&rasterizer_shader_group)
{
	{ _field_terminator }
};

TAG_GROUP(
	vertex_shader_group,
	k_vertex_shader_group_tag,
	sizeof(c_rasterizer_vertex_shader) - sizeof(c_rasterizer_shader),
	&rasterizer_shader_group)
{
	{ _field_terminator }
};
