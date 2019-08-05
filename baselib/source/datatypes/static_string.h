#pragma once

#include <cseries/cseries.h>

/* ---------- constants */

enum
{
	k_maximum_short_string_length = 32,
	k_maximum_short_string_utf8_length = k_maximum_short_string_length / sizeof(char),
	k_maximum_short_string_utf16_length = k_maximum_short_string_length / sizeof(char16_t),
	k_maximum_short_string_utf32_length = k_maximum_short_string_length / sizeof(char32_t),

	k_maximum_long_string_length = 256,
	k_maximum_long_string_utf8_length = k_maximum_long_string_length / sizeof(char),
	k_maximum_long_string_utf16_length = k_maximum_long_string_length / sizeof(char16_t),
	k_maximum_long_string_utf32_length = k_maximum_long_string_length / sizeof(char32_t),
};

/* ---------- types */

template <const long k_length>
struct s_static_string
{
	union
	{
		char ascii[k_length / sizeof(char)];
		wchar_t unicode[k_length / sizeof(wchar_t)];
	};

	s_static_string()
	{
		memset(ascii, 0, k_length / sizeof(char));
	}

	s_static_string(const char *ascii) :
		s_static_string()
	{
		strcpy_s(this->ascii, ascii);
	}

	s_static_string(const wchar_t *unicode) :
		s_static_string()
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

typedef s_static_string<k_maximum_short_string_length> short_string;
static_assert(sizeof(short_string) == k_maximum_short_string_length);

typedef s_static_string<k_maximum_long_string_length> long_string;
static_assert(sizeof(long_string) == k_maximum_long_string_length);

/* ---------- prototypes/STATIC_STRING.CPP */

char *tag_to_string(tag value, char *string);
tag string_to_tag(const char *string);
