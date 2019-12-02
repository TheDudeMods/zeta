#pragma once

#include <cseries/cseries.h>
#include <datatypes/enum.h>
#include <datatypes/static_string.h>
#include <files/file_location_manager.h>

/* ---------- constants */

enum
{
	k_maximum_filename_length = 256
};

/* ---------- enumerators */

enum e_file_error_mode
{
	_file_error_mode_none,
	_file_error_mode_invalid_pointer,
	k_file_error_mode_count
};

/* ---------- structures */

struct s_file_accessor
{
	void *handle;
	c_enum<e_file_location, long> location;
	ulong position;
	c_static_string<k_maximum_filename_length> path;
};

/* ---------- prototypes/FILE_INTERFACE.CPP */

void file_invalidate(s_file_accessor *file);
bool file_valid(s_file_accessor *file);
