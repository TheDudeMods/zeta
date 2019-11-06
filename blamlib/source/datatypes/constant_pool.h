#pragma once

#include <cseries/cseries.h>
#include <datatypes/data_array.h>
#include <datatypes/memory_pool.h>
#include <datatypes/static_string.h>

/* ---------- types */

struct s_constant_pool_element : s_datum_header
{
	// TODO
};

struct s_constant_pool
{
	// TODO
};

/* ---------- prototypes/CONSTANT_POOL.CPP */

/* TODO:
constant_pool_new
constant_pool_item_count
constant_pool_used_size
constant_pool_dispose
constant_pool_reset
constant_pool_add
constant_pool_find
constant_pool_contains
constant_pool_string_size_function
constant_pool_size
constant_pool_simplify
constant_pool_copy
*/
