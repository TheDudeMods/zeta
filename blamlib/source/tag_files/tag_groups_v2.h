/*
TAG_GROUPS_V2.H
*/

#pragma once

#include <cseries/cseries.h>
#include <tag_files/tag_groups.h>

/* ---------- constants */

enum e_tag_data_v2_flags
{
	k_number_of_tag_data_v2_flags
};

/* ---------- structures */

struct s_tag_group_v2
{
	tag tags[3];
	string_id name;
};
static_assert(sizeof(s_tag_group_v2) == 0x10);

struct s_tag_block_v2
{
	long count;
	dword address;
	dword definition;
};
static_assert(sizeof(s_tag_block_v2) == 0xC);

struct s_tag_data_v2
{
	long size;
	c_flags<e_tag_data_v2_flags, long> flags;
	long file_offset;
	dword address;
	dword definition;
};
static_assert(sizeof(s_tag_data_v2) == 0x14);

struct s_tag_reference_v2
{
	tag group_tag;
	long name_length;
	dword name;
	long index;
};
static_assert(sizeof(s_tag_reference_v2) == 0x10);

/* ---------- classes */

class c_tag_group_v2 : public c_tag_group
{
protected:
	s_tag_group_v2 *m_group;

public:
	c_tag_group_v2(s_tag_group_v2 *group);

	tag get_tag() const override;
	void set_tag(tag value) override;

	tag get_parent_tag() const override;
	void set_parent_tag(tag value) override;

	tag get_grandparent_tag() const override;
	void set_grandparent_tag(tag value) override;

	string_id get_name() const override;
	void set_name(string_id value) override;
};

class c_tag_block_v2 : public c_tag_block
{
public:
	// TODO...
};

class c_tag_data_v2 : public c_tag_data
{
public:
	// TODO...
};

class c_tag_reference_v2 : public c_tag_reference
{
public:
	// TODO...
};
