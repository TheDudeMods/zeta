#pragma once

#include <cseries/cseries.h>
#include <tag_files/string_ids.h>
#include <tag_files/tag_definitions.h>

/* ---------- types */

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
	ulong address;
	ulong definition_address;
};
static_assert(sizeof(s_tag_block) == 0xC);

struct s_tag_data
{
	long size;
	long stream_flags;
	long stream_offset;
	ulong address;
	ulong definition_address;
};
static_assert(sizeof(s_tag_data) == 0x14);

struct s_tag_function
{
	s_tag_data data;
};
static_assert(sizeof(s_tag_function) == 0x14);

/* ---------- inline headers */

#include <tag_files/tag_block.inl>
#include <tag_files/tag_block_flags.inl>
#include <tag_files/tag_block_index.inl>
