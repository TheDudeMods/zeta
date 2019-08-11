#pragma once

#include <math/bounds.inl>
#include <math/point2d.inl>
#include <math/rectangle2d.inl>

/* ---------- type definitions */

typedef s_point2d<short> point2d;
static_assert(sizeof(point2d) == 0x4);

typedef s_rectangle2d<short> rectangle2d;
static_assert(sizeof(rectangle2d) == 0x8);

typedef unsigned long rgb_color;
static_assert(sizeof(rgb_color) == 0x4);

typedef unsigned long argb_color;
static_assert(sizeof(argb_color) == 0x4);

typedef s_bounds<short> short_bounds;
static_assert(sizeof(short_bounds) == 0x4);
