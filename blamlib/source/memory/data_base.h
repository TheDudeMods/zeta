#pragma once

#include <cseries/cseries.h>

/* ---------- macros */

#define DATUM_INDEX_TO_ABSOLUTE_INDEX(DATUM_INDEX) ((DATUM_INDEX) & 0xFFFF)
#define DATUM_INDEX_TO_IDENTIFIER(DATUM_INDEX) (((DATUM_INDEX) >> 16) & 0xFFFF)

/* ---------- constants */

enum
{
	k_data_signature = 'd@t@',
};

/* ---------- structures */

struct s_datum
{
	word identifier;
};
static_assert(sizeof(s_datum) == 0x2);

struct s_datum_aligned : s_datum
{
	short : 16;
};
static_assert(sizeof(s_datum_aligned) == 0x4);
