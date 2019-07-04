/*
TAG_GROUPS.H
*/

#pragma once

#include <haloreach.h>

#include <cseries/cseries.h>
#include <tag_files/tag_groups_v2.h>

/* ---------- classes */

class BLAMAPI c_tag_group_reach : public c_tag_group
{
public:
	virtual tag get_tag() const = 0;
	virtual void set_tag(tag value) = 0;

	virtual tag get_parent_tag() const = 0;
	virtual void set_parent_tag(tag value) = 0;

	virtual tag get_grandparent_tag() const = 0;
	virtual void set_grandparent_tag(tag value) = 0;

	virtual char const *get_name() const = 0;
	virtual void set_name(char const *name) = 0;
};

class BLAMAPI c_tag_block_reach : public c_tag_block
{
public:
};

class BLAMAPI c_tag_data_reach : public c_tag_data
{
public:
};
