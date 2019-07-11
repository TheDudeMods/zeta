#pragma once

template <typename t_element>
struct s_ahsv_color
{
	t_element alpha;
	t_element hue;
	t_element saturation;
	t_element value;
};
static_assert(sizeof(s_ahsv_color<long>) == 0x10);
