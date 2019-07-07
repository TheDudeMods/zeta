/*
CACHE_FILES.CPP
*/

#include <cache/cache_files.h>

/* ---------- code */

c_cache_file::c_cache_file() :
	m_buffer(nullptr)
{
}

c_cache_file::c_cache_file(char const *path) :
	c_cache_file()
{
	auto stream = fopen(path, "rb+");
	fseek(stream, 0, SEEK_END);

	auto length = ftell(stream);
	m_buffer = new char[length];

	fseek(stream, 0, SEEK_SET);
	fread(m_buffer, length, 1, stream);
}

c_cache_file::c_cache_file(c_cache_file const &file) :
	m_buffer(file.m_buffer)
{
}

c_cache_file::~c_cache_file()
{
	delete[] m_buffer;
}
