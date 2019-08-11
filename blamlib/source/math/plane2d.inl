#pragma once

template <typename t_element>
struct s_plane2d
{
	t_element i;
	t_element j;
	t_element d;
};
static_assert(sizeof(s_plane2d<long>) == 0xC);
