#pragma once

#include <cseries/cseries.h>
#include <cache/cache_files_base.h>
#include <datatypes/enum.h>
#include <datatypes/static_array.h>
#include <datatypes/static_string.h>
#include <datatypes/tag.h>
#include <memory/allocation_interface.h>
#include <memory/memory_interface.h>
#include <tag_files/string_ids.h>
#include <scenario/scenario_types.h>

/* ---------- constants */

enum
{
	k_cache_file_header_signature = 'head',
	k_cache_file_footer_signature = 'foot',
	k_cache_file_tags_signature = 'tags',
	k_cache_file_tags_section_signature = '343i',
};

/* ---------- types */

struct s_cache_file_section_file_bounds
{
	long offset;
	long size;
};
static_assert(sizeof(s_cache_file_section_file_bounds) == 0x8);

struct s_cache_file_tag_group
{
	tag group_tags[3];
	string_id name;

	bool is_in_group(tag group_tag) const;
	bool is_in_group(s_cache_file_tag_group &group) const;
};
static_assert(sizeof(s_cache_file_tag_group) == 0x10);

struct s_cache_file_tag_instance
{
	short group_index;
	ushort identifier;
	ulong address;
};
static_assert(sizeof(s_cache_file_tag_instance) == 0x8);

struct s_cache_file_tag_global_instance
{
	tag group_tag;
	long definition_index;
};
static_assert(sizeof(s_cache_file_tag_global_instance) == 0x8);

struct s_cache_file_tag_interop
{
	ulong page_address;
	long count;
};

struct s_cache_file_tags_header
{
	template <typename t_type>
	struct s_section
	{
		long count = 0;
		tag post_count_signature = k_cache_file_tags_section_signature;
		ulonglong address = 0;
	};

	s_section<s_cache_file_tag_group> groups;
	s_section<s_cache_file_tag_instance> instances;
	s_section<s_cache_file_tag_global_instance> global_instances;
	s_section<s_cache_file_tag_interop> interop_table;

	long unknown40; // datum index?

	ulong checksum;
	tag signature;

	long unknown4C; // datum index?
};
static_assert(sizeof(s_cache_file_tags_header) == 0x50);

enum e_cache_file_section
{
	_cache_file_section_debug,
	_cache_file_section_resource,
	_cache_file_section_tags,
	_cache_file_section_localization,
	k_number_of_cache_file_sections
};

enum e_cache_file_content_hash
{
	_cache_file_content_hash_tags_internal,
	_cache_file_content_hash_tags_language_dependent,
	_cache_file_content_hash_tags_language_neutral,
	k_number_of_cache_file_content_hashes
};

struct s_cache_file_header
{
	//Comments represent the size of the data structure (above the line)
	//and the offset in the .map file (to the right of the line)
	//This is valid for Halo Reach MCC on PC

	//sizeof 4
	tag header_signature; //0x0000

	//sizeof 4
	long file_version;	//0x004
	long file_length;	//0x008
	long file_compressed_length;	//0x000C

	//sizeof 8
	ulonglong tags_header_address;	//0x0010

	long memory_buffer_offset;		//0x0018
	long memory_buffer_size;		//0x001C

	//sizeof 1 * 256
	c_static_string<256> source_file;	//0x0020
	//sizeof 1 * 32
	c_static_string<32> build;			//0x0120

	//sizeof 2
	c_enum<e_scenario_type, short> scenario_type;	//0x0140
	//sizeof 2
	c_enum<e_scenario_load_type, short> load_type;	//0x0142


	//sizeof 1
	char unknown1;				//0x0144
	//sizeof 1
	bool tracked_build;			//0x0145
	char unknown2;				//0x0146
	char unknown3;				//0x0147

	long unknown4;				//0x0148
	long unknown5;				//0x014C
	long unknown6;				//0x0150
	long unknown7;				//0x0154
	long unknown8;				//0x0158

	long string_id_count;			//0x015C
	long string_ids_buffer_size;	//0x0160
	long string_id_indices_offset;	//0x0164
	long string_ids_buffer_offset;	//0x0168

	long unknown9;					//0x016C

	ulonglong timestamp;			//0x0170
	ulonglong mainmenu_timestamp;	//0x0178
	ulonglong shared_timestamp;		//0x0180
	ulonglong campaign_timestamp;	//0x0188
	ulonglong multiplayer_timestamp;	//0x0190

	//sizeof 1 * 32
	c_static_string<32> name;	//0x0198

	long unknown15;				//0x01B8  one bee eight

	//sizeof 1 * 256
	c_static_string<256> scenario_path;		//0x01BC

	long minor_version;			//0x02BC

