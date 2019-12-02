#pragma once

/* ---------- types */

enum e_file_overwrite_mode
{
	// TODO
	k_number_of_file_overwrite_modes
};

enum e_find_file_flags
{
	// TODO
	k_number_of_find_file_flags
};

struct s_find_files_data
{
	// TODO
};

/* ---------- prototypes/FILE_SYNCHRONOUS_UTILITIES.CPP */

/* TODO:
file_is_readable
file_create_parent_directories
file_read_into_memory
file_read_into_buffer
file_trim
file_trim_fast
directory_create_and_delete_contents
directory_create_recursive
directory_copy_recursive
find_files
*/

/* ---------- prototypes/FILE_SYNCHRONOUS_UTILITIES_WINDOWS.CPP */

/* TODO:
file_exists
file_is_read_only
file_set_read_only
file_get_size
file_create
file_delete
file_rename
file_copy
file_move
file_build_temporary_path
directory_exists
directory_create
directory_delete_recursive
directory_rename
directory_move
find_files_start
find_files_end
find_files_next
*/
