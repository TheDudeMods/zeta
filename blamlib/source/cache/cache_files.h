/*
CACHE_FILES.H
*/

#pragma once

#include <cseries/cseries.h>
#include <tag_files/tag_groups.h>

/* ---------- constants */

enum
{
	k_cache_header_signature = 'head',
	k_cache_footer_signature = 'foot',
	k_cache_tags_signature = 'tags',

	k_maximum_tag_address = 0xC0000000
};

enum e_scenario_type
{
	_scenario_type_none = NONE,
	_scenario_type_campaign,
	_scenario_type_multiplayer,
	_scenario_type_mainmenu,
	_scenario_type_shared,
	_scenario_type_shared_campaign,
	_scenario_type_shared_multiplayer,
	k_number_of_scenario_types
};

enum e_scenario_load_type
{
	_scenario_load_none = NONE,
	_scenario_load_mainmenu,
	_scenario_load_shared,
	_scenario_load_shared_campaign,
	_scenario_load_shared_multiplayer,
	k_number_of_scenario_load_types
};

/* ---------- classes */

class c_cache_file_header
{
public:
	virtual long get_file_version() const = 0;
	virtual void set_file_version(long version) = 0;

	virtual long get_file_length() const = 0;
	virtual void set_file_length(long length) = 0;

	virtual qword get_tags_header_address() const = 0;
	virtual void set_tags_header_address(qword address) = 0;

	virtual long get_memory_buffer_offset() const = 0;
	virtual void set_memory_buffer_offset(long offset) = 0;

	virtual long get_memory_buffer_size() const = 0;
	virtual void set_memory_buffer_size(long size) = 0;

	virtual char const *get_build_name() const = 0;
	virtual void set_build_name(char const *name) = 0;

	virtual e_scenario_type get_scenario_type() const = 0;
	virtual void set_scenario_type(e_scenario_type const &type) = 0;

	virtual e_scenario_load_type get_scenario_load_type() const = 0;
	virtual void set_scenario_load_type(e_scenario_load_type const &type) = 0;

	virtual char const *get_name() const = 0;
	virtual void set_name(char const *name) = 0;
};

class c_cache_file_tag_instance
{
public:
	virtual c_tag_group *get_group() = 0;

	virtual dword get_offset() = 0;

	virtual char const *get_name() = 0;

	virtual long get_index() = 0;
};

class c_cache_file_tags_header
{
public:
	virtual c_tag_group *get_tag_group(long index) = 0;

	virtual c_cache_file_tag_instance *get_tag_instance(long index) = 0;
};

class c_cache_file
{
protected:
	char *m_buffer;

public:
	c_cache_file();
	c_cache_file(char const *path);
	c_cache_file(c_cache_file const &file);
	~c_cache_file();

	virtual dword get_address_mask() const = 0;
	virtual qword get_base_address() const = 0;

	virtual c_cache_file_header &get_header() = 0;
	virtual c_cache_file_tags_header &get_tags_header() = 0;
};
