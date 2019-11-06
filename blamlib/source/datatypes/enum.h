#pragma once

#include <cseries/cseries.h>

/* ---------- classes */

template <typename t_enum, typename t_value>
class c_enum final
{
	static_assert(__is_enum(t_enum));
	static_assert(__is_convertible_to(t_value, long));

private:
	t_value m_value;

public:
	c_enum() : m_value() {}
	c_enum(t_value m_value) : m_value(m_value) {}
	c_enum(t_enum m_value) : c_enum((t_value)m_value) {}
	c_enum(c_enum<t_enum, t_value> const &other) : c_enum(other.m_value) {}

	bool operator==(int other) const { return m_value == (t_value)other; }
	bool operator!=(int other) const { return !(*this == other); }

	bool operator==(t_enum other) const { return m_value == (t_value)other; }
	bool operator!=(t_enum other) const { return !(*this == other); }

	bool operator==(c_enum<t_enum, t_value> const &other) const { return m_value == other.m_value; }
	bool operator!=(c_enum<t_enum, t_value> const &other) const { return !(*this == other); }

	bool operator<(int other) const { return m_value < (t_value)other; }
	bool operator>(int other) const { return m_value > (t_value)other; }

	bool operator<(t_enum other) const { return m_value < (t_value)other; }
	bool operator>(t_enum other) const { return m_value > (t_value)other; }

	bool operator<(c_enum<t_enum, t_value> const &other) const { return m_value < other.m_value; }
	bool operator>(c_enum<t_enum, t_value> const &other) const { return m_value > other.m_value; }

	bool operator<=(int other) const { return m_value <= (t_value)other; }
	bool operator>=(int other) const { return m_value >= (t_value)other; }

	bool operator<=(t_enum other) const { return m_value <= (t_value)other; }
	bool operator>=(t_enum other) const { return m_value >= (t_value)other; }

	bool operator<=(c_enum<t_enum, t_value> const &other) const { return m_value <= other.m_value; }
	bool operator>=(c_enum<t_enum, t_value> const &other) const { return m_value >= other.m_value; }

	c_enum<t_enum, t_value> &operator=(t_enum other) { m_value = (t_value)other; return *this; }
	c_enum<t_enum, t_value> &operator=(c_enum<t_enum, t_value> const &other) { m_value = other.m_value; return *this; }

	operator t_enum() const { return static_cast<t_enum>(m_value); }
	operator t_value() const { return m_value; }
};
