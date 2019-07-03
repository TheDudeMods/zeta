/*
POINT2D.INL
*/

#pragma once

template <typename t_element>
struct s_point2d
{
	t_element x;
	t_element y;

	s_point2d(t_element x, t_element y) : x(x), y(y) {}
	s_point2d(s_point2d<t_element> const &other) : s_point2d(other.x, other.y) {}
	s_point2d() : s_point2d(t_element(), t_element()) {}

	bool operator==(s_point2d<t_element> const &other) const
	{
		return (x == other.x) && (y == other.y);
	}

	bool operator!=(s_point2d<t_element> const &other) const
	{
		return !(*this == other);
	}

	static t_element dot_product(s_point2d<t_element> const &lhs, s_point2d<t_element> const &rhs)
	{
		return (lhs.x * rhs.x) + (lhs.y * rhs.y);
	}

	t_element length_squared() const
	{
		return dot_product(*this, *this);
	}

	t_element length() const;
};
