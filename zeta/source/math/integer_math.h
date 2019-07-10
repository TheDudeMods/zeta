/*
INTEGER_MATH.H
*/

#pragma once

#include <math/point2d.inl>
#include <math/rectangle2d.inl>

/* ---------- types */

typedef s_point2d<short> point2d;
static_assert(sizeof(point2d) == 0x4);

typedef s_rectangle2d<short> rectangle2d;
static_assert(sizeof(rectangle2d) == 0x8);

/* ---------- prototypes/INTEGER_MATH.CPP */
