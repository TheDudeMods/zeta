/*
TAG_GROUPS.H
*/

#pragma once

#include <cseries/cseries.h>

/* ---------- classes */

class c_tag_group
{
public:
	virtual tag get_tag() const = 0;
	virtual void set_tag(tag value) = 0;

	virtual tag get_parent_tag() const = 0;
	virtual void set_parent_tag(tag value) = 0;

	virtual tag get_grandparent_tag() const = 0;
	virtual void set_grandparent_tag(tag value) = 0;

	virtual string_id get_name() const = 0;
	virtual void set_name(string_id value) = 0;
};

class c_tag_block
{
public:
	virtual long get_count() const = 0;
	virtual void set_count(long count) = 0;

	virtual dword get_address() const = 0;
	virtual void set_address(dword const &address) = 0;
};

class c_tag_data
{
public:
	virtual long get_size() const = 0;
	virtual void set_size(long size) = 0;

	virtual dword get_address() const = 0;
	virtual void set_address(dword const &address) = 0;
};

class c_tag_reference
{
public:
	virtual tag get_group_tag() const = 0;
	virtual void set_group_tag(tag value) = 0;

	virtual long get_index() const = 0;
	virtual void set_index(long value) = 0;
};
