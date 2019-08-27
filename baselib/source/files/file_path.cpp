#include <files/file_path.h>

/* ---------- code */

c_file_path::c_file_path() :
	m_filename(),
	m_location(),
	m_flags()
{
}

void c_file_path::clear()
{
	initialize(k_file_location_invalid);
}

void c_file_path::initialize(
	e_file_location location)
{
	assert(location == k_file_location_invalid || VALID_INDEX(location, k_file_location_count));
	m_filename.clear();
	m_location = location;
	m_flags.clear();
}

void c_file_path::set_root(
	e_file_location location)
{
	assert(VALID_INDEX(location, k_file_location_count));

	initialize(location);
}

void c_file_path::set_file_path(
	e_file_location location,
	char const *path)
{
	assert(VALID_INDEX(location, k_file_location_count));
	assert(path);

	initialize(location);
	set_filename(path);
}

void c_file_path::set_directory_path(
	e_file_location location,
	char const *path)
{
	assert(VALID_INDEX(location, k_file_location_count));
	assert(path);

	initialize(location);
	add_directory(path);
}

void c_file_path::copy(
	c_file_path *source)
{
	assert(source);

	csmemcpy(this, source, sizeof(c_file_path));
}

bool c_file_path::is_directory()
{
	return m_flags.test(_file_path_get_directory_bit);
}

bool c_file_path::is_equal(
	c_file_path *path)
{
	assert(path);

	if (m_location != path->m_location)
		return false;

	return csstrncmp(m_filename, path->get_filename_direct(), k_maximum_filename_length) == 0;
}

e_file_location c_file_path::get_location()
{
	return m_location;
}

char const *c_file_path::get_filename_direct() const
{
	return m_filename.get_string();
}

void c_file_path::add_directory(
	char const *directory)
{
	assert(directory);
	assert(!m_flags.test(_file_path_has_filename_bit));

	path_add_name(m_filename.get_buffer(), m_filename.max_length(), directory);
}

void c_file_path::remove_directory()
{
	assert(!m_flags.test(_file_path_has_filename_bit));

	path_remove_name(m_filename.get_buffer());
}

void c_file_path::set_filename(
	char const *name)
{
	assert(name);

	remove_filename();
	path_add_name(m_filename.get_buffer(), m_filename.max_length(), name);
	m_flags.set(_file_path_get_directory_bit, true);
}

void c_file_path::remove_filename()
{
	if (m_flags.test(_file_path_get_directory_bit))
	{
		path_remove_name(m_filename.get_buffer());
		m_flags.set(_file_path_get_directory_bit, false);
	}
}

char *c_file_path::get_full_path(
	char *out_name,
	unsigned long name_length)
{
	assert(out_name);
	assert(m_location == k_file_location_invalid || VALID_INDEX(m_location, k_file_location_count));

	char *root_absolute_path = file_location_get_root_absolute_path(m_location);
	csstrnzcpy(out_name, root_absolute_path, name_length);
	csstrnzcat(out_name, m_filename, name_length);

	return out_name;
}

char *c_file_path::get(
	c_flags<e_file_path_flags, unsigned long> const &path_flags,
	char *out_name,
	unsigned long name_length)
{
	static c_static_string<k_maximum_filename_length> temporary;

	assert(path_flags != 0);
	assert(
		!(
			(
				path_flags.test(_file_path_get_extension_bit) &&
				!path_flags.test(_file_path_get_filename_bit)
			) && (
				path_flags.test(_file_path_get_directory_bit) ||
				path_flags.test(_file_path_get_parent_directory_bit)
			)
		)
	);
	assert
	(
		!(
			path_flags.test(_file_path_get_directory_bit) &&
			path_flags.test(_file_path_get_parent_directory_bit)
		)
	);
	assert
	(
		!(
			path_flags.test(_file_path_get_location_relative_bit) &&
			!path_flags.test(_file_path_get_directory_bit) &&
			!path_flags.test(_file_path_get_parent_directory_bit)
		)
	);
	assert(out_name);
	assert(name_length <= k_maximum_filename_length);

	if (path_flags.test(_file_path_get_location_relative_bit))
		get_full_path(temporary);
	else
		temporary.set(m_filename.get_string());

	char *directory = nullptr;
	char *parent_directory = nullptr;
	char *filename = nullptr;
	char *extension = nullptr;

	path_split(
		temporary.get_buffer(),
		&directory, &parent_directory, &filename, &extension,
		m_flags.test(_file_path_get_directory_bit));

	csstrnzcpy(out_name, "", name_length);

	if (path_flags.test(_file_path_get_directory_bit))
		path_add_name(out_name, name_length, directory);

	if (path_flags.test(_file_path_get_parent_directory_bit))
		path_add_name(out_name, name_length, parent_directory);

	if (path_flags.test(_file_path_get_filename_bit))
		path_add_name(out_name, name_length, filename);

	if (path_flags.test(_file_path_get_extension_bit))
		path_add_extension(out_name, name_length, extension);

	return out_name;
}

char *c_file_path::path_add_name(
	char *path,
	unsigned long name_length,
	char const *name)
{
	static c_static_string<k_maximum_filename_length> temporary;

	assert(path);
	assert(name);

	if (*name == '\0')
		return nullptr;

	temporary.set(name);
	temporary.strip_leading('\\');
	temporary.strip_trailing('\\');
	temporary.replace('/', '\\');

	if (temporary.is_empty())
		return nullptr;

	unsigned int length = csstrnlen(path, name_length);

	if (length != 0 && (path[length - 1] != '\\'))
	{
		path[length++] = '\\';
		path[length] = '\0';
	}

	return csstrnzcpy(path + length, temporary.get_string(), name_length - length);
}

void c_file_path::path_remove_name(
	char *path)
{
	assert(path);

	if (*path == '\0')
		return;

	unsigned int length = csstrnlen(path, k_maximum_filename_length);
	unsigned int index = length < 2 ? 0 : length - 2;

	while (index > 0 && (path[index] != '\\'))
		path--;

	path[index] = '\0';
}

char *c_file_path::path_add_extension(
	char *path,
	unsigned long name_length,
	char const *extension)
{
	assert(path);
	assert(extension);

	if (*extension == '\0')
		return nullptr;

	unsigned int length = csstrnlen(path, name_length);

	if (length != 0)
	{
		path[length++] = '.';
		path[length] = '\0';
	}

	return csstrnzcpy(path + length, extension, name_length - length);
}

void c_file_path::path_split(
	char *path,
	char **out_directory,
	char **out_parent_directory,
	char **out_filename,
	char **out_extension,
	bool full)
{
	assert(path);
	assert(out_directory);
	assert(out_parent_directory);
	assert(out_filename);
	assert(out_extension);

	unsigned int index = csstrnlen(path, k_maximum_filename_length);
	*out_directory = *out_parent_directory = *out_filename = *out_extension = path + index;

	while (index > 0)
	{
		switch (path[index])
		{
		case '.':
			if (full && **out_filename == '\0' && **out_extension == '\0')
			{
				path[index] = '\0';
				*out_extension = path + index + 1;
			}
			break;

		case '\\':
			if (!full || **out_filename != '\0')
			{
				if (**out_directory == '\0')
					*out_parent_directory = path + index + 1;
			}
			else
			{
				path[index] = '\0';
				*out_filename = path + index + 1;
			}
			break;
		}

		index--;
	}

	if (full && **out_filename == '\0')
		*out_filename = path;

	if (*out_filename != path)
		*out_directory = path;
}
