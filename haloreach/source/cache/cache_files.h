#pragma once

#include <cseries/cseries.h>
#include <cache/cache_files_base.h>
#include <datatypes/enum.h>
#include <datatypes/static_string.h>
#include <datatypes/tag.h>
#include <tag_files/string_ids.h>
#include <scenario/scenario.h>

/* ---------- constants */

enum
{
	k_cache_file_header_signature = 'head',
	k_cache_file_footer_signature = 'foot',
	k_cache_file_tags_signature = 'tags',
	k_cache_file_tags_section_signature = '343i',
};

/* ---------- enumerators */

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
	ulonglong address;
	ulonglong size;
};
static_assert(sizeof(s_cache_file_partition) == 0x10);

struct s_cache_file_section
{
	ulong address;
	ulong size;
};
static_assert(sizeof(s_cache_file_section) == 0x8);

struct s_cache_file_interop
{
	ulong unknown0;
	ulong unknown4;
	ulong unknown8;
	ulong unknownC;
	ulong resource_base_offset;
	ulong debug_section_size;
	ulong runtime_base_offset;
	ulong unknown_base_offset;
	s_cache_file_section sections[k_number_of_cache_file_sections];
};
static_assert(sizeof(s_cache_file_interop) == 0x40);

struct s_cache_file_header
{
	tag header_signature;
	long file_version;
	long file_length;
	long file_compressed_length;
	ulonglong tags_header_address;
	long memory_buffer_offset;
	long memory_buffer_size;
	c_static_string<256> source_file;
	c_static_string<32> build;
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
	ulonglong timestamp;
	ulonglong mainmenu_timestamp;
	ulonglong shared_timestamp;
	ulonglong campaign_timestamp;
	ulonglong multiplayer_timestamp;
	c_static_string<32> name;
	long unknown15;
	c_static_string<256> scenario_path;
	long minor_version;
	long tag_name_count;
	long tag_names_buffer_offset;
	long tag_names_buffer_size;
	long tag_name_indices_offset;
	ulong checksum;
	long unknown17;
	long unknown18;
	long unknown19;
	long unknown20;
	long unknown21;
	long unknown22;
	long unknown23;
	long unknown24;
	long unknown25;
	ulonglong virtual_base_address;
	ulong xdk_version;
	long unknown26;
	s_cache_file_partition partitions[k_number_of_cache_file_partitions];
	ulonglong unknown29;
	ulonglong unknown30;
	long sha1_a[5];
	long sha1_b[5];
	long sha1_c[5];
	long rsa[64];
	s_cache_file_interop interop;
	long guid[4];
	long unknown34[0x26BE];
	tag footer_signature;
};
static_assert(sizeof(s_cache_file_header) == 0xA000);

struct s_cache_file_tag_instance
{
	short group_index;
	ushort identifier;
	ulong address;
};
static_assert(sizeof(s_cache_file_tag_instance) == 0x8);

struct s_cache_file_tags_section
{
	ulong count = 0;
	tag post_count_signature = k_cache_file_tags_section_signature;
	ulonglong address = 0;
};
static_assert(sizeof(s_cache_file_tags_section) == 0x10);

struct s_cache_file_tags_header
{
	s_cache_file_tags_section groups;
	s_cache_file_tags_section instances;
	s_cache_file_tags_section important_groups;
	s_cache_file_tags_section interop_table;
	long unknown40; // datum index?
	ulong checksum;
	tag signature;
	long unknown4C; // datum index?
};
static_assert(sizeof(s_cache_file_tags_header) == 0x50);

/* ---------- classes */

struct s_tag_group;

class c_cache_file_reach : public c_cache_file
{
private:
	ulonglong m_address_mask;
	s_cache_file_header m_header;
	char *m_memory_buffer;
	long *m_string_id_indices;
	char *m_string_ids_buffer;
	long *m_tag_name_indices;
	char *m_tag_names_buffer;

public:
	c_cache_file_reach(char const *filename);
	~c_cache_file_reach();

	s_cache_file_header *get_header();
	s_cache_file_tags_header *get_tags_header();

	char const *get_string(string_id id);

	char const *get_tag_name(long index);
	
	long find_tag_group(tag group_tag);
	s_tag_group *get_tag_group(long index);

	s_cache_file_tag_instance *get_tag_instance(long index);

	bool tag_resource_definition_try_and_get(
		long resource_index,
		void **out_address);

	template <typename t_definition>
	inline t_definition *tag_resource_definition_get(
		long resource_index)
	{
		t_definition *definition = nullptr;
		
		if (!tag_resource_definition_try_and_get(resource_index, (void **)&definition))
			return nullptr;

		return definition;
	}

	bool tag_resource_try_and_get(
		long resource_index,
		long *out_length,
		void **out_address);
	
	void *get_resource_page_data(
		struct s_cache_file_resource_physical_location *location,
		struct s_cache_file_resource_page *page);

	template <typename t_data>
	t_data *get_buffer_data(ulonglong address)
	{
		if (address == 0)
			return nullptr;

		return (t_data *)(address + m_address_mask);
	}

	ulonglong get_page_offset(ulong address);
	ulong make_page_offset(ulonglong address);

	template <typename t_data>
	t_data *get_page_data(ulong address)
	{
		if (address == 0)
			return nullptr;

		return (t_data *)(m_memory_buffer + get_page_offset(address));
	}

	template <typename t_tag_definition>
	t_tag_definition *get_tag_definition(long index)
	{
		auto instance = get_tag_instance(index);

		if (!instance || instance->address == 0)
			return nullptr;
		
		return get_page_data<t_tag_definition>(instance->address);
	}
};

/* ---------- prototypes/CACHE_FILES.CPP */

c_cache_file_reach *cache_file_load();
void cache_files_close();
