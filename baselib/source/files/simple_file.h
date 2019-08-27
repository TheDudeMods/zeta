#pragma once

#include <cseries/cseries.h>
#include <datatypes/flags.h>
#include <files/file_path.h>
#include <files/file_synchronous_io.h>

/* ---------- types */

enum e_simple_file_open_flags
{
	_simple_file_open_text_bit,
	_simple_file_open_read_bit,
	_simple_file_open_write_bit,
	_simple_file_open_write_append_bit,
	_simple_file_open_write_allow_read_bit,
	k_number_of_simple_file_open_flags
};

/* ---------- classes */

class c_simple_file final
{
private:
	c_file_path m_file_path;
	void *m_file_handle;

public:
	c_simple_file();
	c_simple_file(char const *filename);
	c_simple_file(c_file_path const *path);
	~c_simple_file();

	e_file_error_mode get_error_mode() const;

	bool is_silent() const;

	void set_debug_filename(char const *name);
	
	void set_path(c_file_path const *path);

	bool open(c_flags<e_simple_file_open_flags, ulong> flags);
	void close();

	ulonglong get_position();
	void set_position(ulonglong position);
	bool set_position_eof();
	bool at_eof();

	void flush();

	//
	// TODO: finish
	//
};
