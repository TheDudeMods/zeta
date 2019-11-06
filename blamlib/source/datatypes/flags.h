#pragma once

#include <cseries/cseries.h>

/* ---------- classes */

template <typename t_enum, typename t_value>
class c_flags final
{
	static_assert(__is_enum(t_enum));
	static_assert(__is_convertible_to(t_value, unsigned long));

private:
	t_value m_value;

public:
	c_flags() : m_value(t_value()) {}
	c_flags(t_value value) : m_value(value) {}
	c_flags(t_enum value) : m_value(static_cast<t_value>(value)) {}
	c_flags(c_flags<t_enum, t_value> const &other) : m_value(other.m_value) {}

	void clear()
	{
		m_value = 0;
	}

	bool operator==(c_flags<t_enum, t_value> const &other) const
	{
		return m_value == other.m_value;
	}

	bool operator!=(c_flags<t_enum, t_value> const &other) const
	{
		return m_value != other.m_value;
	}

	bool test(t_enum bit) const
	{
		return (m_value & FLAG(static_cast<t_value>(bit))) != 0;
	}

	void set(t_enum bit, bool value)
	{
		t_value flag = FLAG(static_cast<t_value>(bit));

		if (value)
			m_value |= flag;
		else
			m_value &= ~flag;
	}

	c_flags<t_enum, t_value> operator&(t_enum value) const
	{
		return c_flags(m_value & FLAG(static_cast<t_value>(value)));
	}

	c_flags<t_enum, t_value> operator~() const
	{
		return c_flags(~m_value);
	}

	c_flags<t_enum, t_value> operator&(c_flags<t_enum, t_value> const &other) const
	{
		return c_flags(m_value & other.m_value);
	}

	c_flags<t_enum, t_value> operator|(t_enum value) const
	{
		return c_flags(m_value | FLAG(static_cast<t_value>(value)));
	}

	c_flags<t_enum, t_value> operator|(c_flags<t_enum, t_value> const &other) const
	{
		return c_flags(m_value | other.m_value);
	}

	explicit operator bool() const
	{
		return m_value != 0;
	}

	explicit operator t_value() const
	{
		return m_value;
	}
};
