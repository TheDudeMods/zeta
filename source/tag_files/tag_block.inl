#pragma once

template <typename t_element>
class c_tag_block : public s_tag_block
{
public:
	bool try_get_element(int index, t_element **out_element)
	{
		if (index < 0 || index >= count || !out_element)
			return false;
		*out_element = &g_cache_file->get_page_data<t_element>(address)[index];
		return true;
	}

	t_element *get_element(int index)
	{
		t_element *result = nullptr;
		if (try_get_element(index, &result))
			return result;
		return nullptr;
	}

	t_element &operator[](int index)
	{
		return *get_element(index);
	}

	t_element *begin()
	{
		return g_cache_file->get_page_data<t_element>(address);
	}

	t_element *end()
	{
		*out_element = &g_cache_file->get_page_data<t_element>(address)[count];
	}

	t_element *operator->()
	{
		return get_element(0);
	}
};
static_assert(sizeof(c_tag_block<long>) == sizeof(s_tag_block));
