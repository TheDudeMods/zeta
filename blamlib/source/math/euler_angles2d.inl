#pragma once

template <typename t_element>
struct s_euler_angles2d
{
	t_element yaw;
	t_element pitch;
};
static_assert(sizeof(s_euler_angles2d<long>) == 0x8);
