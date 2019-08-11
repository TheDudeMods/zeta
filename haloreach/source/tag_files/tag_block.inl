#pragma once

#include <cache/cache_files.h>

template <typename t_element>
class c_tag_block : public s_tag_block
{
public:
	bool try_get_element(c_cache_file_reach *file, int index, t_element **out_element)
	{
		if (index < 0 || index >= count || !out_element)
			return false;
		*out_element = &file->get_page_data<t_element>(address)[index];
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
