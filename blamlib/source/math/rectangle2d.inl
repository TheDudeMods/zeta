#pragma once

template <typename t_element>
struct s_rectangle2d
{
	t_element top;
	t_element left;
	t_element bottom;
	t_element right;
};
static_assert(sizeof(s_rectangle2d<long>) == 0x10);
