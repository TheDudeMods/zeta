#include <datatypes/hash_table.h>
#include <memory/memory_interface.h>

/* ---------- private prototypes */

s_hash_table_bucket **get_buckets(s_hash_table_internals *table);
s_hash_table_bucket *get_free_list_elements(s_hash_table_internals *table);
void *get_user_data(s_hash_table_bucket *bucket);

bool valid_bucket_pointer(s_hash_table_internals *table, s_hash_table_bucket *bucket);

s_hash_table_bucket *hash_table_find_internal(s_hash_table_internals *table, void *key);

/* ---------- public code */

uint hash_table_allocation_size(
	uint user_data_size,
	long bucket_count,
	long maximum_elements)
{
	return sizeof(s_hash_table_internals) +
		(bucket_count * sizeof(void *)) +
		(maximum_elements * (user_data_size + sizeof(s_hash_table_bucket)));
}

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
	c_allocation_interface *allocation)
{
	auto allocation_size = hash_table_allocation_size(
		user_data_size, bucket_count, maximum_elements);
	
	assert(key_offset < user_data_size - sizeof(void *));
	assert(bucket_count > 0);
	assert(maximum_elements > 0);
	assert(hash_function);
	assert(compare_function);
	assert(allocation);

	auto hash_table = reinterpret_cast<s_hash_table_internals *>(
		allocation->allocate(allocation_size, file, line));

	if (hash_table)
	{
		csmemset(hash_table, 0, allocation_size);

		hash_table->name.set(name);
		hash_table->bucket_count = bucket_count;
		hash_table->maximum_elements = maximum_elements;
		hash_table->user_data_size = user_data_size;
		hash_table->verify = verify;
		hash_table->key_offset = key_offset;
		hash_table->hash_function = hash_function;
		hash_table->compare_function = compare_function;
		hash_table->allocation = allocation;
		hash_table->base_address = hash_table;

		hash_table_reset(hash_table);
	}

	return hash_table;
}

void hash_table_dispose(
	s_hash_table_internals *hash_table,
	char const *file,
	long line)
{
	hash_table_verify(hash_table);

	auto allocation = hash_table->allocation;
	assert(allocation != nullptr);

	allocation->deallocate(hash_table, file, line);
}

void hash_table_reset(
	s_hash_table_internals *hash_table)
{
	auto bucket_count = hash_table->bucket_count;
	auto bucket_size = hash_table->user_data_size + sizeof(s_hash_table_bucket);
	auto maximum_elements = hash_table->maximum_elements;
	auto buckets = get_buckets(hash_table);

	csmemset(buckets, 0, bucket_count * sizeof(void *) + maximum_elements * bucket_size);

	auto free_list = get_free_list_elements(hash_table);
	hash_table->free_list = nullptr;

	for (auto i = 0; i < maximum_elements; i++)
	{
		auto next_element_to_add = offset_pointer(free_list, i * bucket_size);
		assert(valid_bucket_pointer(hash_table, next_element_to_add));

		next_element_to_add->next = free_list;
		hash_table->free_list = next_element_to_add;
	}

	hash_table_verify(hash_table);
}

void hash_table_verify(
	s_hash_table_internals *hash_table)
{
	assert(hash_table);
	assert(hash_table->bucket_count > 0);
	assert(hash_table->maximum_elements > 0);
	assert(hash_table->user_data_size > 0);
	assert(hash_table->hash_function);
	assert(hash_table->compare_function);
	assert(hash_table->allocation);
	assert(hash_table->base_address == static_cast<const void *>(hash_table));

	auto buckets = get_buckets(hash_table);

	for (auto i = 0; i < hash_table->bucket_count; i++)
	{
		auto current_bucket = buckets[i];

		while (current_bucket)
		{
			assert(valid_bucket_pointer(hash_table, current_bucket));
			current_bucket = current_bucket->next;
		}
	}

	auto current_bucket = get_free_list_elements(hash_table);

	while (current_bucket)
	{
		assert(valid_bucket_pointer(hash_table, current_bucket));
		current_bucket = current_bucket->next;
	}
}

bool hash_table_add(
	s_hash_table_internals *hash_table,
	void *key,
	void *in_user_data)
{
	assert(hash_table_find_internal(hash_table, key) == nullptr);
	assert(in_user_data);

	if (!hash_table->free_list)
		return false;

	auto hash = hash_table->hash_function(key);

	auto bucket_count = hash_table->bucket_count;
	auto target_bucket_index = hash - (hash / bucket_count) * bucket_count;
	auto buckets = get_buckets(hash_table);

	auto new_element = hash_table->free_list;
	hash_table->free_list = new_element->next;

	assert(valid_bucket_pointer(hash_table, new_element));
	assert(valid_bucket_pointer(hash_table, hash_table->free_list));

	new_element->key = key;
	new_element->hash = hash;

	auto user_data_size = hash_table->user_data_size;
	auto user_data = get_user_data(new_element);

	csmemcpy(user_data, in_user_data, user_data_size);

	if (hash_table->verify)
	{
		user_data = get_user_data(new_element);
		new_element->key = reinterpret_cast<char *>(user_data) + hash_table->key_offset;
	}

	assert(VALID_INDEX(target_bucket_index, hash_table->bucket_count));

	new_element->next = buckets[target_bucket_index];
	buckets[target_bucket_index] = new_element;

	return true;
}

