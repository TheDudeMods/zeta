/*
CACHE_FILES_REACH.H
*/

#pragma once

#include <cseries/cseries.h>
#include <cache/cache_files.h>
#include <tag_files/tag_groups_reach.h>

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

struct s_cache_file_partition_reach
{
	qword address;
	qword size;
};
static_assert(sizeof(s_cache_file_partition_reach) == 0x10);

struct s_cache_file_section_reach
{
	dword address;
	dword size;
};
static_assert(sizeof(s_cache_file_section_reach) == 0x8);

struct s_cache_file_interop_reach
{
	dword unknown0;
	dword unknown4;
	dword unknown8;
	dword unknownC;
	dword resource_base_offset;
	dword debug_section_size;
	dword runtime_base_offset;
	dword unknown_base_offset;
	s_cache_file_section_reach sections[k_number_of_cache_file_sections];
};
static_assert(sizeof(s_cache_file_interop_reach) == 0x40);

struct s_cache_tag_instance_reach
{
	short group_index;
	short identifier;
	dword address;
};
static_assert(sizeof(s_cache_tag_instance_reach) == 0x8);

struct s_cache_tag_index_header_reach
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
static_assert(sizeof(s_cache_tag_index_header_reach) == 0x50);

struct s_cache_file_header_reach
{
	tag header_signature;
	long file_version;
	long file_length;
	long file_compressed_length;
	qword tag_index_address;
	long memory_buffer_offset;
	long memory_buffer_size;
	long_string source_file;
	short_string build;
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
	qword timestamp;
	qword mainmenu_timestamp;
	qword shared_timestamp;
	qword campaign_timestamp;
	qword multiplayer_timestamp;
	short_string name;
	long unknown15;
	long_string scenario_path;
	long minor_version;
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
	dword xdk_version;
	long unknown26;
	s_cache_file_partition_reach partitions[k_number_of_cache_file_partitions];
	qword unknown29;
	qword unknown30;
	long sha1_a[5];
	long sha1_b[5];
	long sha1_c[5];
	long rsa[64];
	s_cache_file_interop_reach interop;
	long guid[4];
	long unknown32[0x26BE];
	tag footer_signature;
};
static_assert(sizeof(s_cache_file_header_reach) == 0xA000);

/* ---------- classes */

class c_cache_file_header_reach : public c_cache_file_header
{
public:
	c_cache_file_header_reach();
	c_cache_file_header_reach(void *header);
	c_cache_file_header_reach(c_cache_file_header_reach const &header);

	long get_file_version() const override;
	void set_file_version(long version) override;

	long get_file_length() const override;
	void set_file_length(long length) override;

	qword get_tag_index_address() const override;
	void set_tag_index_address(qword address) override;

	long get_memory_buffer_offset() const override;
	void set_memory_buffer_offset(long offset) override;

	long get_memory_buffer_size() const override;
	void set_memory_buffer_size(long size) override;

	char const *get_build_name() const override;
	void set_build_name(char const *name) override;

	e_scenario_type get_scenario_type() const override;
	void set_scenario_type(e_scenario_type const &type) override;

	e_scenario_load_type get_scenario_load_type() const override;
	void set_scenario_load_type(e_scenario_load_type const &type) override;

	char const *get_name() const override;
	void set_name(char const *name) override;

	qword get_virtual_base_address() const override;
	void set_virtual_base_address(qword const &address) override;
};

class c_cache_tag_index_reach : public c_cache_tag_index
{
public:
};

class c_cache_tag_instance_reach : public c_cache_tag_instance
{
public:
};

class c_cache_file_reach : public c_cache_file
{
protected:
	c_cache_file_header_reach m_header;
	c_cache_tag_index_reach m_tag_index;

public:
	c_cache_file_reach();
	c_cache_file_reach(char const *path);
	c_cache_file_reach(c_cache_file_reach const &file);

	dword get_magic32() const override;
	qword get_magic64() const override;

	c_cache_file_header &get_header() override;
	c_cache_tag_index &get_tag_index() override;
	c_cache_tag_instance get_tag_instance(long index) override;
};
