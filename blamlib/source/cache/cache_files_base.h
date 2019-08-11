#pragma once

#include <cseries/cseries.h>

/* ---------- classes */

class c_cache_file
{
public:
	c_cache_file(char const *filename);

	char const *get_filename();

protected:
	char const *m_filename;
};
