/*
TAG_GROUPS.CPP
*/

#include <tag_files/tag_groups.h>

/* ---------- code */

c_tag_group::c_tag_group() :
	c_tag_group(nullptr)
{
}

c_tag_group::c_tag_group(s_tag_group *const &group) :
	m_group(group)
{
}

c_tag_group::c_tag_group(c_tag_group const &group) :
	c_tag_group(group.m_group)
{
}

c_tag_block::c_tag_block() :
	c_tag_block(nullptr)
{
}

c_tag_block::c_tag_block(s_tag_block *const &block) :
	m_block(block)
{
}

c_tag_block::c_tag_block(c_tag_block const &block) :
	c_tag_block(block.m_block)
{
}

c_tag_data::c_tag_data() :
	c_tag_data(nullptr)
{
}

c_tag_data::c_tag_data(s_tag_data *const &data) :
	m_data(data)
{
}

c_tag_data::c_tag_data(c_tag_data const &data) :
	c_tag_data(data.m_data)
{
}

c_tag_reference::c_tag_reference() :
	c_tag_reference(nullptr)
{
}

c_tag_reference::c_tag_reference(s_tag_reference *const &reference) :
	m_reference(reference)
{
}

c_tag_reference::c_tag_reference(c_tag_reference const &reference) :
	c_tag_reference(reference.m_reference)
{
}
