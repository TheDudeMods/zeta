#pragma once

#include <cseries/cseries.h>

/* ---------- classes */

template <typename t_element>
class c_basic_buffer
{
private:
	t_element *m_elements;
	long long m_size;

public:
	c_basic_buffer() :
		c_basic_buffer(nullptr, 0)
	{
	}

	c_basic_buffer(t_element *elements, long size) :
		m_elements(elements),
		m_size(size)
	{
	}

	t_element *get_elements()
	{
		return m_elements;
	}

	long long get_size()
	{
		return m_size;
	}

	t_element const *get_elements() const
	{
		return m_elements;
	}

	bool empty() const
	{
		return m_elements == nullptr || m_size == 0;
	}

	t_element *begin()
	{
		return m_elements;
	}

	t_element const *begin() const
	{
		return m_elements;
	}

	t_element *end()
	{
		return (t_element *)((char *)m_elements + m_size);
	}

	t_element const *end() const
	{
		return (t_element *)((char *)m_elements + m_size);
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

/* ---------- inline code */

template <typename t_type>
inline ulonglong address_from_pointer(
	t_type *pointer)
{
	return (ulonglong)pointer;
}

template <typename t_type>
inline t_type *pointer_from_address(
	ulonglong address)
{
	return reinterpret_cast<t_type *>(address);
}

template <typename t_type, typename t_offset>
inline t_type *offset_pointer(
	t_type *pointer,
	t_offset offset)
{
	static_assert(__is_convertible_to(t_offset, ulonglong));
	return pointer_from_address<t_type>(address_from_pointer(pointer) + (ulonglong)offset);
}

inline ulonglong align_address(
	ulonglong address,
	long alignment_bits)
{
	ulonglong alignment_mask = (1Ui64 << ((ulonglong)alignment_bits & (ulonglong)k_int8_max)) - 1Ui64;
	return address + alignment_mask & ~alignment_mask;
}

inline bool address_is_aligned(
	ulonglong address,
	long alignment_bits)
{
	ulonglong alignment_mask = (1Ui64 << ((ulonglong)alignment_bits & (ulonglong)k_int8_max)) - 1Ui64;
	return address & alignment_mask;
}

template <typename t_type>
inline t_type *align_pointer(
	t_type *pointer,
	long alignment_bits)
{
	ulonglong address = address_from_pointer(pointer);
	address = align_address(address, alignment_bits);
	return pointer_from_address<t_type>(address);
}

template <typename t_type>
inline bool pointer_is_aligned(
	t_type *pointer,
	long alignment_bits)
{
	ulonglong address = address_from_pointer(pointer);
	return address_is_aligned(address, alignment_bits);
}

template <typename t_lhs_type, typename t_rhs_type>
long long pointer_distance(
	t_lhs_type *p1,
	t_rhs_type *p2)

{
	return (long long)((ulonglong)p2 - (ulonglong)p1);
}
