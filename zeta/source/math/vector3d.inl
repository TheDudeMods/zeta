#pragma once

template <typename t_element>
struct s_vector3d
{
	t_element i;
	t_element j;
	t_element k;
};
static_assert(sizeof(s_vector3d<long>) == 0xC);

template <typename t_element>
inline t_element dot_product(s_vector3d<t_element>* u, s_vector3d<t_element>* v) {
	return u->i*v->i + u->j * v->j + u->k * v->k;
}

template <typename t_element>
inline s_vector3d<t_element>* cross_product(s_vector3d<t_element>* u, s_vector3d<t_element>* v, s_vector3d<t_element>* result) {
	result->i = u->j*v->k - u->k*v->j;
	result->j = u->k*v->i - u->i*v->k;
	result->k = u->i*v->j - u->j*v->i;
	return result;
}

template <typename t_element>
inline void inverse_sign(s_vector3d<t_element>* u) {
	u->i = -u->i;
	u->j = -u->j;
	u->k = -u->k;
}