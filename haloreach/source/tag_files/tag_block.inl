#pragma once

#include <cache/cache_files.h>

template <typename t_element>
class c_tag_block : public s_tag_block
{
public:
	inline bool valid_index(long index) const
	{
		return index >= 0 && index < count;
	}

	bool try_get_element(c_cache_file_reach *file, int index, t_element **out_element)
	{
		if (!valid_index(index) || !out_element)
			return false;

		*out_element = &file->get_tags_section_pointer_from_page_offset<t_element>(address)[index];

		return true;
	}

	t_element *get_element(c_cache_file_reach *file, int index)
	{
		t_element *result = nullptr;

		if (try_get_element(file, index, &result))
			return result;

		return nullptr;
	}
};
static_assert(sizeof(c_tag_block<long>) == sizeof(s_tag_block));
