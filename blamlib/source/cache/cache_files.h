/*
CACHE_FILES_BASE.H
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
	_scenario_type_unused5,
	_scenario_type_unused6,
	k_number_of_scenario_types
};

enum e_scenario_load_type
{
	_scenario_load_none = NONE,
	_scenario_load_mainmenu,
	_scenario_load_shared,
	_scenario_load_shared_campaign,
	k_number_of_scenario_load_types
};

/* ---------- classes */

class BLAMAPI c_cache_file_header
{
protected:
	void *m_address;

public:
	virtual long get_file_version() const = 0;
	virtual void set_file_version(long version) = 0;

	virtual long get_file_length() const = 0;
	virtual void set_file_length(long length) = 0;

	virtual long get_file_compressed_length() const = 0;
	virtual void set_file_compressed_length(long length) const = 0;

	virtual qword get_tag_index_address() const = 0;
	virtual void set_tag_index_address(qword address) = 0;


};

class BLAMAPI c_cache_file_tag_index
{
protected:
	void *m_address;
};

class BLAMAPI c_cache_file
{
protected:
	char *m_buffer;

public:
	virtual c_cache_file_header &get_header() const = 0;
	virtual c_cache_file_tag_index &get_tag_index() const = 0;

};
