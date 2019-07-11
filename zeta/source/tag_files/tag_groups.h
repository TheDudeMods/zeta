#pragma once

#include <cseries/cseries.h>

/* ---------- structures */

struct s_tag_group
{
	tag tags[3];
	string_id name;

	bool is_in_group(tag group_tag) const;
	bool is_in_group(s_tag_group &group) const;
};
static_assert(sizeof(s_tag_group) == 0x10);

struct s_tag_reference
{
	tag group_tag;
	long name_length;
	long name_offset;
	long index;
};
static_assert(sizeof(s_tag_reference) == 0x10);

struct s_tag_block
{
	long count;
	dword address;
	dword definition_address;
};
static_assert(sizeof(s_tag_block) == 0xC);

struct s_tag_data
{
	long size;
	long stream_flags;
	long stream_offset;
	dword address;
	dword definition_address;
};
static_assert(sizeof(s_tag_data) == 0x14);

/* ---------- inline headers */

#include <tag_files/tag_block.inl>
#include <tag_files/tag_block_flags.inl>
#include <tag_files/tag_block_index.inl>
