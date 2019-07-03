/*
VECTOR2D.INL
*/

#pragma once

template <typename t_element>
struct s_vector2d
{
	t_element i;
	t_element j;

	s_vector2d(t_element i, t_element j) : i(i), j(j) {}
	s_vector2d(s_vector2d<t_element> const &other) : s_vector2d(other.i, other.j) {}
	s_vector2d() : s_vector2d(t_element(), t_element()) {}

	bool operator==(s_vector2d<t_element> const &other) const
	{
		return (i == other.i) && (j == other.j);
	}

	bool operator!=(s_vector2d<t_element> const &other) const
	{
		return !(*this == other);
	}

	static t_element dot_product(s_vector2d<t_element> const &lhs, s_vector2d<t_element> const &rhs)
	{
		return (lhs.i * rhs.i) + (lhs.j * rhs.j);
	}

	t_element length_squared() const
	{
		return dot_product(*this, *this);
	}

	t_element length() const;
};
