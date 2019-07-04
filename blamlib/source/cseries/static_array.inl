/*
STATIC_ARRAY.INL
*/

#pragma once

template <typename t_element, unsigned long const k_length>
struct s_static_array
{
	t_element elements[k_length];
};
