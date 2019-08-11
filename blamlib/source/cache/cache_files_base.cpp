#include <cache/cache_files_base.h>

/* ---------- code */

c_cache_file::c_cache_file(char const *filename) :
	m_filename(filename)
{
}

char const *c_cache_file::get_filename()
{
	return m_filename;
}
