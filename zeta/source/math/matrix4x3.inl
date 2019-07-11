#pragma once

#include <math/point3d.inl>
#include <math/vector3d.inl>

template <typename t_element>
struct s_matrix4x3
{
	t_element scale;
	s_vector3d<t_element> forward;
	s_vector3d<t_element> left;
	s_vector3d<t_element> up;
	s_point3d<t_element> position;
};
static_assert(sizeof(s_matrix4x3<long>) == 0x34);
