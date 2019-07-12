#include <cseries/cseries.h>
#include <math/real_math.h>

#include <cmath>

/* ---------- code */

template <>
real s_point3d<real>::get_length() const
{
	return sqrtf(get_length_squared());
}

bool real_to_real16(const real value, real16 *out)
{
	if (!out)
		return false;

	union {
		float f;
		long l;
		dword ul;
	} s, v = { value };

	dword sign = v.l & k_real16_sign_n;
	v.l ^= sign;

	sign >>= k_real16_shift_sign;
	
	s.l = k_real16_mul_n;
	s.l = (long)(s.f * v.f);

	v.l ^= (s.l ^ v.l) & -(k_real16_min_n > v.l);
	
	v.l ^= (k_real16_inf_n ^ v.l) &
		-((k_real16_inf_n > v.l) & (v.l > k_real16_max_n));
	
	v.l ^= (k_real16_nan_n ^ v.l) &
		-((k_real16_nan_n > v.l) & (v.l > k_real16_inf_n));
	
	v.ul >>= k_real16_shift;
	
	v.l ^= ((v.l - k_real16_max_d) ^ v.l) & -(v.l > k_real16_max_c);
	v.l ^= ((v.l - k_real16_min_d) ^ v.l) & -(v.l > k_real16_sub_c);

	*out = (real16)(v.ul | sign);

	return true;
}

bool real16_to_real(const real16 value, real *out)
{
	if (!out)
		return false;

	union {
		float f;
		long l;
		dword ul;
	} s, v;

	v.ul = value;

	long sign = v.l & k_real16_sign_c;
	v.l ^= sign;
	
	sign <<= k_real16_shift_sign;
	
	v.l ^= ((v.l + k_real16_min_d) ^ v.l) & -(v.l > k_real16_sub_c);
	v.l ^= ((v.l + k_real16_max_d) ^ v.l) & -(v.l > k_real16_max_c);

	s.l = k_real16_mul_c;
	s.f *= v.l;
	
	long mask = -(k_real16_nor_c > v.l);
	
	v.l <<= k_real16_shift;
	v.l ^= (s.l ^ v.l) & mask;
	v.l |= sign;

	*out = v.f;

	return true;
}
