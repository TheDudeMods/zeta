#pragma once

/* ---------- is_base_of

Example:
	
	class c_class1 { };

	class c_class2 : public class1 { };

	static_assert(is_base_of<c_class1, c_class2>);

*/

template <typename t_base, typename t_derived>
constexpr bool is_base_of = __is_base_of(t_base, t_derived);

/* ---------- is_template_of

Example:

	template <typename t_element>
	class c_container { };

	static_assert(is_template_of<c_container, c_container<int>>);

*/

template <template <typename...> typename t_template_type, typename t_type>
constexpr bool is_template_of = false;

template <template <typename...> typename t_template_type, typename... t_types>
constexpr bool is_template_of<t_template_type, t_template_type<t_types...>> = true;

/* ---------- is_ranged_template_of

Example:
	
	template <typename t_element, long const k_maximum_count>
	class c_static_container { };

	static_assert(is_ranged_template_of<c_static_container, c_static_container<int, 32>>);

*/

template <template <typename, long const> typename t_template_type, typename t_type>
constexpr bool is_ranged_template_of = false;

template <template <typename, long const> typename t_template_type, typename t_type, long const k_value>
constexpr bool is_ranged_template_of<t_template_type, t_template_type<t_type, k_value>> = true;