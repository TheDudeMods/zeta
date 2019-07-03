/*
RECTANGLE2D.INL
*/

#pragma once

template <typename t_element>
struct s_rectangle2d
{
	t_element top;
	t_element left;
	t_element bottom;
	t_element right;

	s_rectangle2d(t_element top, t_element left, t_element bottom, t_element right) :
		top(top), left(left), bottom(bottom), right(right)
	{
	}

	s_rectangle2d(s_rectangle2d<t_element> const &other) :
		s_rectangle2d(other.top, other.left, other.bottom, other.right)
	{
	}

	s_rectangle2d() :
		s_rectangle2d(t_element(), t_element(), t_element(), t_element())
	{
	}

	bool operator==(s_rectangle2d<t_element> const &other) const
	{
		return (top == other.top) && (left == other.left) && (bottom == other.bottom) && (right == other.right);
	}

	bool operator!=(s_rectangle2d<t_element> const &other) const
	{
		return !(*this == other);
	}
};
