#pragma once

template <typename t_element>
struct s_hsv_color
{
	t_element hue;
	t_element saturation;
	t_element value;
};
static_assert(sizeof(s_hsv_color<long>) == 0xC);
