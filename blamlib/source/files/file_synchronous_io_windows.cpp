#include <files/file_synchronous_io.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

/* ---------- code */

void file_open(
	c_file_path *path,
	c_flags<e_file_open_flags, ulong, k_number_of_file_open_flags> flags,
	e_file_error_mode error_mode,
	s_file_accessor *out_file)
{
	assert(path);
	assert(flags.valid());
	assert(flags.test(_file_open_read_bit) || flags.test(_file_open_write_bit));
	assert(flags.test(_file_open_write_bit) || !flags.test(_file_open_write_append_bit));
	assert(flags.test(_file_open_write_bit) || !flags.test(_file_open_write_allow_read_bit));
	assert(!(flags.test(_file_open_random_access_bit) && flags.test(_file_open_sequential_scan_bit)));
	assert(VALID_INDEX(error_mode, k_file_error_mode_count));
	assert(out_file);

	file_invalidate(out_file);
	
	c_static_string<k_maximum_filename_length> file_path;
	path->get_full_path<k_maximum_filename_length>(file_path);

	auto read_flags = flags.test(_file_open_read_bit) ? GENERIC_READ : 0;
	auto write_flags = flags.test(_file_open_write_bit) ? GENERIC_WRITE : 0;
	auto share_mode =
		(!flags.test(_file_open_write_bit) || flags.test(_file_open_write_allow_read_bit)) ? FILE_SHARE_READ :
		(flags.test(_file_open_write_shared_bit) ? FILE_SHARE_WRITE : 0);
	auto temporary_flags = flags.test(_file_open_temporary_bit) ? FILE_ATTRIBUTE_TEMPORARY : 0;
	auto delete_flags = flags.test(_file_open_delete_on_close_bit) ? FILE_FLAG_DELETE_ON_CLOSE : 0;
	auto access_flags = flags.test(_file_open_random_access_bit) ? FILE_FLAG_RANDOM_ACCESS : 0;
	auto sequential_flags = flags.test(_file_open_sequential_scan_bit) ? FILE_FLAG_SEQUENTIAL_SCAN : 0;

	auto file = CreateFile(
		file_path,
		read_flags | write_flags,
		share_mode,
		nullptr,
		OPEN_EXISTING,
		temporary_flags | delete_flags | access_flags | sequential_flags,
		nullptr);

	if (file != nullptr && file != INVALID_HANDLE_VALUE)
	{
		out_file->handle = file;
		out_file->location = path->get_location();
		out_file->position = 0;
		out_file->path.set(file_path);
	}
	else
	{
		// TODO: errors
	}

	// TODO: finish
}

bool file_close(
	s_file_accessor *file)
{
	assert(file_valid(file));

	if (!CloseHandle(file->handle))
	{
		// TODO: file_error(__FUNCTION__, _file_error_mode_none, file);
		return false;
	}

	file_invalidate(file);

	return true;
}

bool file_get_read_only(
	s_file_accessor *file)
{
	assert(file_valid(file));

	BY_HANDLE_FILE_INFORMATION file_information;
	
	if (!GetFileInformationByHandle(file->handle, &file_information))
	{
		// TODO: file_error(__FUNCTION__, _file_error_mode_none, file);
		return false;
	}

	return file_information.dwFileAttributes & FILE_ATTRIBUTE_READONLY;
}

bool file_set_position(
	s_file_accessor *file,
	uint position,
	e_file_error_mode error_mode)
{
	assert(file_valid(file));

	if (file->position == position)
		return true;

	file->position = SetFilePointer(file->handle, position, nullptr, FILE_BEGIN);

	if (file->position == INVALID_SET_FILE_POINTER)
	{
		// TODO: file_error(__FUNCTION__, error_mode, file);
		return false;
	}

	return true;
}

bool file_set_position_eof(
	s_file_accessor *file)
{
	assert(file_valid(file));

	file->position = SetFilePointer(file->handle, 0, nullptr, FILE_END);

	if (file->position == INVALID_SET_FILE_POINTER)
	{
		// TODO: file_error(__FUNCTION__, _file_error_mode_none, file);
		return false;
	}

	return true;
}

uint file_get_eof(
	s_file_accessor *file)
{
	assert(file_valid(file));

	auto result = GetFileSize(file->handle, nullptr);

	if (result == INVALID_FILE_SIZE)
	{
		// TODO: file_error(__FUNCTION__, _file_error_mode_none, file);
		return NONE;
	}

	return result;
}

bool file_set_eof(
	s_file_accessor *file,
	uint position)
{
	if (!file_set_position(file, position, _file_error_mode_none))
	{
		// TODO: file_error(__FUNCTION__, _file_error_mode_none, file);
		return false;
	}

	return SetEndOfFile(file->handle);
}

bool file_at_eof(
	s_file_accessor *file)
{
	return file_get_eof(file) == file->position;
}

bool file_flush(
	s_file_accessor *file)
{
	assert(file_valid(file));

	if (!FlushFileBuffers(file->handle))
	{
		// TODO: file_error(__FUNCTION__, _file_error_mode_none, file);
		return false;
	}

	return true;
}

bool file_read(
	s_file_accessor *file,
	uint count,
	e_file_error_mode error_mode,
	void *buffer)
{
	assert(count > 0 && count <= k_uint32_max);
	assert(buffer);
	assert(file_valid(file));

	ulong bytes_read = 0;
	if (!ReadFile(file->handle, buffer, count, &bytes_read, nullptr))
	{
		// TODO: file_error(__FUNCTION__, error_mode, file);
		return false;
	}

	return true;
}

bool file_write(
	s_file_accessor *file,
	uint count,
	e_file_error_mode error_mode,
	void *buffer)
{
	assert(count > 0 && count <= k_uint32_max);
	assert(buffer);
	assert(file_valid(file));

	ulong bytes_written = 0;
	if (!WriteFile(file->handle, buffer, count, &bytes_written, nullptr))
	{
		// TODO: file_error(__FUNCTION__, error_mode, file);
		return false;
	}

	return false;
}