bool hash_table_remove(
	s_hash_table_internals *hash_table,
	void *key)
{
	auto hash = hash_table->hash_function(key);
	auto bucket_count = hash_table->bucket_count;
	auto target_bucket_index = hash - (hash / bucket_count) * bucket_count;
	auto buckets = get_buckets(hash_table);

	assert(VALID_INDEX(target_bucket_index, hash_table->bucket_count));

	auto current_bucket = buckets[target_bucket_index];
	s_hash_table_bucket *previous_bucket = nullptr;

	while (true)
	{
		if (!current_bucket)
		{
			assert(hash_table_find_internal(hash_table, key) == nullptr);
			return false;
		}

		assert(valid_bucket_pointer(hash_table, current_bucket));

		auto comparison = hash_table->compare_function(key, current_bucket->key);

		if (comparison)
		{
			assert(hash_table_find_internal(hash_table, key) == current_bucket);

			if (previous_bucket)
				previous_bucket->next = current_bucket->next;
			else
				buckets[target_bucket_index] = current_bucket->next;

			current_bucket->next = hash_table->free_list;
			hash_table->free_list = current_bucket;
			
			assert(hash_table_find_internal(hash_table, key) == nullptr);
			return true;
		}

		previous_bucket = current_bucket;
		current_bucket = current_bucket->next;
	}
}

bool hash_table_set_data(
	s_hash_table_internals *hash_table,
	void *key,
	void *in_user_data)
{
	auto bucket = hash_table_find_internal(hash_table, key);

	assert(in_user_data);

	if (!bucket)
		return false;

	auto user_data_size = hash_table->user_data_size;
	auto user_data = get_user_data(bucket);

	csmemcpy(user_data, in_user_data, user_data_size);

	if (hash_table->verify)
	{
		user_data = get_user_data(bucket);
		bucket->key = reinterpret_cast<char *>(user_data) + hash_table->key_offset;
	}

	return true;
}

void *hash_table_find(
	s_hash_table_internals *hash_table,
	void *key,
	void *out_user_data)
{
	auto bucket = hash_table_find_internal(hash_table, key);

	if (!bucket)
		return nullptr;

	if (out_user_data != nullptr)
	{
		auto user_data_size = hash_table->user_data_size;
		auto user_data = get_user_data(bucket);

		csmemcpy(out_user_data, user_data, user_data_size);
	}

	return bucket->key;
}

void hash_table_iterator_new(
	s_hash_table_iterator *iterator,
	s_hash_table_internals *hash_table)
{
	iterator->hash_table = hash_table;
	iterator->current_bucket_index = NONE;
	iterator->current_bucket = nullptr;
	iterator->previous_bucket = nullptr;
	iterator->current_user_data = nullptr;
}

void *hash_table_iterator_next(
	s_hash_table_iterator *iterator)
{
	auto buckets = get_buckets(iterator->hash_table);

	if (iterator->current_bucket)
		iterator->current_bucket = iterator->current_bucket->next;

	while (iterator->current_bucket == nullptr &&
		++iterator->current_bucket_index < iterator->hash_table->bucket_count)
	{
		iterator->current_bucket = buckets[iterator->current_bucket_index];
	}

	if (!iterator->current_bucket)
		return nullptr;

	iterator->previous_bucket = iterator->current_bucket;

	return iterator->current_user_data = get_user_data(iterator->current_bucket);
}

/* ---------- private code */

s_hash_table_bucket **get_buckets(
	s_hash_table_internals *table)
{
	return &table->buckets;
}

s_hash_table_bucket *get_free_list_elements(
	s_hash_table_internals *table)
{
	return reinterpret_cast<s_hash_table_bucket *>(
		offset_pointer(table, sizeof(s_hash_table_internals) +
		(table->bucket_count * sizeof(s_hash_table_bucket *))));
}

void *get_user_data(s_hash_table_bucket *bucket)
{
	return &bucket[1];
}

bool valid_bucket_pointer(
	s_hash_table_internals *table,
	s_hash_table_bucket *bucket)
{
	assert(table);

	if (!bucket)
		return true;

	auto bucket_size = table->user_data_size + sizeof(s_hash_table_bucket);
	auto free_buckets = get_free_list_elements(table);
	auto last_bucket = offset_pointer(free_buckets, bucket_size * (table->maximum_elements - 1ui64));

	if ((bucket < free_buckets) || (last_bucket < bucket))
		return false;

	auto distance = pointer_distance(free_buckets, bucket);

	return distance == (distance / bucket_size) * bucket_size;
}

s_hash_table_bucket *hash_table_find_internal(
	s_hash_table_internals *table,
	void *key)
{
	s_hash_table_bucket *result = nullptr;

	auto hash = table->hash_function(key);
	auto bucket_count = table->bucket_count;

	auto target_bucket_index = hash - (hash / bucket_count) * bucket_count;
	auto buckets = get_buckets(table);

	assert(VALID_INDEX(target_bucket_index, table->bucket_count));

	for (auto current_bucket = buckets[target_bucket_index];
		current_bucket != nullptr;
		current_bucket = current_bucket->next)
	{
		assert(valid_bucket_pointer(table, current_bucket));
		assert(result == nullptr);

		if ((current_bucket->hash == hash) && table->compare_function(key, current_bucket->key))
		{
			assert(result == nullptr);
			result = current_bucket;
		}
	}

	return result;
}
