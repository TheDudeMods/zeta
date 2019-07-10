#pragma once

#include <cstring>

template <typename t_element, const long k_length>
struct s_static_array
{
	t_element elements[k_length];

	s_static_array()
	{
		memset(elements, 0, sizeof(t_element) * k_length);
	}

	s_static_array(t_element *elements) :
		s_static_array()
	{
		memcpy(this->elements, elements, sizeof(t_element) * k_length);
	}

	s_static_array(s_static_array<t_element, k_length> const &other) :
		s_static_array(other.elements)
	{
	}

	operator t_element *()
	{
		return elements;
	}
};
