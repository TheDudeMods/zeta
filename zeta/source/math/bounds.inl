#pragma once

template <typename t_value>
struct s_bounds
{
	t_value lower;
	t_value upper;
};
static_assert(sizeof(s_bounds<long>) == 0x8);
