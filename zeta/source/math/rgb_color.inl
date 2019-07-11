#pragma once

template <typename t_element>
struct s_rgb_color
{
	t_element red;
	t_element green;
	t_element blue;
};
static_assert(sizeof(s_rgb_color<long>) == 0xC);
