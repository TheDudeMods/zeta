#pragma once

template <typename t_element>
struct s_quaternion
{
	t_element i;
	t_element j;
	t_element k;
	t_element w;
};
static_assert(sizeof(s_quaternion<long>) == 0x10);
