#pragma once

#include <cseries/cseries.h>
#include <datatypes/static_string.h>
#include <memory/allocation_interface.h>

/* ---------- types */

typedef ulong(*hash_table_hash_function)(void *address);
typedef bool (*hash_table_compare_function)(void *lhs, void *rhs);

struct s_hash_table_bucket
{
	void *key;
	ulong hash;
	s_hash_table_bucket *next;
};

struct s_hash_table_internals
{
	c_static_string<32> name;
	long bucket_count;
	long maximum_elements;
	ulong user_data_size;
	bool verify;
	long key_offset;
	hash_table_hash_function hash_function;
	hash_table_compare_function compare_function;
	c_allocation_interface *allocation;
	void *base_address;
	s_hash_table_bucket *free_list;
	s_hash_table_bucket *buckets;
};

struct s_hash_table_iterator
{
	s_hash_table_internals *hash_table;
	long current_bucket_index;
	s_hash_table_bucket *current_bucket;
	s_hash_table_bucket *previous_bucket;
	void *current_user_data;
};

/* ---------- prototypes/HASH_TABLE.CPP */

uint hash_table_allocation_size(
	uint user_data_size,
	long bucket_count,
	long maximum_elements);

s_hash_table_internals *hash_table_create(
	char const *name,
	uint user_data_size,
	bool verify,
	uint key_offset,
	long bucket_count,
	long maximum_elements,
	hash_table_hash_function hash_function,
	hash_table_compare_function compare_function,
	char const *file,
	long line,
	c_allocation_interface *allocation);

void hash_table_dispose(
	s_hash_table_internals *hash_table,
	char const *file,
	long line);

void hash_table_reset(
	s_hash_table_internals *hash_table);

void hash_table_verify(
	s_hash_table_internals *hash_table);

bool hash_table_add(
	s_hash_table_internals *hash_table,
	void *key,
	void *in_user_data);

bool hash_table_remove(
	s_hash_table_internals *hash_table,
	void *key);

bool hash_table_set_data(
	s_hash_table_internals *hash_table,
	void *key,
	void *in_user_data);

void *hash_table_find(
	s_hash_table_internals *hash_table,
	void *key,
	void *out_user_data);

void hash_table_iterator_new(
	s_hash_table_iterator *iterator,
	s_hash_table_internals *hash_table);

void *hash_table_iterator_next(
	s_hash_table_iterator *iterator);

/* ---------- classes */

template <typename t_user_data, typename t_key>
class c_hash_table final :
	public s_hash_table_internals
{
public:
	static uint allocation_size(
		long bucket_count,
		long maximum_elements)
	{
		return hash_table_allocation_size(
			sizeof(t_user_data),
			bucket_count,
			maximum_elements);
	}

	static c_hash_table<t_user_data, t_key> *create(
		char const *name,
		long bucket_count,
		long maximum_elements,
		hash_table_hash_function hash_function,
		hash_table_compare_function compare_function,
		char const *file,
		long line,
		c_allocation_interface *allocation)
	{
		return reinterpret_cast<c_hash_table<t_user_data, t_key> *>(
			hash_table_create(
				name,
				sizeof(t_user_data),
				false,
				0,
				bucket_count,
				maximum_elements,
				hash_function,
				compare_function,
				file,
				line,
				allocation));
	}

	void dispose(
		char const *file,
		long line)
	{
		hash_table_dispose(this, file, line);
	}

	void reset()
	{
		hash_table_reset(this);
	}

	void verify()
	{
		hash_table_verify(this);
	}

	bool add(
		t_key *key,
		t_user_data *user_data)
	{
		return hash_table_add(this, key, user_data);
	}

	bool remove(
		t_key *key)
	{
		return hash_table_remove(this, key);
	}

	bool set_data(
		t_key *key,
		t_user_data *in_user_data)
	{
		return hash_table_set_data(this, key, in_user_data);
	}

	t_key *find(
		t_key *key,
		t_user_data *out_user_data)
	{
		return reinterpret_cast<t_key *>(
			hash_table_find(this, key, out_user_data));
	}
};
