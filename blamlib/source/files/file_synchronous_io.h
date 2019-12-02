#pragma once

#include <cseries/cseries.h>
#include <datatypes/flags.h>
#include <files/file_interface.h>
#include <files/file_path.h>

/* ---------- types */

enum e_file_open_flags
{
	_file_open_read_bit,
	_file_open_write_bit,
	_file_open_write_append_bit,
	_file_open_write_allow_read_bit,
	_file_open_write_shared_bit,
	_file_open_temporary_bit,
	_file_open_delete_on_close_bit,
	_file_open_random_access_bit,
	_file_open_sequential_scan_bit,
	k_number_of_file_open_flags
};

enum e_file_open_result
{
	// TODO
	k_number_of_file_open_results
};

/* ---------- prototypes/FILE_SYNCHRONOUS_IO.CPP */

ulong file_get_position(
	s_file_accessor *file);

/* TODO:
file_read_from_position
file_write_to_position
file_print
file_printf
file_vprintf
*/

/* ---------- prototypes/FILE_SYNCHRONOUS_IO_WINDOWS.CPP */

void file_open(
	c_file_path *path,
	c_flags<e_file_open_flags, ulong, k_number_of_file_open_flags> flags,
	e_file_error_mode error_mode,
	s_file_accessor *out_file);

bool file_close(
	s_file_accessor *file);

bool file_get_read_only(
	s_file_accessor *file);

bool file_set_position(
	s_file_accessor *file,
	uint position,
	e_file_error_mode error_mode);

bool file_set_position_eof(
	s_file_accessor *file);

uint file_get_eof(
	s_file_accessor *file);

bool file_set_eof(
	s_file_accessor *file,
	uint position);

bool file_at_eof(
	s_file_accessor *file);

bool file_flush(
	s_file_accessor *file);

bool file_read(
	s_file_accessor *file,
	uint count,
	e_file_error_mode error_mode,
	void *buffer);

bool file_write(
	s_file_accessor *file,
	uint count,
	e_file_error_mode error_mode,
	void *buffer);
