/*
TAG_GROUPS_V1.CPP
*/

#include <tag_files/tag_groups_v1.h>

/* ---------- code */

c_tag_group_v1::c_tag_group_v1() :
	c_tag_group_v1(nullptr)
{
}

c_tag_group_v1::c_tag_group_v1(s_tag_group_v1 *group) :
	m_group(group)
{
}

c_tag_group_v1::c_tag_group_v1(c_tag_group_v1 const &group) :
	c_tag_group_v1(group.m_group)
{
}

tag c_tag_group_v1::get_tag() const
{
	return ((s_tag_group_v1 *)m_group)->tags[0];
}

void c_tag_group_v1::set_tag(tag value)
{
	((s_tag_group_v1 *)m_group)->tags[0] = value;
}

tag c_tag_group_v1::get_parent_tag() const
{
	return ((s_tag_group_v1 *)m_group)->tags[1];
}

void c_tag_group_v1::set_parent_tag(tag value)
{
	((s_tag_group_v1 *)m_group)->tags[1] = value;
}

tag c_tag_group_v1::get_grandparent_tag() const
{
	return ((s_tag_group_v1 *)m_group)->tags[2];
}

void c_tag_group_v1::set_grandparent_tag(tag value)
{
	((s_tag_group_v1 *)m_group)->tags[2] = value;
}
