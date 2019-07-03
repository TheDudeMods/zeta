/*
QUATERNION.INL
*/

#pragma once

template <typename t_element>
struct s_quaternion
{
	t_element i;
	t_element j;
	t_element k;
	t_element w;

	s_quaternion(t_element i, t_element j, t_element k, t_element w) : i(i), j(j), k(k), w(w) {}
	s_quaternion(s_quaternion<t_element> const &other) : s_quaternion(other.i, other.j, other.k, other.w) {}
	s_quaternion() : s_quaternion(t_element(), t_element(), t_element(), t_element()) {}

	bool operator==(s_quaternion<t_element> const &other) const
	{
		return (i == other.i) && (j == other.j) && (k == other.k) && (w == other.w);
	}

	bool operator!=(s_quaternion<t_element> const &other) const
	{
		return !(*this == other);
	}

	static t_element dot_product(s_quaternion<t_element> const &lhs, s_quaternion<t_element> const &rhs)
	{
		return (lhs.i * rhs.i) + (lhs.j * rhs.j) + (lhs.k * rhs.k) + (lhs.w * rhs.w);
	}

	t_element length_squared() const
	{
		return dot_product(*this, *this);
	}

	t_element length() const;
};
