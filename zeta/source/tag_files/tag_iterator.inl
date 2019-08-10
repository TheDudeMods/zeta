#pragma once

#include <cseries/cseries.h>

class c_cache_file;

template <tag const k_group_tag = NONE>
class c_tag_iterator : s_tag_iterator
{
private:
	c_cache_file *m_file;

public:
	inline c_tag_iterator(c_cache_file *file) :
		m_file(file)
	{
		tag_iterator_initialize(this, k_group_tag);
	}

	inline long next()
	{
		return tag_iterator_next(m_file, this);
	}
};
