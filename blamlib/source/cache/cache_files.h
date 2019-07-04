/*
CACHE_FILES.H
*/

#pragma once

#include <cseries/cseries.h>

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

/* ---------- structures */

struct s_cache_file_header {};
static_assert(sizeof(s_cache_file_header) == 0x1);

struct s_cache_tag_index {};
static_assert(sizeof(s_cache_tag_index) == 0x1);

struct s_cache_tag_instance {};
static_assert(sizeof(s_cache_tag_instance) == 0x1);

/* ---------- classes */

class BLAMAPI c_cache_file_header
{
protected:
	s_cache_file_header *m_header;

public:
	c_cache_file_header();
	c_cache_file_header(s_cache_file_header *const &header);
	c_cache_file_header(c_cache_file_header const &header);

	virtual long get_file_version() const = 0;
	virtual void set_file_version(long version) = 0;

	virtual long get_file_length() const = 0;
	virtual void set_file_length(long length) = 0;

	virtual long get_file_compressed_length() const = 0;
	virtual void set_file_compressed_length(long length) const = 0;

	virtual s_ptr64<s_cache_tag_index> get_tag_index_address() const = 0;
	virtual void set_tag_index_address(s_ptr64<s_cache_tag_index> address) = 0;

	virtual long get_memory_buffer_offset() const = 0;
	virtual void set_memory_buffer_offset(long offset) = 0;

	virtual long get_memory_buffer_size() const = 0;
	virtual void set_memory_buffer_size(long size) = 0;

	virtual char const *get_source_file() const = 0;
	virtual void set_source_file(char const *file) = 0;

	// TODO...
};

class BLAMAPI c_cache_tag_index
{
protected:
	s_cache_tag_index *m_index;

public:
	c_cache_tag_index();
	c_cache_tag_index(s_cache_tag_index *const &index);
	c_cache_tag_index(c_cache_tag_index const &index);

	// TODO...
};

class BLAMAPI c_cache_tag_instance
{
protected:
	s_cache_tag_instance *m_instance;

public:
	c_cache_tag_instance();
	c_cache_tag_instance(s_cache_tag_instance *const &instance);
	c_cache_tag_instance(c_cache_tag_instance const &instance);

	// TODO...
};

class BLAMAPI c_cache_file
{
protected:
	char *m_buffer;

public:
	c_cache_file();
	c_cache_file(char const *path);
	c_cache_file(c_cache_file const &file);

	virtual c_cache_file_header &get_header() const = 0;
	virtual c_cache_tag_index &get_tag_index() const = 0;
	virtual c_cache_tag_instance &get_tag_instance(long index) const = 0;
};
