#pragma once

#include <cseries/cseries.h>
#include <tag_files/tag_groups.h>
#include <cache/cache_files.h>

#include <cache/cache_file_tag_resource.inl>

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

enum e_cache_file_tag_resource_flags
{
	_cache_file_tag_resource_unknown0_bit,
	_cache_file_tag_resource_unknown1_bit,
	_cache_file_tag_resource_unknown2_bit,
	_cache_file_tag_resource_unknown3_bit,
	_cache_file_tag_resource_unknown4_bit,
	_cache_file_tag_resource_unknown5_bit,
	_cache_file_tag_resource_unknown6_bit,
	_cache_file_tag_resource_unknown7_bit,
	k_number_of_cache_file_tag_resource_flags,
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
	long block_offset;
	long compressed_block_size;
	long uncompressed_block_size;
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
	long unknown1;
	long unknown2;
	long unknown3;
	c_tag_block<s_cache_file_resource_page_sizes> sizes;
	c_tag_block<s_cache_file_resource_segment> segments;
};
static_assert(sizeof(s_cache_file_resource_layout_table) == 0x48);

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

struct s_cache_file_tag_resource_fixup
{
	dword block_offset;
	dword address;
};
static_assert(sizeof(s_cache_file_tag_resource_fixup) == 0x8);

struct s_cache_file_tag_resource
{
	s_tag_reference parent_tag;
	word identifier;
	c_tag_block_index<s_cache_file_resource_type, char> resource_type_index;
	c_flags<e_cache_file_tag_resource_flags, byte> flags;
	long definition_data_offset;
	long definition_data_length;
	long secondary_fixup_information_offset;
	short unknown20;
	c_tag_block_index<s_cache_file_resource_segment, short> segment_index;
	dword definition_address;
	c_tag_block<s_cache_file_tag_resource_fixup> resource_fixups;
	c_tag_block<s_cache_file_tag_resource_fixup> resource_definition_fixups;
};
static_assert(sizeof(s_cache_file_tag_resource) == 0x40);

struct s_cache_file_resource_gestalt
{
	c_enum<e_cache_file_resource_location, short> location;
	c_flags<e_cache_file_resource_gestalt_flags, word> flags;
	c_tag_block<s_cache_file_resource_type> resource_types;
	c_tag_block<s_cache_file_resource_structure_type> resource_structure_types;
	s_cache_file_resource_layout_table layout_table;
	c_tag_block<s_cache_file_tag_resource> tag_resources;
	//
	// TODO: finish
	//
	s_tag_block designer_zonesets;
	s_tag_block global_zoneset;
	s_tag_block unknown_zoneset1;
	s_tag_block unattached_zoneset;
	s_tag_block disc_forbidden_zoneset;
	s_tag_block disc_always_streaming_zoneset;
	s_tag_block bsp_zonesets1;
	s_tag_block bsp_zonesets2;
	s_tag_block bsp_zonesets3;
	s_tag_block cinematic_zonesets;
	s_tag_block scenario_zonesets;
	s_tag_block unknown_zonesets2;
	s_tag_block unknown_zonesets3;
	s_tag_block scenario_zoneset_groups;
	s_tag_block scenario_bsps;
	s_tag_block unknown_block1;
	s_tag_block unknown_block2;
	s_tag_block unknown_block3;
	s_tag_data definition_data;
	long unknown1;
	long unknown2;
	long unknown3;
	long unknown4;
	long unknown5;
	s_tag_block unknown_block4;
	s_tag_block unknown_block5;
	s_tag_block unknown_block6;
	s_tag_block unknown_block7;
	s_tag_block unknown_block8;
	s_tag_block unknown_block9;
	s_tag_block unknown_block10;
	s_tag_block unknown_block11;
	s_tag_block unknown_block12;
	s_tag_block block_a;
	s_tag_block block_b;
	s_tag_block block_c;
	s_tag_block block_d1;
	s_tag_block block_d2;
	//
	// END TODO
	//
	long campaign_id;
	long map_id;
};
static_assert(sizeof(s_cache_file_resource_gestalt) == 0x220);
