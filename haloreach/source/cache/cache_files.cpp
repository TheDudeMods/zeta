#include <cache/cache_files.h>
#include <datatypes/data_array.h>
#include <files/file_interface.h>
#include <files/file_synchronous_io.h>
#include <tag_files/string_ids.h>
#include <tag_files/tag_groups.h>

/* ---------- code */

bool s_cache_file_tag_group::is_in_group(tag group_tag) const
{
	if (group_tag == NONE)
		return true;

	return group_tags[0] == group_tag
		|| group_tags[1] == group_tag
		|| group_tags[2] == group_tag;
}

bool s_cache_file_tag_group::is_in_group(s_cache_file_tag_group &group) const
{
	return group_tags[0] == group.group_tags[0]
		|| group_tags[1] == group.group_tags[0]
		|| group_tags[2] == group.group_tags[0];
}

c_cache_file_reach::c_cache_file_reach(char const *filename) :
	c_cache_file(filename),
	m_header(),
	m_address_mask(0),
	m_memory_buffers()
{
	c_file_path path;
	path.set_filename(filename);

	s_file_accessor file;
	file_open(&path, FLAG(_file_open_read_bit), _file_error_mode_none, &file);

	//
	// Read the cache file header
	//

	file_set_position(&file, 0, _file_error_mode_none);
	file_read(&file, sizeof(s_cache_file_header), _file_error_mode_none, &m_header);

	//
	// Allocate and read the cache file sections
	//

	for (auto i = 0; i < k_number_of_cache_file_sections; i++)
	{
		auto section_offset = m_header.section_offsets[i] + m_header.section_bounds[i].offset;
		auto section_size = m_header.section_bounds[i].size;

		m_memory_buffers[i] = new char[section_size];

		file_set_position(&file, section_offset, _file_error_mode_none);
		file_read(&file, section_size, _file_error_mode_none, m_memory_buffers[i]);
	}

	m_address_mask = ((ulonglong)m_memory_buffers[_cache_file_section_tags] - m_header.virtual_base_address);

	assert(m_header.tag_post_link_buffer.empty()
		|| m_header.tag_post_link_buffer.end() == m_header.tag_language_dependent_read_only_buffer.begin());
	assert(m_header.tag_language_dependent_read_only_buffer.end() == m_header.tag_language_dependent_read_write_buffer.begin());
	assert(m_header.tag_language_dependent_read_write_buffer.end() == m_header.tag_language_neutral_read_write_buffer.begin());
	assert(m_header.tag_language_neutral_read_write_buffer.end() == m_header.tag_language_neutral_write_combined_buffer.begin());
	assert(m_header.tag_language_neutral_write_combined_buffer.end() == m_header.tag_language_neutral_read_only_buffer.begin());

	//
	// Close the file stream
	//

	file_close(&file);
}

c_cache_file_reach::~c_cache_file_reach()
{
	for (auto i = 0; i < k_number_of_cache_file_sections; i++)
		if (m_memory_buffers[i])
			delete[] m_memory_buffers[i];
}

s_cache_file_header *c_cache_file_reach::get_header()
{
	return &m_header;
}

s_cache_file_tags_header *c_cache_file_reach::get_tags_header()
{
	return get_tags_section_pointer<s_cache_file_tags_header>(m_header.tags_header_address);
}

char const *c_cache_file_reach::get_string(string_id id)
{
	auto set_min = 0x4C9;
	auto set_max = 0x1FFFF;
	auto set = STRING_ID_SET(id);
	auto index = STRING_ID_INDEX(id);

	if (set < 0 || set >= k_number_of_string_id_sets)
		return nullptr;

	auto string_id_indices = get_debug_section_pointer<long>(
		m_header.string_id_indices_offset);

	auto string_ids_buffer = get_debug_section_pointer<char>(
		m_header.string_ids_buffer_offset);

	if (set == 0 && (index < set_min || index > set_max))
		return string_ids_buffer + string_id_indices[index];

	return string_ids_buffer + string_id_indices[index + k_string_id_set_offsets[set]];
}

char const *c_cache_file_reach::get_tag_name(long index)
{
	auto tags_header = get_tags_header();
	auto absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(index);

	auto tag_name_indices = get_debug_section_pointer<long>(
		m_header.tag_name_indices_offset);

	auto tag_names_buffer = get_debug_section_pointer<char>(
		m_header.tag_names_buffer_offset);

	if (absolute_index < 0 || absolute_index >= tags_header->instances.count)
		return nullptr;

	return tag_names_buffer + tag_name_indices[absolute_index];
}

long c_cache_file_reach::find_tag_group(tag group_tag)
{
	auto tags_header = get_tags_header();

	for (auto i = 0; i < tags_header->groups.count; i++)
	{
		auto group = get_tag_group(i);
		
		if (group->group_tags[0] == group_tag)
			return i;
	}

	return NONE;
}

s_cache_file_tag_group *c_cache_file_reach::get_tag_group(long index)
{
	auto tags_header = get_tags_header();

	if (index < 0 || index >= tags_header->groups.count)
		return nullptr;

	return &get_tags_section_pointer<s_cache_file_tag_group>((ulonglong)tags_header->groups.address)[index];
}

s_cache_file_tag_instance *c_cache_file_reach::get_tag_instance(long index)
{
	auto tags_header = get_tags_header();
	auto absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(index);
	auto identifier = DATUM_INDEX_TO_IDENTIFIER(index);

	if (absolute_index < 0 || absolute_index >= tags_header->instances.count)
		return nullptr;

	auto instances = get_tags_section_pointer<s_cache_file_tag_instance>((ulonglong)tags_header->instances.address);

	return &instances[absolute_index];
}

char *c_cache_file_reach::get_section_buffer(e_cache_file_section section, long *out_offset, long *out_size)
{
	if (out_offset)
		*out_offset = m_header.section_offsets[section] + m_header.section_bounds[section].offset;

	if (out_size)
		*out_size = m_header.section_bounds[section].size;

	return m_memory_buffers[section];
}

ulonglong c_cache_file_reach::get_page_offset(ulong address)
{
	return ((ulonglong)address * 4) - (m_header.virtual_base_address - 0x50000000);
}

ulong c_cache_file_reach::make_page_offset(ulonglong address)
{
	return (ulong)((address + (m_header.virtual_base_address - 0x50000000)) / 4);
}
