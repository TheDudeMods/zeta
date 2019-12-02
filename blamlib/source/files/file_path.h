#pragma once

#include <cseries/cseries.h>
#include <datatypes/enum.h>
#include <datatypes/flags.h>
#include <datatypes/static_string.h>
#include <files/file_interface.h>
#include <files/file_location_manager.h>

/* ---------- types */

enum e_file_path_flags
{
	_file_path_get_directory_bit,
	_file_path_get_parent_directory_bit,
	_file_path_get_filename_bit,
	_file_path_get_extension_bit,
	_file_path_get_location_relative_bit,
	_file_path_has_filename_bit,
	k_number_of_file_path_flags
};

/* ---------- classes */

class c_file_path final
{
private:
	c_static_string<k_maximum_filename_length> m_filename;
	c_enum<e_file_location, long> m_location;
	c_flags<e_file_path_flags, ulong> m_flags;

public:
	c_file_path();

	void clear();
	void initialize(e_file_location location);

	void set_root(e_file_location location);
	void set_file_path(e_file_location location, char const *path);
	void set_directory_path(e_file_location location, char const *path);

	void copy(c_file_path *source);

	bool is_directory();
	bool is_equal(c_file_path *path);

	e_file_location get_location();

	char const *get_filename_direct() const;

	void add_directory(char const *directory);
	void remove_directory();

	void set_filename(char const *name);
	void remove_filename();

	char *get_full_path(char *out_name, unsigned long name_length);

	template <unsigned long const k_length>
	char *get_full_path(char(&path)[k_length])
	{
		return get_full_path(path, k_length);
	}

	template <unsigned long const k_length>
	char *get_full_path(c_static_string<k_length> &m_string)
	{
		return get_full_path(m_string.get_buffer(), c_static_string<k_length>::max_length());
	}

	char *get(c_flags<e_file_path_flags, unsigned long> const &path_flags, char *out_name, unsigned long name_length);

	char *path_add_name(char *path, unsigned long name_length, char const *name);
	void path_remove_name(char *path);

	char *path_add_extension(char *path, unsigned long name_length, char const *extension);

	void path_split(char *path,
		char **out_directory,
		char **out_parent_directory,
		char **out_filename,
		char **out_extension,
		bool full);
};
