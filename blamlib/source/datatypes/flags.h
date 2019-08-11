#pragma once

template <typename t_flags, typename t_value = int>
class c_flags
{
private:
	t_value m_value;

public:
	c_flags() : m_value() {}
	c_flags(const t_value &value) : m_value(value) {}
	c_flags(const t_flags &value) : c_flags((t_value)value) {}
	c_flags(const c_flags<t_flags, t_value> &other) : c_flags(other.m_value) {}

	bool operator==(const t_value &other) const { return m_value == other; }
	bool operator!=(const t_value &other) const { return !(*this == other); }

	bool operator==(const t_flags &other) const { return m_value == (t_value)other; }
	bool operator!=(const t_flags &other) const { return !(*this == other); }

	bool operator==(const c_flags<t_flags, t_value> &other) const { return m_value == other.m_value; }
	bool operator!=(const c_flags<t_flags, t_value> &other) const { return !(*this == other); }

	bool operator<(const t_value &other) const { return m_value < other; }
	bool operator>(const t_value &other) const { return m_value > other; }

	bool operator<(const t_flags &other) const { return m_value < (t_value)other; }
	bool operator>(const t_flags &other) const { return m_value > (t_value)other; }

	bool operator<(const c_flags<t_flags, t_value> &other) const { return m_value < other.m_value; }
	bool operator>(const c_flags<t_flags, t_value> &other) const { return m_value > other.m_value; }

	bool operator<=(const t_value &other) const { return m_value <= other; }
	bool operator>=(const t_value &other) const { return m_value >= other; }

	bool operator<=(const t_flags &other) const { return m_value <= (t_value)other; }
	bool operator>=(const t_flags &other) const { return m_value >= (t_value)other; }

	bool operator<=(const c_flags<t_flags, t_value> &other) const { return m_value <= other.m_value; }
	bool operator>=(const c_flags<t_flags, t_value> &other) const { return m_value >= other.m_value; }

	c_flags<t_flags, t_value> operator~() const { return c_flags(~m_value); }

	c_flags<t_flags, t_value> operator|(const int other) const { return c_flags(m_value | (t_value)other); }
	c_flags<t_flags, t_value> operator|(const t_flags &other) const { return c_flags(m_value | (t_value)other); }
	c_flags<t_flags, t_value> operator|(const c_flags<t_flags, t_value> &other) const { return c_flags(m_value | other.m_value); }

	c_flags<t_flags, t_value> &operator|=(const int other) { m_value |= (t_value)other; return *this; }
	c_flags<t_flags, t_value> &operator|=(const t_flags &other) { m_value |= (t_value)other; return *this; }
	c_flags<t_flags, t_value> &operator|=(const c_flags<t_flags, t_value> &other) { m_value |= other.m_value; return *this; }

	c_flags<t_flags, t_value> operator&(const int other) const { return c_flags(m_value & (t_value)other); }
	c_flags<t_flags, t_value> operator&(const t_flags &other) const { return c_flags(m_value & (t_value)other); }
	c_flags<t_flags, t_value> operator&(const c_flags<t_flags, t_value> &other) const { return c_flags(m_value & other.m_value); }

	c_flags<t_flags, t_value> &operator&=(const int other) { m_value &= (t_value)other; return *this; }
	c_flags<t_flags, t_value> &operator&=(const t_flags &other) { m_value &= (t_value)other; return *this; }
	c_flags<t_flags, t_value> &operator&=(const c_flags<t_flags, t_value> &other) { m_value &= other.m_value; return *this; }

	c_flags<t_flags, t_value> operator+(const t_value &other) const { return c_flags(m_value + other); }
	c_flags<t_flags, t_value> operator+(const t_flags &other) const { return c_flags(m_value + (t_value)other); }
	c_flags<t_flags, t_value> operator+(const c_flags<t_flags, t_value> &other) const { return c_flags(m_value + other.m_value); }

	c_flags<t_flags, t_value> &operator+=(const t_value &other) { m_value += other; return *this; }
	c_flags<t_flags, t_value> &operator+=(const t_flags &other) { m_value += (t_value)other; return *this; }
	c_flags<t_flags, t_value> &operator+=(const c_flags<t_flags, t_value> &other) { m_value += other.m_value; return *this; }

	c_flags<t_flags, t_value> operator-() const { return c_flags(-m_value); }

	c_flags<t_flags, t_value> operator-(const t_value &other) const { return c_flags(m_value - other); }
	c_flags<t_flags, t_value> operator-(const t_flags &other) const { return c_flags(m_value - (t_value)other); }
	c_flags<t_flags, t_value> operator-(const c_flags<t_flags, t_value> &other) const { return c_flags(m_value - other.m_value); }

	c_flags<t_flags, t_value> &operator-=(const t_value &other) { m_value -= other; return *this; }
	c_flags<t_flags, t_value> &operator-=(const t_flags &other) { m_value -= (t_value)other; return *this; }
	c_flags<t_flags, t_value> &operator-=(const c_flags<t_flags, t_value> &other) { m_value -= other.m_value; return *this; }

	c_flags<t_flags, t_value> operator*(const t_value &other) const { return c_flags(m_value * other); }
	c_flags<t_flags, t_value> operator*(const t_flags &other) const { return c_flags(m_value * (t_value)other); }
	c_flags<t_flags, t_value> operator*(const c_flags<t_flags, t_value> &other) const { return c_flags(m_value * other.m_value); }

	c_flags<t_flags, t_value> &operator*=(const t_value &other) { m_value *= other; return *this; }
	c_flags<t_flags, t_value> &operator*=(const t_flags &other) { m_value *= (t_value)other; return *this; }
	c_flags<t_flags, t_value> &operator*=(const c_flags<t_flags, t_value> &other) { m_value *= other.m_value; return *this; }

	c_flags<t_flags, t_value> operator/(const t_value &other) const { return c_flags(m_value / other); }
	c_flags<t_flags, t_value> operator/(const t_flags &other) const { return c_flags(m_value / (t_value)other); }
	c_flags<t_flags, t_value> operator/(const c_flags<t_flags, t_value> &other) const { return c_flags(m_value / other.m_value); }

	c_flags<t_flags, t_value> &operator/=(const t_value &other) { m_value /= other; return *this; }
	c_flags<t_flags, t_value> &operator/=(const t_flags &other) { m_value /= (t_value)other; return *this; }
	c_flags<t_flags, t_value> &operator/=(const c_flags<t_flags, t_value> &other) { m_value /= other.m_value; return *this; }

	c_flags<t_flags, t_value> &operator=(const t_value &other) { m_value = other; return *this; }
	c_flags<t_flags, t_value> &operator=(const t_flags &other) { m_value = (t_value)other; return *this; }
	c_flags<t_flags, t_value> &operator=(const c_flags<t_flags, t_value> &other) { m_value = other.m_value; return *this; }

	operator bool() const { return m_value; }
	operator t_flags() const { return (t_flags)m_value; }
	operator t_value() const { return m_value; }
};