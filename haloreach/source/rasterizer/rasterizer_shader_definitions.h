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
	s_tag_data unknown2C;
	long unknown40;
	long unknown44;
	long unknown48;
	long unknown4C;
	long unknown50;
	long unknown54;
	long unknown58;
	long unknown5C;
	long unknown60;
	long unknown64;
	long unknown68;
	long unknown6C;
	long unknown70;
	long unknown74;
	long unknown78;
	long unknown7C;
	long unknown80;
	long unknown84;
	long unknown88;
	long unknown8C;
	long unknown90;
	long unknown94;
};
static_assert(sizeof(s_rasterizer_compiled_shader) == 0x98);

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
