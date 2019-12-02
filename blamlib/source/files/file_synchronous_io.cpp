#include <files/file_synchronous_io.h>

/* ---------- code */

ulong file_get_position(
	s_file_accessor *file)
{
	return file->position;
}

//
// TODO
//
