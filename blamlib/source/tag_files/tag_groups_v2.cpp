/*
TAG_GROUPS_V2.CPP
*/

#include <tag_files/tag_groups_v2.h>

/* ---------- code */

c_tag_group_v2::c_tag_group_v2(s_tag_group_v2 *group) :
	m_group(group)
{
}

tag c_tag_group_v2::get_tag() const
{
	return m_group->tags[0];
}

void c_tag_group_v2::set_tag(tag value)
{
	m_group->tags[0] = value;
}

tag c_tag_group_v2::get_parent_tag() const
{
	return m_group->tags[1];
}

void c_tag_group_v2::set_parent_tag(tag value)
{
	m_group->tags[1] = value;
}

tag c_tag_group_v2::get_grandparent_tag() const
{
	return m_group->tags[2];
}

void c_tag_group_v2::set_grandparent_tag(tag value)
{
	m_group->tags[2] = value;
}

string_id c_tag_group_v2::get_name() const
{
	return m_group->name;
}

void c_tag_group_v2::set_name(string_id value)
{
	m_group->name = value;
}
