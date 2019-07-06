/*
TAG_GROUP_V1.INL
*/

#pragma once

#include <cseries/cseries.h>
#include <tag_files/tag_groups.h>

/* ---------- structures */

struct s_tag_group_v1
{
	tag tags[3];
};
static_assert(sizeof(s_tag_group_v1) == 0xC);

struct s_tag_block_v1
{
	long count;
	dword address;
};
static_assert(sizeof(s_tag_block_v1) == 0x8);

struct s_tag_data_v1
{
	long size;
	dword address;
};
static_assert(sizeof(s_tag_data_v1) == 0x8);

struct s_tag_reference_v1
{
	tag group_tag;
	long index;
};
static_assert(sizeof(s_tag_reference_v1) == 0x8);

/* ---------- classes */

class BLAMAPI c_tag_group_v1 : public c_tag_group
{
public:
	c_tag_group_v1();
	c_tag_group_v1(s_tag_group_v1 *const &group);
	c_tag_group_v1(c_tag_group_v1 const &group);

	tag get_tag() const override;
	void set_tag(tag value) override;

	tag get_parent_tag() const override;
	void set_parent_tag(tag value) override;

	tag get_grandparent_tag() const override;
	void set_grandparent_tag(tag value) override;

	virtual char const *get_name() const = 0;
	virtual void set_name(char const *name) = 0;
};

class c_tag_block_v1 : public c_tag_block
{
public:
	// TODO...
};

class c_tag_data_v1 : public c_tag_data
{
public:
	// TODO...
};

class c_tag_reference_v1 : public c_tag_reference
{
public:
	// TODO...
};
