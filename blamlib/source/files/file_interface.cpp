#include <files/file_interface.h>

/* ---------- code */

void file_invalidate(
	s_file_accessor *file)
{
	assert(file);
	csmemset(file, 0, sizeof(s_file_accessor));
	// TODO: finish
}

bool file_valid(
	s_file_accessor *file)
{
	return file && file->handle && file->handle != (void *)NONE;
}
