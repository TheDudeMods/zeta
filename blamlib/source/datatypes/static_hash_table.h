#pragma once

#include <cseries/cseries.h>
#include <datatypes/static_hash_table_data.h>

/* ---------- classes */

template <typename t_data, long const k_unknown1, long const k_unknown2, long const k_unknown3>
class c_static_hash_table
{
	static_assert(is_ranged_template_of<c_static_hash_table_data, t_data>);

private:
	t_data m_data;

public:
	c_static_hash_table() :
		m_data()
	{
	}

	long calculate_hash(t_data *data, long a1, long a2, long a3)
	{
		assert(data);

		long maximum_count = data->get_maximum_count();
		long unknown = a1 * k_unknown1 + a2 * k_unknown2 + a3 * k_unknown3;

		return unknown - (unknown / maximum_count) * maximum_count;
	}

	long find_new_hash_entry(t_data *data, long index)
	{
		// TODO
	}
};
