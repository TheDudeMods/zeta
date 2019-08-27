#pragma once

#include <cseries/cseries.h>

/* ---------- types */

struct s_hash_table_bucket
{
	// TODO
};

struct s_hash_table_internals
{
	// TODO
};

struct s_hash_table_iterator
{
	// TODO
};

/* ---------- prototypes/HASH_TABLE.CPP */

/* TODO:
hash_table_find
hash_table_find_internal
hash_table_set_functions
hash_table_allocation_size
hash_table_create
hash_table_dispose
hash_table_reset
hash_table_verify
hash_table_rebase
hash_table_add
hash_table_remove
hash_table_set_data
hash_table_iterator_new
hash_table_iterator_next
*/

/* ---------- classes */

class c_hash final
{
private:
	long m_hash;

public:
	c_hash(long hash);

	long get_hash() const;

	void add_data_range(void *address, long length);
	void max_tail(uchar *&a1, long &a2);
};

template <typename t_element, typename t_key>
class c_hash_table final : public s_hash_table_internals
{
public:
	c_hash_table()
	{
	}

	~c_hash_table()
	{

	}

	bool is_created() const;

};