	long tag_name_count;		//0x02C0
	long tag_names_buffer_offset;	//0x02C4
	long tag_names_buffer_size;		//0x02C8
	long tag_name_indices_offset;	//0x02CC

	ulong checksum;				//0x02D0

	long unknown17;				//0x02D4
	long unknown18;				//0x02D8
	long unknown19;				//0x02DC
	long unknown20;				//0x02E0
	long unknown21;				//0x02E4
	long unknown22;				//0x02E8
	long unknown23;				//0x02EC
	long unknown24;				//0x02F0
	long unknown25;				//0x02F4

	ulonglong virtual_base_address;		//0x02F8

	ulong xdk_version;					//0x0300
	long unknown26;				//0x0304

	//sizeof 16
	c_basic_buffer<void> tag_post_link_buffer;						//0x0308		think this is right, but seems weird in the hex
	c_basic_buffer<void> tag_language_dependent_read_only_buffer;	//0x0318		
	c_basic_buffer<void> tag_language_dependent_read_write_buffer;	//0x0328		
	
	c_basic_buffer<void> tag_language_neutral_read_write_buffer;	//0x0338		
	c_basic_buffer<void> tag_language_neutral_write_combined_buffer;//0x0348		
	c_basic_buffer<void> tag_language_neutral_read_only_buffer;		//0x0358		

	ulonglong unknown29;											//0x0368		
	ulonglong unknown30;											//0x0370

	//sizeof 4 * 5
	long sha1_a[5];			//0x0378	
	long sha1_b[5];			//0x038C
	long sha1_c[5];			//0x03A0
	
	//sizeof 4 * 64
	long rsa[64];			//0x03B4

	//sizeof 16
	c_static_array<long,
		k_number_of_cache_file_sections> section_offsets;	//0x04B4

	//sizeof 32
	c_static_array<s_cache_file_section_file_bounds,
		k_number_of_cache_file_sections> section_bounds;	//0x04C4

	long guid[4];				//0x04E4	

	//sizeof 39688 or 0x9B08
	long unknown34[0x26C2];		//0x04F4	
						
	tag footer_signature;		//0x9FFC	
};
static_assert(sizeof(s_cache_file_header) == 0xA000);

struct s_cache_file_loaded_state
{
	s_cache_file_header header;
	ulonglong tags_address_mask;
	c_static_array<c_basic_buffer<void>,
		k_number_of_cache_file_sections> sections;
};

/* ---------- prototypes/CACHE_FILES.cpp */

bool cache_file_allocate_and_load(
	char const *filename,
	s_cache_file_loaded_state *loaded_state,
	c_allocation_interface *allocation);

void cache_file_unload_and_deallocate(
	s_cache_file_loaded_state *loaded_state,
	c_allocation_interface *allocation);

/* ---------- classes */

class c_cache_file_reach : public c_cache_file
{
private:
	s_cache_file_header m_header;
	ulonglong m_address_mask;
	c_basic_buffer<uchar> m_debug_section_buffer;
	c_basic_buffer<uchar> m_tags_section_buffer;

public:
	c_cache_file_reach(char const *filename);
	~c_cache_file_reach();

	s_cache_file_header *get_header();
	s_cache_file_tags_header *get_tags_header();

	char const *get_string(string_id id);

	char const *get_tag_name(long index);
	
	long find_tag_group(tag group_tag);
	s_cache_file_tag_group *get_tag_group(long index);

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
		struct s_cache_file_resource_shared_file *shared_file,
		struct s_cache_file_resource_page *page);

	template <typename t_type>
	t_type *get_debug_section_pointer(long offset)
	{
		if (offset == 0)
			return nullptr;

		auto actual_offset = offset - m_header.section_bounds[_cache_file_section_debug].offset;

		return reinterpret_cast<t_type *>(m_debug_section_buffer + actual_offset);
	}

	template <typename t_type>
	t_type *get_tags_section_pointer(ulonglong address)
	{
		if (address == 0)
			return nullptr;

		auto actual_address = address + m_address_mask;

		return (t_type *)actual_address;
	}

	ulonglong get_page_offset(ulong address);
	ulong make_page_offset(ulonglong address);

	template <typename t_type>
	t_type *get_tags_section_pointer_from_page_offset(ulong page_offset)
	{
		if (page_offset == 0)
			return nullptr;

		return (t_type *)(m_tags_section_buffer + get_page_offset(page_offset));
	}

	template <typename t_tag_definition>
	t_tag_definition *get_tag_definition(long index)
	{
		auto instance = get_tag_instance(index);

		if (!instance || instance->address == 0)
			return nullptr;
		
		return get_tags_section_pointer_from_page_offset<t_tag_definition>(instance->address);
	}
};
