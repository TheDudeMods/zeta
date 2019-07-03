/*
TAG_GROUPS.H
*/

#pragma once

#include <cseries/cseries.h>
#include <tag_files/tag_groups.h>

/* ---------- structures */

struct s_tag_group_reach
{
	tag tags[3];
	string_id name;
};
static_assert(sizeof(s_tag_group_reach) == 0x10);

struct s_tag_block_reach
{
	long count;
	s_ptr32<void> address;
	long : 32;
};
static_assert(sizeof(s_tag_block_reach) == 0xC);

struct s_tag_data_reach
{
	long size;
	long : 32;
	long : 32;
	s_ptr32<void> address;
	long : 32;
};
static_assert(sizeof(s_tag_data_reach) == 0x14);

/* ---------- classes */

class c_tag_group_reach : public c_tag_group
{
public:
};

class c_tag_block_reach : public c_tag_block
{
public:
};

class c_tag_data_reach : public c_tag_data
{
public:
};
