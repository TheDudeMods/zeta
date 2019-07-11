#include <cache/cache_files.h>

/* ---------- code */

c_cache_file::c_cache_file(char const *filename) :
	m_filename(filename),
	m_address_mask(0),
	m_header(),
	m_memory_buffer(nullptr),
	m_string_id_indices(nullptr),
	m_string_ids_buffer(nullptr),
	m_tag_name_indices(nullptr),
	m_tag_names_buffer(nullptr)
{
	FILE *stream = nullptr;
	fopen_s(&stream, filename, "rb+");

	//
	// Read the cache file header
	//

	fseek(stream, 0, SEEK_SET);
	fread(&m_header, sizeof(s_cache_file_header), 1, stream);

	//
	// Allocate and read the cache file memory buffer
	//

	m_memory_buffer = new char[m_header.memory_buffer_size];

	fseek(stream, m_header.memory_buffer_offset, SEEK_SET);
	fread(m_memory_buffer, m_header.memory_buffer_size, 1, stream);

	m_address_mask = ((qword)m_memory_buffer - m_header.virtual_base_address);

	//
	// Allocate and read the cache file string ids
	//

	m_string_id_indices = new long[m_header.string_id_count];

	fseek(stream, m_header.string_id_indices_offset, SEEK_SET);
	fread(m_string_id_indices, sizeof(long), m_header.string_id_count, stream);

	m_string_ids_buffer = new char[m_header.string_ids_buffer_size];

	fseek(stream, m_header.string_ids_buffer_offset, SEEK_SET);
	fread(m_string_ids_buffer, m_header.string_ids_buffer_size, 1, stream);

	//
	// Allocate and read the cache file tag names
	//

	m_tag_name_indices = new long[m_header.tag_name_count];

	fseek(stream, m_header.tag_name_indices_offset, SEEK_SET);
	fread(m_tag_name_indices, sizeof(long), m_header.tag_name_count, stream);

	m_tag_names_buffer = new char[m_header.tag_names_buffer_size];

	fseek(stream, m_header.tag_names_buffer_offset, SEEK_SET);
	fread(m_tag_names_buffer, m_header.tag_names_buffer_size, 1, stream);

	//
	// Close the file stream
	//

	fclose(stream);
}

c_cache_file::~c_cache_file()
{
	if (m_tag_names_buffer) delete[] m_tag_names_buffer;
	if (m_tag_name_indices) delete[] m_tag_name_indices;
	if (m_string_ids_buffer) delete[] m_string_ids_buffer;
	if (m_string_id_indices) delete[] m_string_id_indices;
	if (m_memory_buffer) delete[] m_memory_buffer;
}

s_cache_file_tags_header *c_cache_file::get_tags_header()
{
	return get_buffer_data<s_cache_file_tags_header>(m_header.tags_header_address);
}

char const *c_cache_file::get_string(string_id id) const
{
	auto set_min = unsigned long(0x4C8);
	auto set_max = unsigned long(0xFFFF);
	auto set = STRING_ID_SET(id);
	auto index = STRING_ID_INDEX(id);

	if (set == 0 && (index < set_min || index > set_max))
		return m_string_ids_buffer + m_string_id_indices[index];

	if (set < 0 || set >= k_number_of_string_id_sets)
		return nullptr;

	if (set == 0)
		index -= set_min;
	else
		index += set_min;

	return m_string_ids_buffer + m_string_id_indices[index + k_string_id_set_offsets[set]];
}

char const *c_cache_file::get_tag_name(long index) const
{
	return m_tag_names_buffer + m_tag_name_indices[index];
}

s_tag_group *c_cache_file::get_tag_group(long index)
{
	return &get_buffer_data<s_tag_group>(get_tags_header()->groups_address)[index];
}

s_cache_file_tag_instance *c_cache_file::get_tag_instance(long index)
{
	return &get_buffer_data<s_cache_file_tag_instance>(get_tags_header()->tags_address)[index & 0xFFFF];
}
