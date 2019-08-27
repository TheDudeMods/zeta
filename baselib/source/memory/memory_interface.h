#pragma once

#include <cseries/cseries.h>

/* ---------- inline code */

template <typename t_type>
inline ulonglong address_from_pointer(
	t_type *pointer)
{
	return reinterpret_cast<ulonglong>(pointer);
}

template <typename t_type>
inline t_type *pointer_from_address(
	ulonglong address)
{
	return reinterpret_cast<t_type *>(address);
}

template <typename t_type>
inline t_type *offset_pointer(
	t_type *pointer,
	long offset)
{
	return pointer_from_address<t_type>(address_from_pointer(pointer) + offset);
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
