#pragma once

#include <cseries/cseries_asserts.h>
#include <cseries/cseries_memory.h>
#include <cseries/cseries_string.h>
#include <cseries/cseries_traits.h>

/* ---------- macros */

#define NUMBEROF(xs) \
	(sizeof((xs)) / sizeof((xs)[0]))

#define FLAG(bit) \
	(1U << (bit))

#define TEST_BIT(flags, bit) \
	((flags) & FLAG(bit))

#define SET_FLAG(flags, bit, value) \
	((flags) = ((value) ? ((flags) | FLAG(bit)) : ((flags) & ~FLAG(bit))))

#define VALID_INDEX(index, max_count) \
	(((index) >= 0) && ((index) < (max_count)))

#define BIT_VECTOR_SIZE_IN_LONGS(bit_count) \
	(((bit_count) + 31) >> 5)

#define BIT_VECTOR_SIZE_IN_BYTES(bit_count) \
	(BIT_VECTOR_SIZE_IN_LONGS(bit_count) * sizeof(long))

#define BIT_VECTOR_WORD_INDEX(bit) \
	((bit) >> 5)

#define BIT_VECTOR_WORD(vector, bit) \
	((vector)[BIT_VECTOR_WORD_INDEX(bit)])

#define BIT_VECTOR_TEST_FLAG(vector, bit) \
	TEST_BIT(BIT_VECTOR_WORD(vector, bit), (bit) % (sizeof(long) * k_uint8_bits))

#define BIT_VECTOR_SET_FLAG(vector, bit, value) \
	SET_FLAG(BIT_VECTOR_WORD(vector, bit), ((bit) % (sizeof(long) * k_uint8_bits)), value)

/* ---------- types */

enum e_none_sentinel
{
	NONE = -1
};

typedef unsigned char uchar;
static_assert(sizeof(uchar) == 0x1);

typedef unsigned short ushort;
static_assert(sizeof(ushort) == 0x2);

typedef unsigned long ulong;
static_assert(sizeof(ulong) == 0x4);

typedef unsigned long long ulonglong;
static_assert(sizeof(ulonglong) == 0x8);

typedef unsigned int uint;
static_assert(sizeof(uint) == 0x4);

typedef signed __int8 int8;
static_assert(sizeof(int8) == 0x1);

typedef unsigned __int8 uint8;
static_assert(sizeof(uint8) == 0x1);

typedef signed __int16 int16;
static_assert(sizeof(int16) == 0x2);

typedef unsigned __int16 uint16;
static_assert(sizeof(uint16) == 0x2);

typedef signed __int32 int32;
static_assert(sizeof(int32) == 0x4);

typedef unsigned __int32 uint32;
static_assert(sizeof(uint32) == 0x4);

typedef signed __int64 int64;
static_assert(sizeof(int64) == 0x8);

typedef unsigned __int64 uint64;
static_assert(sizeof(uint64) == 0x8);

/* ---------- constants */

enum : __int8
{
	k_int8_max = 127i8,
	k_int8_min = -k_int8_max - 1i8,
	k_int8_bits = 8i8,
};

enum : unsigned __int8
{
	k_uint8_max = 255Ui8,
	k_uint8_bits = 8Ui8,
};

enum : __int16
{
	k_int16_max = 32767i16,
	k_int16_min = -k_int16_max - 1i16,
	k_int16_bits = 16i16,
};

enum : unsigned __int16
{
	k_uint16_max = 65535Ui16,
	k_uint16_bits = 16Ui16,
};

enum : __int32
{
	k_int32_max = 2147483647i32,
	k_int32_min = -k_int32_max - 1i32,
	k_int32_bits = 32i32,
};

enum : unsigned __int32
{
	k_uint32_max = 4294967295Ui32,
	k_uint32_bits = 32Ui32,
};

enum : __int64
{
	k_int64_max = 9223372036854775807i64,
	k_int64_min = -k_int64_max - 1i64,
	k_int64_bits = 64i64,
};

enum : unsigned __int64
{
	k_uint64_max = 18446744073709551615Ui64,
	k_uint64_bits = 64Ui64,
};
