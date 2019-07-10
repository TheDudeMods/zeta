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
	return (s_cache_file_tags_header *)(m_header.tags_header_address + m_address_mask);
}

enum e_string_id_set
{
	_string_id_set_static_globals,
	_string_id_set_ui,
	_string_id_set_ui_alerts,
	_string_id_set_events,
	_string_id_set_ui_events,
	_string_id_set_widget_events,
	_string_id_set_widgets,
	_string_id_set_properties,
	_string_id_set_cui_events,
	_string_id_set_mp_events,
	_string_id_set_result_codes,
	_string_id_set_achievements,
	_string_id_set_default_formats,
	_string_id_set_engine_globals,
	_string_id_set_ai,
	_string_id_set_hud_message,
	k_number_of_string_id_sets
};

static long string_id_set_offsets[k_number_of_string_id_sets] =
{
	0x173B, 0x0, 0x4C8, 0xB2D, 0xC0A, 0xC70,
	0xD49, 0xD6F, 0xD74, 0x1433, 0x15A3,
	0x15B7, 0x1619, 0x1631, 0x163E, 0x1667
};

#define STRING_ID_INDEX(id) ((id) & ((1 << 17) - 1))
#define STRING_ID_SET(id) (((id) >> 17) & ((1 << 8) - 1))
#define STRING_ID_LENGTH(id) (((id) >> (17 + 8)) & ((1 << 7) - 1))

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

	if (id == 0x2015C)
		printf("");

	if (set == 0)
		index -= set_min;
	else
		index += set_min;

	return m_string_ids_buffer + m_string_id_indices[index + string_id_set_offsets[set]];
}

char const *c_cache_file::get_tag_name(long index) const
{
	return m_tag_names_buffer + m_tag_name_indices[index];
}

s_tag_group *c_cache_file::get_tag_group(long index)
{
	auto groups = (s_tag_group *)(get_tags_header()->groups_address + m_address_mask);
	return &groups[index];
}

s_cache_file_tag_instance *c_cache_file::get_tag_instance(long index)
{
	auto instances = (s_cache_file_tag_instance *)(get_tags_header()->tags_address + m_address_mask);
	return &instances[index];
}
