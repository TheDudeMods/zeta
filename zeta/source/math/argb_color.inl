#pragma once

template <typename t_element>
struct s_argb_color
{
	t_element alpha;
	t_element red;
	t_element green;
	t_element blue;
};
static_assert(sizeof(s_argb_color<long>) == 0x10);
