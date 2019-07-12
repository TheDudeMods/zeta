#pragma once

template <typename t_element>
struct s_point3d
{
	t_element x;
	t_element y;
	t_element z;

	inline s_point3d(const t_element &x, const t_element &y, const t_element &z) : x(x), y(y), z(z) {}
	inline s_point3d() : s_point3d(t_element(), t_element(), t_element()) {}

	inline t_element get_length_squared() const { return (x * x) + (y * y) + (z * z); }
	t_element get_length() const;

	inline s_point3d<t_element> normalize() const { return *this / get_length(); }

	inline s_point3d<t_element> operator+(const t_element &other) const
	{
		return s_point3d<t_element>(x + other, y + other, z + other);
	}

	inline s_point3d<t_element> operator+(const s_point3d<t_element> &other) const
	{
		return s_point3d<t_element>(x + other.x, y + other.y, z + other.z);
	}

	inline friend s_point3d<t_element> operator+(const t_element &lhs, const s_point3d<t_element> &rhs)
	{
		return s_point3d<t_element>(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z);
	}

	inline s_point3d<t_element> operator-() const
	{
		return s_point3d<t_element>(-x, -y, -z);
	}

	inline s_point3d<t_element> operator-(const t_element &other) const
	{
		return s_point3d<t_element>(x - other, y - other, z - other);
	}

	inline s_point3d<t_element> operator-(const s_point3d<t_element> &other) const
	{
		return s_point3d<t_element>(x - other.x, y - other.y, z - other.z);
	}

	inline friend s_point3d<t_element> operator-(const t_element &lhs, const s_point3d<t_element> &rhs)
	{
		return s_point3d<t_element>(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z);
	}

	inline s_point3d<t_element> operator*(const t_element &other) const
	{
		return s_point3d<t_element>(x * other, y * other, z * other);
	}

	inline s_point3d<t_element> operator*(const s_point3d<t_element> &other) const
	{
		return s_point3d<t_element>(x * other.x, y * other.y, z * other.z);
	}

	inline friend s_point3d<t_element> operator*(const t_element &lhs, const s_point3d<t_element> &rhs)
	{
		return s_point3d<t_element>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
	}

	inline s_point3d<t_element> operator/(const t_element &other) const
	{
		return s_point3d<t_element>(x / other, y / other, z / other);
	}

	inline s_point3d<t_element> operator/(const s_point3d<t_element> &other) const
	{
		return s_point3d<t_element>(x / other.x, y / other.y, z / other.z);
	}

	inline friend s_point3d<t_element> operator/(const t_element &lhs, const s_point3d<t_element> &rhs)
	{
		return s_point3d<t_element>(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z);
	}
};
static_assert(sizeof(s_point3d<long>) == 0xC);
