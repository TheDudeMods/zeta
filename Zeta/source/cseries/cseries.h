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
#include <cseries/static_array.inl>
#include <cseries/static_string.inl>

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
	k_int64_maximum = 9223372036854775807i64,
	k_int64_minimum = (-k_int64_maximum) - 1,
	k_int64_bits = sizeof(long long) * k_bits_per_byte
};

enum : unsigned char
{
	k_byte_maximum = 0xFF,
	k_byte_bits = sizeof(unsigned char) * k_bits_per_byte
};

enum : unsigned short
{
	k_word_maximum = 0xFFFF,
	k_word_bits = sizeof(unsigned short) * k_bits_per_byte
};

enum : unsigned long
{
	k_dword_maximum = 0xFFFFFFFF,
	k_dword_bits = sizeof(unsigned long) * k_bits_per_byte
};

enum : unsigned long long
{
	k_qword_maximum = 0xFFFFFFFFFFFFFFFF,
	k_qword_bits = sizeof(unsigned long long) * k_bits_per_byte
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

typedef u_static_string<k_maximum_short_string_length> short_string;
static_assert(sizeof(short_string) == k_maximum_short_string_length);

typedef u_static_string<k_maximum_long_string_length> long_string;
static_assert(sizeof(long_string) == k_maximum_long_string_length);

/* ---------- prototypes/CSERIES.CPP */

bool cseries_initialize();
void cseries_dispose();

char *tag_to_string(tag value, char *string);
tag string_to_tag(char const *string);
