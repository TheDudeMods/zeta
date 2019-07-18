#pragma once

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <cseries/enum.inl>
#include <cseries/flags.inl>
#include <cseries/static_array.inl>
#include <cseries/static_string.inl>

/* ---------- macros */

#define FLAG(BIT) \
	(1 << (BIT))

#define TEST_FLAG(FLAGS, BIT) \
	((FLAGS) & FLAG(BIT))

#define SET_FLAG(FLAGS, BIT, VALUE) \
	((FLAGS) = ((VALUE) ? ((FLAGS) | FLAG(BIT)) : ((FLAGS) & ~FLAG(BIT))))

#define STRING_ID_INDEX(id) ((id) & ((1 << 17) - 1))
#define STRING_ID_SET(id) (((id) >> 17) & ((1 << 8) - 1))
#define STRING_ID_LENGTH(id) (((id) >> (17 + 8)) & ((1 << 7) - 1))

/* ---------- constants */

enum
{
	NONE = -1,

	k_maximum_short_string_length = 32,
	k_maximum_short_string_ascii_length = k_maximum_short_string_length / sizeof(char),
	k_maximum_short_string_unicode_length = k_maximum_short_string_length / sizeof(wchar_t),

	k_maximum_long_string_length = 256,
	k_maximum_long_string_ascii_length = k_maximum_long_string_length / sizeof(char),
	k_maximum_long_string_unicode_length = k_maximum_long_string_length / sizeof(wchar_t),
};

enum : char
{
	k_char_maximum = (char)0x7F,
	k_char_minimum = (char)0x80,
	k_bits_per_char = 8
};

enum : unsigned char
{
	k_byte_maximum = (unsigned char)0xFF,
	k_bits_per_byte = 8
};

enum : short
{
	k_short_maximum = (short)0x7FFF,
	k_short_minimum = (short)0x8000,
	k_bits_per_short = 16
};

enum : unsigned short
{
	k_word_maximum = (unsigned short)0xFFFF,
	k_bits_per_word = 16
};

enum : long
{
	k_long_maximum = (long)0x7FFFFFFF,
	k_long_minimum = (long)0x80000000,
	k_bits_per_long = 32
};

enum : unsigned long
{
	k_dword_maximum = (unsigned long)0xFFFFFFFF,
	k_bits_per_dword = 32
};

enum : long long
{
	k_long_long_maximum = (long long)0x7FFFFFFFFFFFFFFF,
	k_long_long_minimum = (long long)0x8000000000000000,
	k_bits_per_long_long = 64
};

enum : unsigned long long
{
	k_qword_maximum = (unsigned long long)0xFFFFFFFFFFFFFFFF,
	k_bits_per_qword = 64
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

typedef u_static_string<k_maximum_short_string_length> short_string;
static_assert(sizeof(short_string) == k_maximum_short_string_length);

typedef u_static_string<k_maximum_long_string_length> long_string;
static_assert(sizeof(long_string) == k_maximum_long_string_length);

typedef unsigned long string_id;
static_assert(sizeof(string_id) == 0x4);

/* ---------- prototypes/CSERIES.CPP */

char *tag_to_string(tag value, char *string);
tag string_to_tag(const char *string);
