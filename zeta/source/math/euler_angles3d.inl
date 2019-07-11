#pragma once

template <typename t_element>
struct s_euler_angles3d
{
	t_element yaw;
	t_element pitch;
	t_element roll;
};
static_assert(sizeof(s_euler_angles3d<long>) == 0xC);
