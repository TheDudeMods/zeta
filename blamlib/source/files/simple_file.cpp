#include <files/simple_file.h>

/* ---------- code */

c_simple_file::c_simple_file()
{
}

c_simple_file::c_simple_file(char const *filename)
{
}

c_simple_file::c_simple_file(c_file_path const *path)
{
}

c_simple_file::~c_simple_file()
{
}

e_file_error_mode c_simple_file::get_error_mode() const
{
	return e_file_error_mode();
}

bool c_simple_file::is_silent() const
{
	return false;
}

void c_simple_file::set_debug_filename(char const *name)
{
}

void c_simple_file::set_path(c_file_path const *path)
{
}

bool c_simple_file::open(c_flags<e_simple_file_open_flags, ulong> flags)
{
	return false;
}

void c_simple_file::close()
{
}

ulonglong c_simple_file::get_position()
{
	return ulonglong();
}

void c_simple_file::set_position(ulonglong position)
{
}

bool c_simple_file::set_position_eof()
{
	return false;
}

bool c_simple_file::at_eof()
{
	return false;
}

void c_simple_file::flush()
{
}
