#pragma once

#include <cseries/cseries.h>

/* ---------- classes */

template <typename t_enum, typename t_storage, long const k_number_of_bits = sizeof(t_storage) *k_uint8_bits>
class c_flags final
{
	static_assert(__is_enum(t_enum));
	static_assert(k_number_of_bits <= sizeof(t_storage) * k_uint8_bits);

private:
	t_storage m_value;

public:
	c_flags() : m_value(t_storage()) {}
	c_flags(t_storage value) : m_value(value) {}
	c_flags(t_enum value) : m_value(FLAG(static_cast<t_storage>(value))) {}
	c_flags(c_flags<t_enum, t_storage> const &other) : m_value(other.m_value) {}

	void clear()
	{
		m_value = 0;
	}

	bool operator==(c_flags<t_enum, t_storage> const &other) const
	{
		return m_value == other.m_value;
	}

	bool operator!=(c_flags<t_enum, t_storage> const &other) const
	{
		return m_value != other.m_value;
	}

	bool test(t_enum bit) const
	{
		return (m_value & FLAG(static_cast<t_storage>(bit))) != 0;
	}

	void set(t_enum bit, bool value)
	{
		t_storage flag = FLAG(static_cast<t_storage>(bit));

		if (value)
			m_value |= flag;
		else
			m_value &= ~flag;
	}

	bool valid() const
	{
		auto total_bits = sizeof(t_storage) * k_uint8_bits;

		for (auto current_bit = k_number_of_bits;
			current_bit < total_bits;
			current_bit++)
		{
			if (TEST_BIT(m_value, current_bit))
				return false;
		}

		return true;
	}

	c_flags<t_enum, t_storage> operator&(t_enum value) const
	{
		return c_flags(m_value & FLAG(static_cast<t_storage>(value)));
	}

	c_flags<t_enum, t_storage> operator~() const
	{
		return c_flags(~m_value);
	}

	c_flags<t_enum, t_storage> operator&(c_flags<t_enum, t_storage> const &other) const
	{
		return c_flags(m_value & other.m_value);
	}

	c_flags<t_enum, t_storage> operator|(t_enum value) const
	{
		return c_flags(m_value | FLAG(static_cast<t_storage>(value)));
	}

	c_flags<t_enum, t_storage> operator|(c_flags<t_enum, t_storage> const &other) const
	{
		return c_flags(m_value | other.m_value);
	}

	explicit operator bool() const
	{
		return m_value != 0;
	}

	explicit operator t_storage() const
	{
		return m_value;
	}
};
