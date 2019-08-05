#pragma once

#include <cseries/cseries.h>

template <tag const k_group_tag = NONE>
class c_tag_iterator : s_tag_iterator
{
public:
	inline c_tag_iterator()
	{
		tag_iterator_initialize(this, k_group_tag);
	}

	inline long next()
	{
		return tag_iterator_next(this);
	}
};
