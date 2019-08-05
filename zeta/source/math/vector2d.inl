#pragma once

template <typename t_element>
struct s_vector2d
{
	t_element i;
	t_element j;
};
static_assert(sizeof(s_vector2d<long>) == 0x8);
