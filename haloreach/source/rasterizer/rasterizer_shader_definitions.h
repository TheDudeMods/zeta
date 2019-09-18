#pragma once

#include <cseries/cseries.h>
#include <datatypes/enum.h>
#include <tag_files/string_ids.h>
#include <tag_files/tag_groups.h>

/* ---------- constants */

enum
{
	k_pixel_shader_group_tag = 'pixl',
	k_vertex_shader_group_tag = 'vtsh',
};

/* ---------- types */

struct s_rasterizer_shader_draw_mode
{
	uchar offset;
	uchar count;
};
static_assert(sizeof(s_rasterizer_shader_draw_mode) == 0x2);

enum e_rasterizer_shader_register_type
{
	_rasterizer_shader_register_boolean,
	_rasterizer_shader_register_integer,
	_rasterizer_shader_register_vector,
	_rasterizer_shader_register_sampler,
	k_number_of_rasterizer_shader_register_types
};

struct s_rasterizer_shader_constant
{
	string_id name;
	ushort register_index;
	uchar register_count;
	c_enum<e_rasterizer_shader_register_type, char> register_type;
};
static_assert(sizeof(s_rasterizer_shader_constant) == 0x8);

struct s_rasterizer_compiled_shader
{
	long unknown0;
	s_tag_data xbox_data;
	s_tag_data pc_data;
	c_tag_block<s_rasterizer_shader_constant> xbox_constants;
	long unknown38;
	c_tag_block<s_rasterizer_shader_constant> pc_constants;
	long unknown48;
	long unknown4C;
	long global_cache_shader_index;
	ulong address;
};
static_assert(sizeof(s_rasterizer_compiled_shader) == 0x58);

/* ---------- classes */

class c_rasterizer_shader
{
public:
	long unknown0;
	c_tag_block<s_rasterizer_shader_draw_mode> draw_modes;
	long unknown10;
	c_tag_block<s_rasterizer_compiled_shader> compiled_shaders;
};
static_assert(sizeof(c_rasterizer_shader) == 0x20);

class c_rasterizer_pixel_shader :
	public c_rasterizer_shader
{
};
static_assert(sizeof(c_rasterizer_pixel_shader) == 0x20);

class c_rasterizer_vertex_shader :
	public c_rasterizer_shader
{
};
static_assert(sizeof(c_rasterizer_vertex_shader) == 0x20);
