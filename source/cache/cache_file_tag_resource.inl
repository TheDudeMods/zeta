#pragma once

#include <cseries/cseries.h>

template <typename t_definition>
class c_cache_file_tag_resource
{
private:
	t_definition *m_definition;
	void *m_data;

public:
	c_cache_file_tag_resource(t_definition *definition, void *data) :
		m_definition(definition),
		m_data(data)
	{
	}

	void *get_address(dword address)
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
};
