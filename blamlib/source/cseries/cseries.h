#pragma once

#include <cctype>
#include <climits>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cuchar>

#include <cseries/cseries_asserts.h>
#include <cseries/cseries_memory.h>
#include <cseries/cseries_string.h>

/* ---------- constants */

enum
{
	NONE = -1,

	k_maximum_temporary_string_length = 1024,
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

/* ---------- macros */

#define FLAG(BIT) (1 << (BIT))
#define TEST_FLAG(FLAGS, BIT) ((FLAGS) & FLAG(BIT))
#define SWAP_FLAG(FLAGS, BIT) ((FLAGS) ^= FLAG(BIT))
#define SET_FLAG(FLAGS, BIT, VALUE) ((VALUE) ? ((FLAGS) |= FLAG(BIT)) : ((FLAGS) &= ~FLAG(BIT)))
#define FLAG_RANGE(FIRST_BIT, LAST_BIT) ((FLAG((LAST_BIT) + 1 - (FIRST_BIT)) - 1) << (FIRST_BIT))

#undef HIWORD
#define HIWORD(N) (((N) >> 16) & USHRT_MAX)
#define SET_HIWORD(N, V) ((N) = (((N) & USHRT_MAX) | (((V) & USHRT_MAX) << 16)))

#undef LOWORD
#define LOWORD(N) ((N) & USHRT_MAX)
#define SET_LOWORD(N, V) ((N) = (((N) & (USHRT_MAX << 16)) | ((V) & USHRT_MAX)))

#undef assert
#ifdef _DEBUG
#	define assert(EXPR) \
	(void)((!!(EXPR)) || \
		(display_assert(#EXPR, __FILE__, __LINE__, true), \
		0))
#	define vassert(EXPR, FORMAT, ...) \
	(void)((!!(EXPR)) || \
		(memset(global_temporary_string, 0, k_maximum_temporary_string_length), \
		sprintf_s(global_temporary_string, FORMAT, __VA_ARGS__), \
		display_assert(global_temporary_string, __FILE__, __LINE__, true), \
		0))
#else
#	define assert(EXPR)
#	define vassert(EXPR, FORMAT, ...)
#endif

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

/* ---------- globals */

extern char global_temporary_string[k_maximum_temporary_string_length];
