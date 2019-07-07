/*
STATIC_STRING.INL
*/

#pragma once

template <unsigned long const k_maximum_length>
union u_static_string
{
	char ascii[k_maximum_length / sizeof(char)];
	wchar_t unicode[k_maximum_length / sizeof(wchar_t)];
};
