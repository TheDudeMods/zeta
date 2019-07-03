/*
POINT3D.INL
*/

#pragma once

template <typename t_element>
struct s_point3d
{
	t_element x;
	t_element y;
	t_element z;

	s_point3d(t_element x, t_element y, t_element z) : x(x), y(y), z(z) {}
	s_point3d(s_point3d<t_element> const &other) : s_point3d(other.x, other.y, other.z) {}
	s_point3d() : s_point3d(t_element(), t_element(), t_element()) {}

	bool operator==(s_point3d<t_element> const &other) const
	{
		return (x == other.x) && (y == other.y) && (z == other.z);
	}

	bool operator!=(s_point3d<t_element> const &other) const
	{
		return !(*this == other);
	}

	static t_element dot_product(s_point3d<t_element> const &lhs, s_point3d<t_element> const &rhs)
	{
		return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
	}

	t_element length_squared() const
	{
		return dot_product(*this, *this);
	}

	t_element length() const;
};
