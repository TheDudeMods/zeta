/*
TAG_GROUPS.H
*/

#pragma once

#include <cseries/cseries.h>

/* ---------- structures */

struct s_tag_group
{
	tag tags[3];
	string_id name;
};
static_assert(sizeof(s_tag_group) == 0x10);

struct s_tag_reference
{
	tag group_tag;
	long : 32;
	long : 32;
	long index;
};
static_assert(sizeof(s_tag_reference) == 0x10);

struct s_tag_block
{
	long count;
	s_ptr32<void> address;
	long : 32;
};
static_assert(sizeof(s_tag_block) == 0xC);

struct s_tag_data
{
	long size;
	long : 32;
	long : 32;
	s_ptr32<void> address;
	long : 32;
};
static_assert(sizeof(s_tag_data) == 0x14);

/* ---------- prototypes/TAG_GROUPS.CPP */
