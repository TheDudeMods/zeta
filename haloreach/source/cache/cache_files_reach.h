/*
CACHE_FILES_REACH.H
*/

#pragma once

#include <haloreach.h>

#include <cseries/cseries.h>
#include <cache/cache_files.h>
#include <tag_files/tag_groups.h>

/* ---------- constants */

enum e_cache_file_partition
{
	_cache_file_partition_resources,
	_cache_file_partition_gestalt_resources,
	_cache_file_partition_tags,
	_cache_file_partition_shared,
	_cache_file_partition_base,
	_cache_file_partition_multiplayer,
	k_number_of_cache_file_partitions
};

enum e_cache_file_section
{
	_cache_file_section_debug,
	_cache_file_section_resource,
	_cache_file_section_tags,
	_cache_file_section_localization,
	k_number_of_cache_file_sections
};

/* ---------- structures */

struct s_cache_file_partition
{
	qword base_address;
	qword size;
};
static_assert(sizeof(s_cache_file_partition) == 0x10);

struct s_cache_file_section
{
	dword virtual_address;
	dword size;
};
static_assert(sizeof(s_cache_file_section) == 0x8);

struct s_cache_file_interop
{
	dword unknown0;
	dword unknown4;
	dword unknown8;
	dword unknownC;
	dword resource_base_offset;
	dword debug_section_size;
	dword runtime_base_offset;
	dword unknown_base_offset;
	s_cache_file_section sections[k_number_of_cache_file_sections];
};
static_assert(sizeof(s_cache_file_interop) == 0x40);

struct s_cache_tag_instance
{
	short group_index;
	short identifier;
	dword page_address;
};
static_assert(sizeof(s_cache_tag_instance) == 0x8);

struct s_cache_tag_index_header
{
	qword group_count;
	qword groups_address;
	qword tag_count;
	qword tags_address;
	qword important_group_count;
	qword important_groups_address;
	qword tag_interop_table_count;
	qword tag_interop_table_address;
	long unknown44;
	long unknown48;
	tag signature;
	long : 32;
};
static_assert(sizeof(s_cache_tag_index_header) == 0x50);

struct s_cache_file_header
{
	tag header_signature;
	long file_version;
	long file_length;
	long file_compressed_length;
	qword tag_index_address;
	long memory_buffer_offset;
	long memory_buffer_size;
	u_long_string source_file;
	u_short_string build;
	c_enum<e_scenario_type, short> scenario_type;
	c_enum<e_scenario_load_type, short> load_type;
	char unknown1;
	bool tracked_build;
	char unknown2;
	char unknown3;
	long unknown4;
	long unknown5;
	long unknown6;
	long unknown7;
	long unknown8;
	long string_id_count;
	long string_ids_buffer_size;
	long string_id_indices_offset;
	long string_ids_buffer_offset;
	long unknown9;
	qword unknown10;
	qword unknown11;
	qword unknown12;
	qword unknown13;
	qword unknown14;
	u_short_string name;
	long unknown15;
	u_long_string scenario_path;
	long unknown16;
	long tag_name_count;
	long tag_names_buffer_offset;
	long tag_names_buffer_size;
	long tag_name_indices_offset;
	dword checksum;
	long unknown17;
	long unknown18;
	long unknown19;
	long unknown20;
	long unknown21;
	long unknown22;
	long unknown23;
	long unknown24;
	long unknown25;
	qword virtual_base_address;
	qword virtual_base_size;
	s_cache_file_partition partitions[k_number_of_cache_file_partitions];
	qword unknown29;
	qword unknown30;
	long sha1_a[5];
	long sha1_b[5];
	long sha1_c[5];
	long rsa[64];
	s_cache_file_interop interop;
	long guid[4];
	long unknown32[0x26BE];
	tag footer_signature;
};
static_assert(sizeof(s_cache_file_header) == 0xA000);

/* ---------- classes */

class BLAMAPI c_cache_file_reach : public c_cache_file
{
public:
};
