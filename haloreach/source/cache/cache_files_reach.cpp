/*
CACHE_FILES_REACH.CPP
*/

#include <cache/cache_files_reach.h>

/* ---------- code */

c_cache_file_header_reach::c_cache_file_header_reach() :
	c_cache_file_header()
{
}

c_cache_file_header_reach::c_cache_file_header_reach(s_cache_file_header *const &header) :
	c_cache_file_header(header)
{
}

c_cache_file_header_reach::c_cache_file_header_reach(c_cache_file_header_reach const &header) :
	c_cache_file_header(header)
{
}

long c_cache_file_header_reach::get_file_version() const
{
	return ((s_cache_file_header_reach *)m_header)->file_version;
}

void c_cache_file_header_reach::set_file_version(long version)
{
	((s_cache_file_header_reach *)m_header)->file_version = version;
}

long c_cache_file_header_reach::get_file_length() const
{
	return ((s_cache_file_header_reach *)m_header)->file_length;
}

void c_cache_file_header_reach::set_file_length(long length)
{
	((s_cache_file_header_reach *)m_header)->file_length = length;
}

s_ptr64<s_cache_tag_index> c_cache_file_header_reach::get_tag_index_address() const
{
	return s_ptr64<s_cache_tag_index>(((s_cache_file_header_reach *)m_header)->tag_index_address.value);
}

void c_cache_file_header_reach::set_tag_index_address(s_ptr64<s_cache_tag_index> address)
{
	((s_cache_file_header_reach *)m_header)->tag_index_address.value = address.value;
}

long c_cache_file_header_reach::get_memory_buffer_offset() const
{
	return ((s_cache_file_header_reach *)m_header)->memory_buffer_offset;
}

void c_cache_file_header_reach::set_memory_buffer_offset(long offset)
{
	((s_cache_file_header_reach *)m_header)->memory_buffer_offset = offset;
}

long c_cache_file_header_reach::get_memory_buffer_size() const
{
	return ((s_cache_file_header_reach *)m_header)->memory_buffer_size;
}

void c_cache_file_header_reach::set_memory_buffer_size(long size)
{
	((s_cache_file_header_reach *)m_header)->memory_buffer_size = size;
}

char const *c_cache_file_header_reach::get_build_name() const
{
	return ((s_cache_file_header_reach *)m_header)->build.ascii;
}

void c_cache_file_header_reach::set_build_name(char const *name)
{
	memset(((s_cache_file_header_reach *)m_header)->build.ascii, 0, k_maximum_short_string_ascii_length);
	strcpy_s(((s_cache_file_header_reach *)m_header)->build.ascii, name);
}

e_scenario_type c_cache_file_header_reach::get_scenario_type() const
{
	return ((s_cache_file_header_reach *)m_header)->scenario_type.operator e_scenario_type();
}

void c_cache_file_header_reach::set_scenario_type(e_scenario_type const &type)
{
	((s_cache_file_header_reach *)m_header)->scenario_type = type;
}

e_scenario_load_type c_cache_file_header_reach::get_scenario_load_type() const
{
	return ((s_cache_file_header_reach *)m_header)->load_type;
}

void c_cache_file_header_reach::set_scenario_load_type(e_scenario_load_type const &type)
{
	((s_cache_file_header_reach *)m_header)->load_type = type;
}

char const *c_cache_file_header_reach::get_name() const
{
	return ((s_cache_file_header_reach *)m_header)->name.ascii;
}

void c_cache_file_header_reach::set_name(char const *name)
{
	memset(((s_cache_file_header_reach *)m_header)->name.ascii, 0, k_maximum_short_string_ascii_length);
	strcpy_s(((s_cache_file_header_reach *)m_header)->name.ascii, name);
}

s_ptr64<void> c_cache_file_header_reach::get_virtual_base_address() const
{
	return ((s_cache_file_header_reach *)m_header)->virtual_base_address;
}

void c_cache_file_header_reach::set_virtual_base_address(s_ptr64<void> const &address)
{
	((s_cache_file_header_reach *)m_header)->virtual_base_address = address;
}

c_cache_file_reach::c_cache_file_reach() :
	c_cache_file()
{
}

c_cache_file_reach::c_cache_file_reach(char const *path) :
	c_cache_file(path)
{
	m_header = c_cache_file_header_reach((s_cache_file_header *)&m_buffer[0]);
	//m_tag_index = c_cache_tag_index_reach((s_cache_tag_index *)&m_buffer[m_header.get_tag_index_address().value]);
}

c_cache_file_reach::c_cache_file_reach(c_cache_file_reach const &file) :
	c_cache_file(file)
{
}

dword c_cache_file_reach::get_magic32() const
{
	return (dword)(m_header.get_virtual_base_address().value - (qword)m_header.get_memory_buffer_offset() - 0x10000000);
}

qword c_cache_file_reach::get_magic64() const
{
	return (qword)m_header.get_memory_buffer_offset() - m_header.get_virtual_base_address().value;
}

c_cache_file_header &c_cache_file_reach::get_header()
{
	return m_header;
}

c_cache_tag_index &c_cache_file_reach::get_tag_index()
{
	return m_tag_index;
}

c_cache_tag_instance c_cache_file_reach::get_tag_instance(long index)
{
	return c_cache_tag_instance();
}
