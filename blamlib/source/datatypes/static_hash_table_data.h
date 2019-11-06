#pragma once

#include <cseries/cseries.h>
#include <datatypes/static_array.h>

/* ---------- classes */

template <typename t_element, long const k_maximum_count>
class c_static_hash_table_data
{
	static_assert(k_maximum_count > 0);

private:
	long m_total_count;
	c_static_array<t_element, k_maximum_count> m_elements;
	
	long m_hash_entry_count;
	c_static_array<short, k_maximum_count> m_hash_entries;

public:
	c_static_hash_table_data() :
		m_total_count(0),
		m_elements(),
		m_hash_entry_count(0),
		m_hash_entries()
	{
	}

	void clear_all()
	{
		m_total_count = 0;
		m_hash_entries.set_memory(NONE);
	}

	t_element &get_data(long index)
	{
		assert(VALID_INDEX(index, k_maximum_count));

		return m_elements[index];
	}

	t_element const &get_data(long index) const
	{
		assert(VALID_INDEX(index, k_maximum_count));

		return m_elements[index];
	}

	long get_maximum_count() const
	{
		return k_maximum_count;
	}

	long get_total_count() const
	{
		return m_total_count;
	}

	void increment_total_count()
	{
		m_total_count++;
	}

	void decrement_total_count()
	{
		m_total_count--;
	}

	long get_hash_entry_count() const
	{
		return m_hash_entry_count;
	}

	void increment_hash_entry_count()
	{
		m_hash_entry_count++;
	}

	void decrement_hash_entry_count()
	{
		m_hash_entry_count--;
	}
};
