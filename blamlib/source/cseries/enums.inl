#pragma once

template <typename t_enum, typename t_value = int>
class c_enum
{
private:
	t_value m_value;

public:
	c_enum() : m_value() {}
	c_enum(const t_value &value) : m_value(value) {}
	c_enum(const t_enum &value) : c_enum((t_value)value) {}
	c_enum(const c_enum<t_enum, t_value> &other) : c_enum(other.m_value) {}

	bool operator==(const t_value &other) const { return m_value == other; }
	bool operator!=(const t_value &other) const { return !(*this == other); }

	bool operator==(const t_enum &other) const { return m_value == (t_value)other; }
	bool operator!=(const t_enum &other) const { return !(*this == other); }

	bool operator==(const c_enum<t_enum, t_value> &other) const { return m_value == other.m_value; }
	bool operator!=(const c_enum<t_enum, t_value> &other) const { return !(*this == other); }

	bool operator<(const t_value &other) const { return m_value < other; }
	bool operator>(const t_value &other) const { return m_value > other; }

	bool operator<(const t_enum &other) const { return m_value < (t_value)other; }
	bool operator>(const t_enum &other) const { return m_value > (t_value)other; }

	bool operator<(const c_enum<t_enum, t_value> &other) const { return m_value < other.m_value; }
	bool operator>(const c_enum<t_enum, t_value> &other) const { return m_value > other.m_value; }

	bool operator<=(const t_value &other) const { return m_value <= other; }
	bool operator>=(const t_value &other) const { return m_value >= other; }

	bool operator<=(const t_enum &other) const { return m_value <= (t_value)other; }
	bool operator>=(const t_enum &other) const { return m_value >= (t_value)other; }

	bool operator<=(const c_enum<t_enum, t_value> &other) const { return m_value <= other.m_value; }
	bool operator>=(const c_enum<t_enum, t_value> &other) const { return m_value >= other.m_value; }

	c_enum<t_enum, t_value> operator~() const { return c_enum(~m_value); }

	c_enum<t_enum, t_value> operator|(const int other) const { return c_enum(m_value | (t_value)other); }
	c_enum<t_enum, t_value> operator|(const t_enum &other) const { return c_enum(m_value | (t_value)other); }
	c_enum<t_enum, t_value> operator|(const c_enum<t_enum, t_value> &other) const { return c_enum(m_value | other.m_value); }

	c_enum<t_enum, t_value> &operator|=(const int other) { m_value |= (t_value)other; return *this; }
	c_enum<t_enum, t_value> &operator|=(const t_enum &other) { m_value |= (t_value)other; return *this; }
	c_enum<t_enum, t_value> &operator|=(const c_enum<t_enum, t_value> &other) { m_value |= other.m_value; return *this; }

	c_enum<t_enum, t_value> operator&(const int other) const { return c_enum(m_value & (t_value)other); }
	c_enum<t_enum, t_value> operator&(const t_enum &other) const { return c_enum(m_value & (t_value)other); }
	c_enum<t_enum, t_value> operator&(const c_enum<t_enum, t_value> &other) const { return c_enum(m_value & other.m_value); }

	c_enum<t_enum, t_value> &operator&=(const int other) { m_value &= (t_value)other; return *this; }
	c_enum<t_enum, t_value> &operator&=(const t_enum &other) { m_value &= (t_value)other; return *this; }
	c_enum<t_enum, t_value> &operator&=(const c_enum<t_enum, t_value> &other) { m_value &= other.m_value; return *this; }

	c_enum<t_enum, t_value> operator+(const t_value &other) const { return c_enum(m_value + other); }
	c_enum<t_enum, t_value> operator+(const t_enum &other) const { return c_enum(m_value + (t_value)other); }
	c_enum<t_enum, t_value> operator+(const c_enum<t_enum, t_value> &other) const { return c_enum(m_value + other.m_value); }

	c_enum<t_enum, t_value> &operator+=(const t_value &other) { m_value += other; return *this; }
	c_enum<t_enum, t_value> &operator+=(const t_enum &other) { m_value += (t_value)other; return *this; }
	c_enum<t_enum, t_value> &operator+=(const c_enum<t_enum, t_value> &other) { m_value += other.m_value; return *this; }

	c_enum<t_enum, t_value> operator-() const { return c_enum(-m_value); }

	c_enum<t_enum, t_value> operator-(const t_value &other) const { return c_enum(m_value - other); }
	c_enum<t_enum, t_value> operator-(const t_enum &other) const { return c_enum(m_value - (t_value)other); }
	c_enum<t_enum, t_value> operator-(const c_enum<t_enum, t_value> &other) const { return c_enum(m_value - other.m_value); }

	c_enum<t_enum, t_value> &operator-=(const t_value &other) { m_value -= other; return *this; }
	c_enum<t_enum, t_value> &operator-=(const t_enum &other) { m_value -= (t_value)other; return *this; }
	c_enum<t_enum, t_value> &operator-=(const c_enum<t_enum, t_value> &other) { m_value -= other.m_value; return *this; }

	c_enum<t_enum, t_value> operator*(const t_value &other) const { return c_enum(m_value * other); }
	c_enum<t_enum, t_value> operator*(const t_enum &other) const { return c_enum(m_value * (t_value)other); }
	c_enum<t_enum, t_value> operator*(const c_enum<t_enum, t_value> &other) const { return c_enum(m_value * other.m_value); }

	c_enum<t_enum, t_value> &operator*=(const t_value &other) { m_value *= other; return *this; }
	c_enum<t_enum, t_value> &operator*=(const t_enum &other) { m_value *= (t_value)other; return *this; }
	c_enum<t_enum, t_value> &operator*=(const c_enum<t_enum, t_value> &other) { m_value *= other.m_value; return *this; }

	c_enum<t_enum, t_value> operator/(const t_value &other) const { return c_enum(m_value / other); }
	c_enum<t_enum, t_value> operator/(const t_enum &other) const { return c_enum(m_value / (t_value)other); }
	c_enum<t_enum, t_value> operator/(const c_enum<t_enum, t_value> &other) const { return c_enum(m_value / other.m_value); }

	c_enum<t_enum, t_value> &operator/=(const t_value &other) { m_value /= other; return *this; }
	c_enum<t_enum, t_value> &operator/=(const t_enum &other) { m_value /= (t_value)other; return *this; }
	c_enum<t_enum, t_value> &operator/=(const c_enum<t_enum, t_value> &other) { m_value /= other.m_value; return *this; }

	c_enum<t_enum, t_value> &operator=(const t_value &other) { m_value = other; return *this; }
	c_enum<t_enum, t_value> &operator=(const t_enum &other) { m_value = (t_value)other; return *this; }
	c_enum<t_enum, t_value> &operator=(const c_enum<t_enum, t_value> &other) { m_value = other.m_value; return *this; }

	operator bool() const { return m_value; }
	operator t_enum() const { return (t_enum)m_value; }
	operator t_value() const { return m_value; }
};