#pragma once

#include <cseries/cseries.h>
#include <tag_files/tag_groups.h>
#include <cache/cache_files.h>

/* ---------- constants */

enum
{
	k_cache_file_resource_gestalt_group_tag = 'zone',
	k_cache_file_resource_layout_table_group_tag = 'play',
};

/* ---------- enumerators */

enum e_cache_file_resource_page_flags
{
	_cache_file_resource_page_unknown0_bit,
	_cache_file_resource_page_unknown1_bit,
	_cache_file_resource_page_unknown2_bit,
	_cache_file_resource_page_unknown3_bit,
	_cache_file_resource_page_unknown4_bit,
	_cache_file_resource_page_unknown5_bit,
	_cache_file_resource_page_unknown6_bit,
	_cache_file_resource_page_unknown7_bit,
	k_number_of_cache_file_resource_page_flags,
};

enum e_cache_file_resource_location
{
	_cache_file_type_none = NONE,
	_cache_file_type_campaign,
	_cache_file_type_mainmenu,
	_cache_file_type_multiplayer,
	k_number_of_cache_file_types
};

enum e_cache_file_resource_gestalt_flags
{
	_cache_file_resource_gestalt_unknown0_bit,
	_cache_file_resource_gestalt_unknown1_bit,
	_cache_file_resource_gestalt_unknown2_bit,
	_cache_file_resource_gestalt_unknown3_bit,
	_cache_file_resource_gestalt_unknown4_bit,
	_cache_file_resource_gestalt_unknown5_bit,
	_cache_file_resource_gestalt_unknown6_bit,
	_cache_file_resource_gestalt_unknown7_bit,
	_cache_file_resource_gestalt_unknown8_bit,
	_cache_file_resource_gestalt_unknown9_bit,
	_cache_file_resource_gestalt_unknown10_bit,
	_cache_file_resource_gestalt_unknown11_bit,
	_cache_file_resource_gestalt_unknown12_bit,
	_cache_file_resource_gestalt_unknown13_bit,
	_cache_file_resource_gestalt_unknown14_bit,
	_cache_file_resource_gestalt_unknown15_bit,
	k_number_of_cache_file_resource_gestalt_flags,
};

/* ---------- structures */

struct s_cache_file_resource_compression_codec
{
	long guid[4];
};
static_assert(sizeof(s_cache_file_resource_compression_codec) == 0x10);

struct s_cache_file_resource_physical_location
{
	short_string path;
	long unknown[58];
};
static_assert(sizeof(s_cache_file_resource_physical_location) == 0x108);

struct s_cache_file_resource_page
{
	word identifier;
	c_flags<e_cache_file_resource_page_flags, byte> flags;
	c_tag_block_index<s_cache_file_resource_compression_codec, char> compression_codec;
	c_tag_block_index<s_cache_file_resource_physical_location, short> shared_cache_file;
	short : 16;
	dword block_offset;
	dword compressed_block_size;
	dword uncompressed_block_size;
	long crc;
	long sha1_a[5];
	long sha1_b[5];
	long sha1_c[5];
	short block_asset_count;
	short unknown;
};
static_assert(sizeof(s_cache_file_resource_page) == 0x58);

struct s_cache_file_resource_segment_sizes
{
	long size1;
	long size2;
};
static_assert(sizeof(s_cache_file_resource_segment_sizes) == 0x8);

struct s_cache_file_resource_page_sizes
{
	long total_size;
	c_tag_block<s_cache_file_resource_segment_sizes> segments;
};
static_assert(sizeof(s_cache_file_resource_page_sizes) == 0x10);

struct s_cache_file_resource_segment
{
	c_tag_block_index<s_cache_file_resource_page, short> primary_page;
	c_tag_block_index<s_cache_file_resource_page, short> secondary_page;
	long primary_segment_offset;
	long secondary_segment_offset;
	c_tag_block_index<s_cache_file_resource_page_sizes, short> primary_size;
	c_tag_block_index<s_cache_file_resource_page_sizes, short> secondary_size;
};
static_assert(sizeof(s_cache_file_resource_segment) == 0x10);

struct s_cache_file_resource_layout_table
{
	c_tag_block<s_cache_file_resource_compression_codec> compression_codecs;
	c_tag_block<s_cache_file_resource_physical_location> physical_locations;
	c_tag_block<s_cache_file_resource_page> pages;
	c_tag_block<s_cache_file_resource_page_sizes> sizes;
	c_tag_block<s_cache_file_resource_segment> segments;
};
static_assert(sizeof(s_cache_file_resource_layout_table) == 0x3C);

struct s_cache_file_resource_type
{
	long guid[4];
	short unknown10;
	short unknown12;
	short unknown14;
	short unknown16;
	string_id name;
};
static_assert(sizeof(s_cache_file_resource_type) == 0x1C);

struct s_cache_file_resource_structure_type
{
	long guid[4];
	string_id name;
};
static_assert(sizeof(s_cache_file_resource_structure_type) == 0x14);

struct s_cache_file_resource_gestalt
{
	c_enum<e_cache_file_resource_location, short> location;
	c_flags<e_cache_file_resource_gestalt_flags, word> flags;
	c_tag_block<s_cache_file_resource_type> resource_types;
	c_tag_block<s_cache_file_resource_structure_type> resource_structure_types;
	s_cache_file_resource_layout_table layout_table;
};
