#pragma once

template <typename t_element>
struct s_plane3d
{
	t_element i;
	t_element j;
	t_element k;
	t_element d;
};
static_assert(sizeof(s_plane3d<long>) == 0x10);
