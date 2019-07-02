/*
CSERIES.H
*/

#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <cseries/enums.inl>
#include <cseries/flags.inl>

/* ---------- macros */

/* ---------- constants */

enum
{
	NONE = -1,

	k_bits_per_byte = 8,

	k_maximum_short_string_length = 32,
	k_maximum_short_string_ascii_length = k_maximum_short_string_length / sizeof(char),
	k_maximum_short_string_unicode_length = k_maximum_short_string_length / sizeof(wchar_t),

	k_maximum_long_string_length = 256,
	k_maximum_long_string_ascii_length = k_maximum_long_string_length / sizeof(char),
	k_maximum_long_string_unicode_length = k_maximum_long_string_length / sizeof(wchar_t)
};

/* ---------- types */

typedef unsigned char byte;
static_assert(sizeof(byte) == 0x1);

typedef unsigned short word;
static_assert(sizeof(word) == 0x2);

typedef unsigned long dword;
static_assert(sizeof(dword) == 0x4);

typedef unsigned long long qword;
static_assert(sizeof(qword) == 0x8);

typedef unsigned long tag;
static_assert(sizeof(tag) == 0x4);

typedef unsigned long string_id;
static_assert(sizeof(string_id) == 0x4);

union u_short_string
{
	char ascii[k_maximum_short_string_ascii_length];
	wchar_t unicode[k_maximum_short_string_unicode_length];
};
static_assert(sizeof(u_short_string) == k_maximum_short_string_length);

union u_long_string
{
	char ascii[k_maximum_long_string_ascii_length];
	wchar_t unicode[k_maximum_long_string_unicode_length];
};
static_assert(sizeof(u_long_string) == k_maximum_long_string_length);

template <typename t_value>
struct s_ptr32
{
	dword address;

	operator t_value *() { return (t_value *)address; }
};
static_assert(sizeof(s_ptr32<void>) == sizeof(dword));

template <typename t_value>
struct s_ptr64
{
	qword address;

	operator t_value *() { return (t_value *)address; }
};
static_assert(sizeof(s_ptr64<void>) == sizeof(qword));

/* ---------- limits */

enum : char
{
	k_char_maximum = 127,
	k_char_minimum = (-k_char_maximum) - 1,
	k_char_bits = sizeof(char) * k_bits_per_byte
};

enum : short
{
	k_short_maximum = 32767,
	k_short_minimum = (-k_short_maximum) - 1,
	k_short_bits = sizeof(short) * k_bits_per_byte
};

enum : long
{
	k_long_maximum = 2147483647,
	k_long_minimum = (-k_long_maximum) - 1,
	k_long_bits = sizeof(long) * k_bits_per_byte
};

enum : long long
{
	k_longlong_maximum = 9223372036854775807i64,
	k_longlong_minimum = (-k_longlong_maximum) - 1,
	k_longlong_bits = sizeof(long long) * k_bits_per_byte
};

enum : byte
{
	k_uchar_maximum = 0xFF,
	k_uchar_bits = sizeof(byte) * k_bits_per_byte
};

enum : word
{
	k_ushort_maximum = 0xFFFF,
	k_ushort_bits = sizeof(word) * k_bits_per_byte
};

enum : dword
{
	k_ulong_maximum = 0xFFFFFFFF,
	k_ulong_bits = sizeof(dword) * k_bits_per_byte
};

enum : qword
{
	k_ulonglong_maximum = 0xFFFFFFFFFFFFFFFF,
	k_ulonglong_bits = sizeof(qword) * k_bits_per_byte
};

/* ---------- prototypes/CSERIES.CPP */

bool cseries_initialize();
void cseries_dispose();

char *tag_to_string(tag value, char *string);
tag string_to_tag(char const *string);
