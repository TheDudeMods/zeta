#pragma once

#include <math/ahsv_color.inl>
#include <math/argb_color.inl>
#include <math/bounds.inl>
#include <math/euler_angles2d.inl>
#include <math/euler_angles3d.inl>
#include <math/hsv_color.inl>
#include <math/matrix3x3.inl>
#include <math/matrix4x3.inl>
#include <math/plane2d.inl>
#include <math/plane3d.inl>
#include <math/point2d.inl>
#include <math/point3d.inl>
#include <math/quaternion.inl>
#include <math/rgb_color.inl>
#include <math/vector2d.inl>
#include <math/vector3d.inl>

/* ---------- constants */

// TODO: name the real16 constants a bit better
enum {
	k_real16_shift = 13,
	k_real16_shift_sign = 16,
	k_real16_sign_n = 0x80000000,
	k_real16_sign_c = k_real16_sign_n >> k_real16_shift_sign,
	k_real16_min_n = 0x38800000,
	k_real16_max_n = 0x477FE000,
	k_real16_mul_n = (1 << 23) / k_real16_min_n,
	k_real16_mul_c = k_real16_min_n / (1 << (23 - k_real16_shift)),
	k_real16_inf_n = 0x7F800000,
	k_real16_inf_c = k_real16_inf_n >> k_real16_shift,
	k_real16_nan_n = (k_real16_inf_c + 1) << k_real16_shift,
	k_real16_min_c = k_real16_min_n >> k_real16_shift,
	k_real16_max_c = k_real16_max_n >> k_real16_shift,
	k_real16_sub_c = 0x003FF,
	k_real16_nor_c = 0x00400,
	k_real16_min_d = k_real16_min_c - k_real16_sub_c - 1,
	k_real16_max_d = k_real16_inf_c - k_real16_max_c - 1
};

/* ---------- type definitions */

typedef float angle;
static_assert(sizeof(angle) == 0x4);

typedef s_bounds<angle> angle_bounds;
static_assert(sizeof(angle_bounds) == 0x8);

typedef float real;
static_assert(sizeof(real) == 0x4);

typedef s_bounds<real> real_bounds;
static_assert(sizeof(real_bounds) == 0x8);

typedef s_point2d<real> real_point2d;
static_assert(sizeof(real_point2d) == 0x8);

typedef s_point3d<real> real_point3d;
static_assert(sizeof(real_point3d) == 0xC);

typedef s_vector2d<real> real_vector2d;
static_assert(sizeof(real_vector2d) == 0x8);

typedef s_vector3d<real> real_vector3d;
static_assert(sizeof(real_vector3d) == 0xC);

typedef s_quaternion<real> real_quaternion;
static_assert(sizeof(real_quaternion) == 0x10);

typedef s_euler_angles2d<angle> real_euler_angles2d;
static_assert(sizeof(real_euler_angles2d) == 0x8);

typedef s_euler_angles3d<angle> real_euler_angles3d;
static_assert(sizeof(real_euler_angles3d) == 0xC);

typedef s_plane2d<real> real_plane2d;
static_assert(sizeof(real_plane2d) == 0xC);

typedef s_plane3d<real> real_plane3d;
static_assert(sizeof(real_plane3d) == 0x10);

typedef s_rgb_color<real> real_rgb_color;
static_assert(sizeof(real_rgb_color) == 0xC);

typedef s_argb_color<real> real_argb_color;
static_assert(sizeof(real_argb_color) == 0x10);

typedef s_hsv_color<real> real_hsv_color;
static_assert(sizeof(real_hsv_color) == 0xC);

typedef s_ahsv_color<real> real_ahsv_color;
static_assert(sizeof(real_ahsv_color) == 0x10);

typedef float real_fraction;
static_assert(sizeof(real_fraction) == 0x4);

typedef s_bounds<real_fraction> real_fraction_bounds;
static_assert(sizeof(real_fraction_bounds) == 0x8);

typedef short real16;
static_assert(sizeof(real16) == 0x2);

typedef s_bounds<real16> real16_bounds;
static_assert(sizeof(real16_bounds) == 0x4);

typedef s_matrix4x3<real> real_matrix4x3;
static_assert(sizeof(real_matrix4x3) == 0x34);

typedef s_matrix3x3<real> real_matrix3x3;
static_assert(sizeof(real_matrix3x3) == 0x24);

/* ---------- prototypes */

bool real_to_real16(const real value, real16 *out);
bool real16_to_real(const real16 value, real *out);
