/*
CACHE_FILES.CPP
*/

#include <cache/cache_files.h>

/* ---------- code */

c_cache_file_header::c_cache_file_header() :
	c_cache_file_header(nullptr)
{
}

c_cache_file_header::c_cache_file_header(s_cache_file_header *const &header) :
	m_header(header)
{
}

c_cache_file_header::c_cache_file_header(c_cache_file_header const &header) :
	c_cache_file_header(header.m_header)
{
}

c_cache_tag_index::c_cache_tag_index() :
	c_cache_tag_index(nullptr)
{
}

c_cache_tag_index::c_cache_tag_index(s_cache_tag_index *const &index) :
	m_index(index)
{
}

c_cache_tag_index::c_cache_tag_index(c_cache_tag_index const &index) :
	c_cache_tag_index(index.m_index)
{
}

c_cache_tag_instance::c_cache_tag_instance() :
	c_cache_tag_instance(nullptr)
{
}

c_cache_tag_instance::c_cache_tag_instance(s_cache_tag_instance *const &instance) :
	m_instance(instance)
{
}

c_cache_tag_instance::c_cache_tag_instance(c_cache_tag_instance const &instance) :
	c_cache_tag_instance(instance.m_instance)
{
}

c_cache_file::c_cache_file() :
	m_buffer(nullptr)
{
}

c_cache_file::c_cache_file(char const *path) :
	c_cache_file()
{
	// TODO: load
}

c_cache_file::c_cache_file(c_cache_file const &file) :
	m_buffer(file.m_buffer)
{
}
