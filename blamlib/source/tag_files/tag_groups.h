/*
TAG_GROUPS.H
*/

#pragma once

#include <cseries/cseries.h>

/* ---------- classes */

class BLAMAPI c_tag_group
{
protected:
	void *m_group;

public:
	c_tag_group();
	c_tag_group(void *const &group);
	c_tag_group(c_tag_group const &group);

	virtual tag get_tag() const = 0;
	virtual void set_tag(tag value) = 0;

	virtual tag get_parent_tag() const = 0;
	virtual void set_parent_tag(tag value) = 0;

	virtual tag get_grandparent_tag() const = 0;
	virtual void set_grandparent_tag(tag value) = 0;

	virtual char const *get_name() const = 0;
	virtual void set_name(char const *name) = 0;
};

class BLAMAPI c_tag_block
{
protected:
	void *m_block;

public:
	c_tag_block();
	c_tag_block(void *const &block);
	c_tag_block(c_tag_block const &block);

	virtual long get_count() const = 0;
	virtual void set_count(long count) = 0;

	virtual dword get_address() const = 0;
	virtual void set_address(dword const &address) = 0;
};

class BLAMAPI c_tag_data
{
protected:
	void *m_data;

public:
	c_tag_data();
	c_tag_data(void *const &data);
	c_tag_data(c_tag_data const &data);

	virtual long get_size() const = 0;
	virtual void set_size(long size) = 0;

	virtual dword get_address() const = 0;
	virtual void set_address(dword const &address) = 0;
};

class BLAMAPI c_tag_reference
{
protected:
	void *m_reference;

public:
	c_tag_reference();
	c_tag_reference(void *const &reference);
	c_tag_reference(c_tag_reference const &reference);

	virtual tag get_group_tag() const = 0;
	virtual void set_group_tag(tag value) = 0;

	virtual long get_index() const = 0;
	virtual void set_index(long value) = 0;
};
