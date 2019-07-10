/*
REAL_MATH.H
*/

#pragma once

#include <math/point2d.inl>
#include <math/point3d.inl>
#include <math/vector2d.inl>
#include <math/vector3d.inl>
#include <math/vector4d.inl>
#include <math/quaternion.inl>

/* ---------- types */

typedef float angle;
static_assert(sizeof(angle) == 0x4);

typedef float real;
static_assert(sizeof(real) == 0x4);

typedef float real_fraction;
static_assert(sizeof(real_fraction) == 0x4);

typedef s_point2d<real> real_point2d;
static_assert(sizeof(real_point2d) == 0x8);

typedef s_point3d<real> real_point3d;
static_assert(sizeof(real_point3d) == 0xC);

typedef s_vector2d<real> real_vector2d;
static_assert(sizeof(real_vector2d) == 0x8);

typedef s_vector3d<real> real_vector3d;
static_assert(sizeof(real_vector3d) == 0xC);

typedef s_vector4d<real> real_vector4d;
static_assert(sizeof(real_vector4d) == 0x10);

typedef s_quaternion<real> real_quaternion;
static_assert(sizeof(real_quaternion) == 0x10);

/* ---------- prototypes/REAL_MATH.CPP */
