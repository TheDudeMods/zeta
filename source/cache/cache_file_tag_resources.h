#pragma once

#include <cseries/cseries.h>
#include <tag_files/tag_groups.h>

/* ---------- structures */

struct s_resource_compression_codec
{
	long guid[4];
};
static_assert(sizeof(s_resource_compression_codec) == 0x10);

struct s_external_cache_file_reference
{
	short_string path;
	long unknown[58];
};
static_assert(sizeof(s_external_cache_file_reference) == 0x108);

struct s_resource_layout_table
{
	c_tag_block<s_resource_compression_codec> compression_codecs;
	c_tag_block<s_external_cache_file_reference> external_cache_file_references;

};
