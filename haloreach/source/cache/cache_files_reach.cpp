/*
CACHE_FILES_REACH.CPP
*/

#include <cache/cache_files_reach.h>

/* ---------- code */

c_cache_file_header_reach::c_cache_file_header_reach(
	c_cache_file_reach *file,
	s_cache_file_header_reach *header) :
		m_file(file),
		m_header(header)
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

qword c_cache_file_header_reach::get_tags_header_address() const
{
	return qword(((s_cache_file_header_reach *)m_header)->tags_header_address);
}

void c_cache_file_header_reach::set_tags_header_address(qword address)
{
	((s_cache_file_header_reach *)m_header)->tags_header_address = address;
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

c_cache_file_tags_header_reach::c_cache_file_tags_header_reach(
	c_cache_file_reach *file,
	s_cache_file_tags_header_reach *tags_header) :
	m_file(file),
	m_tags_header(tags_header)
{
	m_tag_groups = new c_tag_group_v2 *[tags_header->group_count];
	m_tag_instances = new c_cache_file_tag_instance_reach *[tags_header->tag_count];

	auto tag_groups = (s_tag_group_v2 *)(file->m_buffer + (tags_header->groups_address + file->get_base_address()));

	for (auto i = 0; i < tags_header->group_count; i++)
		m_tag_groups[i] = new c_tag_group_v2(&tag_groups[i]);

	auto tag_instances = (s_cache_file_tag_instance_reach *)(file->m_buffer + (tags_header->tags_address + file->get_base_address()));

	for (auto i = 0; i < tags_header->tag_count; i++)
		m_tag_instances[i] = new c_cache_file_tag_instance_reach(file, &tag_instances[i], i);
}

c_cache_file_tags_header_reach::~c_cache_file_tags_header_reach()
{
	for (auto i = 0; i < m_tags_header->group_count; i++)
		delete m_tag_groups[i];

	delete[] m_tag_groups;

	for (auto i = 0; i < m_tags_header->tag_count; i++)
		delete m_tag_instances[i];

	delete[] m_tag_instances;
}

c_tag_group *c_cache_file_tags_header_reach::get_tag_group(long index)
{
	return m_tag_groups[index];
}

c_cache_file_tag_instance *c_cache_file_tags_header_reach::get_tag_instance(long index)
{
	return m_tag_instances[index];
}

c_cache_file_tag_instance_reach::c_cache_file_tag_instance_reach(
	c_cache_file_reach *file,
	s_cache_file_tag_instance_reach *instance,
	long index) :
	m_file(file),
	m_instance(instance),
	m_index(index)
{
}

c_tag_group *c_cache_file_tag_instance_reach::get_group()
{
	return m_file->get_tags_header().get_tag_group(m_instance->group_index);
}

dword c_cache_file_tag_instance_reach::get_offset()
{
	return (m_instance->address * 4) - m_file->get_address_mask();
}

char const *c_cache_file_tag_instance_reach::get_name()
{
	// TODO:
	return nullptr;
}

long c_cache_file_tag_instance_reach::get_index()
{
	return m_index;
}

c_cache_file_reach::c_cache_file_reach(char const *path) :
	c_cache_file(path)
{
	m_header = new c_cache_file_header_reach(this,
		(s_cache_file_header_reach *)&m_buffer[0]);

	m_tags_header = new c_cache_file_tags_header_reach(this,
		(s_cache_file_tags_header_reach *)&m_buffer[m_header->get_tags_header_address() + get_base_address()]);
}

c_cache_file_reach::~c_cache_file_reach()
{
	delete m_header;
	delete m_tags_header;
}

dword c_cache_file_reach::get_address_mask() const
{
	return (dword)(m_header->m_header->virtual_base_address - (qword)m_header->get_memory_buffer_offset() - 0x10000000);
}

qword c_cache_file_reach::get_base_address() const
{
	return (qword)m_header->get_memory_buffer_offset() - m_header->m_header->virtual_base_address;
}

c_cache_file_header &c_cache_file_reach::get_header()
{
	return *m_header;
}

c_cache_file_tags_header &c_cache_file_reach::get_tags_header()
{
	return *m_tags_header;
}
