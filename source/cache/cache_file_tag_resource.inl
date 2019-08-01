#pragma once

#include <cseries/cseries.h>

template <typename t_definition>
class c_cache_file_tag_resource
{
private:
	t_definition *m_definition;
	byte *m_data;
	long m_data_length;
	bool m_should_delete;

public:
	c_cache_file_tag_resource(t_definition *definition, void *data, long data_length, bool should_delete) :
		m_definition(definition),
		m_data((byte *)data),
		m_data_length(data_length),
		m_should_delete(should_delete)
	{
	}

	c_cache_file_tag_resource(long resource_index) :
		c_cache_file_tag_resource(nullptr, nullptr, NONE, true)
	{
		m_definition = g_cache_file->tag_resource_definition_get<t_definition>(resource_index);

		if (!g_cache_file->tag_resource_try_and_get(resource_index, &m_data_length, (void **)&m_data))
		{
			m_data = nullptr;
			m_data_length = NONE;
		}
	}

	~c_cache_file_tag_resource()
	{
		if (m_should_delete && m_data)
			delete[] m_data;
	}

	t_definition *get_definition()
	{
		return m_definition;
	}

	void *get_data(dword address)
	{
		switch ((address >> 28) & 0xF)
		{
		case 4: // points to compressed data
			return (char *)m_data + (address & 0x0FFFFFFF);

		default: // points to definition data
			bool negative = ((address >> 27) & 1) != 0;
			long offset = address & 0x07FFFFFF;
			return (char *)m_definition + (negative ? -offset : offset);
		}
	}

	template <typename t_type>
	t_type *get_data(dword address)
	{
		return (t_type *)get_data(address);
	}

	t_definition *operator->()
	{
		return get_definition();
	}
};
