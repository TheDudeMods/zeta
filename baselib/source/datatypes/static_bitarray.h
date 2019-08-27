#pragma once

#include <cseries/cseries.h>
#include <datatypes/flags.h>

/* ---------- classes */

template <long const k_maximum_count>
class c_static_bitarray final
{
	static_assert(k_maximum_count > 0);

private:
	long m_bit_vector[BIT_VECTOR_SIZE_IN_LONGS(k_maximum_count)];

public:
	void clear()
	{
		csmemset(m_bit_vector, 0, BIT_VECTOR_SIZE_IN_BYTES(k_maximum_count));
	}

	void set(long bit_index, bool m_value)
	{
		assert(VALID_INDEX(bit_index, k_maximum_count));
		BIT_VECTOR_SET_FLAG(m_bit_vector, bit_index, m_value);
	}

	bool test(long bit_index) const
	{
		assert(VALID_INDEX(bit_index, k_maximum_count));
		return BIT_VECTOR_TEST_FLAG(m_bit_vector, bit_index);
	}

	bool operator[](long bit_index) const
	{
		assert(VALID_INDEX(bit_index, k_maximum_count));
		return test(bit_index);
	}
};
