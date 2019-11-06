#pragma once

#include <cseries/cseries.h>

/* ---------- classes */

template <typename t_element, long const k_maximum_count>
class c_static_array final
{
	static_assert(k_maximum_count > 0);

private:
	t_element m_elements[k_maximum_count];

public:
	c_static_array()
	{
		csmemset(m_elements, 0, sizeof(t_element) * k_maximum_count);
	}

	c_static_array(t_element *m_elements) :
		c_static_array()
	{
		assert(m_elements);

		csmemcpy(this->m_elements, m_elements, sizeof(t_element) * k_maximum_count);
	}

	c_static_array(c_static_array<t_element, k_maximum_count> const &other) :
		c_static_array(other.m_elements)
	{
	}

	long get_count() const
	{
		return k_maximum_count;
	}

	void set_memory(long value)
	{
		csmemset(m_elements, value, sizeof(t_element) * k_maximum_count);
	}

	t_element &operator[](long index)
	{
		assert(VALID_INDEX(index, k_maximum_count));

		return m_elements[index];
	}

	t_element const &operator[](long index) const
	{
		assert(VALID_INDEX(index, k_maximum_count));

		return m_elements[index];
	}

	operator t_element *()
	{
		return m_elements;
	}

	operator t_element const *() const
	{
		return m_elements;
	}
};
