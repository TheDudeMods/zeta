#pragma once

#include <cseries/cseries.h>
#include <datatypes/static_array.h>

/* ---------- types */

enum e_file_location
{
	k_file_location_invalid = -1,
	_file_location_absolute,
	_file_location_application_relative,
	// TODO: add more
	k_file_location_count
};

enum e_file_location_usage_mode
{
	_file_location_read,
	// TODO
	k_file_location_usage_mode_count
};

struct s_file_location
{
	// TODO
};

struct s_file_location_globals
{
	// TODO
	c_static_array<s_file_location, k_file_location_count> file_locations;
};

/* ---------- globals */

extern s_file_location_globals g_file_location_globals;

/* ---------- prototypes/FILE_LOCATION_MANAGER.CPP */

/* TODO:
file_locations_initialize
file_location_globals_get
file_location_available
file_location_get_device_type
*/

char *file_location_get_root_absolute_path(
	e_file_location file_location);

/* TODO:
file_locations_configure
*/

/* ---------- prototypes/FILE_LOCATION_MANAGER_WINDOWS.CPP */
