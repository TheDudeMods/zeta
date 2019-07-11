#pragma once

template <typename t_element>
struct s_point2d
{
	t_element x;
	t_element y;
};
static_assert(sizeof(s_point2d<long>) == 0x8);
