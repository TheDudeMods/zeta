/*
TAG_GROUPS.H
*/

#pragma once

#include <cseries/cseries.h>

/* ---------- structures */

struct s_tag_group {};
static_assert(sizeof(s_tag_group) == 0x1);

struct s_tag_block {};
static_assert(sizeof(s_tag_block) == 0x1);

struct s_tag_data {};
static_assert(sizeof(s_tag_data) == 0x1);

struct s_tag_reference {};
static_assert(sizeof(s_tag_reference) == 0x1);

/* ---------- classes */

class BLAMAPI c_tag_group
{
protected:
	s_tag_group *m_group;

public:
	c_tag_group();
	c_tag_group(s_tag_group *const &group);
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
	s_tag_block *m_block;

public:
	c_tag_block();
	c_tag_block(s_tag_block *const &block);
	c_tag_block(c_tag_block const &block);

	virtual long get_count() const = 0;
	virtual void set_count(long count) = 0;

	virtual s_ptr32<void> get_address() const = 0;
	virtual void set_address(s_ptr32<void> const &address) = 0;
};

class BLAMAPI c_tag_data
{
protected:
	s_tag_data *m_data;

public:
	c_tag_data();
	c_tag_data(s_tag_data *const &data);
	c_tag_data(c_tag_data const &data);

	virtual long get_size() const = 0;
	virtual void set_size(long size) = 0;

	virtual s_ptr32<void> get_address() const = 0;
	virtual void set_address(s_ptr32<void> const &address) = 0;
};

class BLAMAPI c_tag_reference
{
protected:
	s_tag_reference *m_reference;

public:
	c_tag_reference();
	c_tag_reference(s_tag_reference *const &reference);
	c_tag_reference(c_tag_reference const &reference);

	virtual tag get_group_tag() const = 0;
	virtual void set_group_tag(tag value) = 0;

	virtual long get_index() const = 0;
	virtual void set_index(long value) = 0;
};
