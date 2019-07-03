/*
VECTOR4D.INL
*/

#pragma once

template <typename t_element>
struct s_vector4d
{
	t_element i;
	t_element j;
	t_element k;
	t_element w;

	s_vector4d(t_element i, t_element j, t_element k, t_element w) : i(i), j(j), k(k), w(w) {}
	s_vector4d(s_vector4d<t_element> const &other) : s_vector4d(other.i, other.j, other.k, other.w) {}
	s_vector4d() : s_vector4d(t_element(), t_element(), t_element(), t_element()) {}

	bool operator==(s_vector4d<t_element> const &other) const
	{
		return (i == other.i) && (j == other.j) && (k == other.k) && (w == other.w);
	}

	bool operator!=(s_vector4d<t_element> const &other) const
	{
		return !(*this == other);
	}

	static t_element dot_product(s_vector4d<t_element> const &lhs, s_vector4d<t_element> const &rhs)
	{
		return (lhs.i * rhs.i) + (lhs.j * rhs.j) + (lhs.k * rhs.k) + (lhs.w * rhs.w);
	}

	t_element length_squared() const
	{
		return dot_product(*this, *this);
	}

	t_element length() const;
};
