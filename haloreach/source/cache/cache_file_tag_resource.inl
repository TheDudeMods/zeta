#pragma once

#include <cseries/cseries.h>

template <typename t_definition>
class c_cache_file_reach_tag_resource
{
private:
	c_cache_file_reach *m_file;
	t_definition *m_definition;
	uchar *m_data;
	long m_data_length;
	bool m_should_delete;

public:
	c_cache_file_reach_tag_resource(c_cache_file_reach *file, t_definition *definition, void *data, long data_length, bool should_delete) :
		m_file(file),
		m_definition(definition),
		m_data((uchar *)data),
		m_data_length(data_length),
		m_should_delete(should_delete)
	{
	}

	c_cache_file_reach_tag_resource(c_cache_file_reach *file, long resource_index) :
		c_cache_file_reach_tag_resource(file, nullptr, nullptr, NONE, true)
	{
		m_definition = m_file->tag_resource_definition_get<t_definition>(resource_index);

		if (!m_file->tag_resource_try_and_get(resource_index, &m_data_length, (void **)&m_data))
		{
			m_data = nullptr;
			m_data_length = NONE;
		}
	}

	~c_cache_file_reach_tag_resource()
	{
		if (m_should_delete && m_data)
			delete[] m_data;
	}

	t_definition *get_definition()
	{
		return m_definition;
	}

	long get_data_length()
	{
		return m_data_length;
	}

	void *get_data(ulong address = 0)
	{
		if (!address)
			return m_data;

		auto type = (address >> 28) & 0xF;

		switch (type)
		{
		case 4: // points to compressed data
		{
			long data_offset = (address & 0x0FFFFFFF);
			return (char *)m_data + data_offset;
		}

		default: // points to definition data
		{
			bool negative = ((address >> 27) & 1) != 0;
			long offset = address & 0x07FFFFFF;
			return (char *)m_definition + (negative ? -offset : offset);
		}
		}
	}

	template <typename t_type>
	t_type *get_data(ulong address)
	{
		return (t_type *)get_data(address);
	}

	t_definition *operator->()
	{
		return get_definition();
	}
};
