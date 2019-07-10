/*
VECTOR3D.INL
*/

#pragma once

template <typename t_element>
struct s_vector3d
{
	t_element i;
	t_element j;
	t_element k;

	s_vector3d(t_element i, t_element j, t_element k) : i(i), j(j), k(k) {}
	s_vector3d(s_vector3d<t_element> const &other) : s_vector3d(other.i, other.j, other.k) {}
	s_vector3d() : s_vector3d(t_element(), t_element(), t_element()) {}

	bool operator==(s_vector3d<t_element> const &other) const
	{
		return (i == other.i) && (j == other.j) && (k == other.k);
	}

	bool operator!=(s_vector3d<t_element> const &other) const
	{
		return !(*this == other);
	}

	static t_element dot_product(s_vector3d<t_element> const &lhs, s_vector3d<t_element> const &rhs)
	{
		return (lhs.i * rhs.i) + (lhs.j * rhs.j) + (lhs.k * rhs.k);
	}

	t_element length_squared() const
	{
		return dot_product(*this, *this);
	}

	t_element length() const;
};
