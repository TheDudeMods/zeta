#pragma once

#include <math/point3d.inl>
#include <math/vector3d.inl>

template <typename t_element>
struct s_matrix3x3
{
	s_vector3d<t_element> forward;
	s_vector3d<t_element> left;
	s_vector3d<t_element> up;
};
static_assert(sizeof(s_matrix3x3<long>) == 0x24);
