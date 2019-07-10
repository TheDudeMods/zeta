#pragma once

#include <cstring>

template <const long k_length>
union u_static_string
{
	char ascii[k_length / sizeof(char)];
	wchar_t unicode[k_length / sizeof(wchar_t)];

	u_static_string()
	{
		memset(ascii, 0, k_length / sizeof(char));
	}

	u_static_string(const char *ascii) :
		u_static_string()
	{
		strcpy_s(this->ascii, ascii);
	}

	u_static_string(const wchar_t *unicode) :
		u_static_string()
	{
		wcscpy_s(this->unicode, unicode);
	}

	operator char *()
	{
		return ascii;
	}

	operator wchar_t *()
	{
		return unicode;
	}
};
