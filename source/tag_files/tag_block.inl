#pragma once

template <typename t_element>
class c_tag_block : public s_tag_block
{
public:
	inline bool try_get_element(int index, t_element **out_element)
	{
		if (index < 0 || index >= count || !out_element)
			return false;
		*out_element = &((t_element *)address)[index];
		return true;
	}

	inline t_element *get_element(int index)
	{
		t_element *result = nullptr;
		if (try_get_element(index, &result))
			return result;
		return nullptr;
	}

	inline t_element &operator[](int index)
	{
		return *get_element(index);
	}

	inline t_element *begin()
	{
		return &((t_element *)address)[0];
	}

	inline t_element *end()
	{
		return &((t_element *)address)[count];
	}

	inline t_element *operator->()
	{
		return get_element(0);
	}
};
static_assert(sizeof(c_tag_block<long>) == sizeof(s_tag_block));
