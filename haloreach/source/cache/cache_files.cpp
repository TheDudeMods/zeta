#include <cache/cache_files.h>
#include <datatypes/data_array.h>
#include <files/file_interface.h>
#include <files/file_synchronous_io.h>
#include <tag_files/string_ids.h>
#include <tag_files/tag_groups.h>

/* ---------- code */

bool s_cache_file_tag_group::is_in_group(
	tag group_tag) const
{
	if (group_tag == NONE)
		return true;

	return group_tags[0] == group_tag
		|| group_tags[1] == group_tag
		|| group_tags[2] == group_tag;
}

bool s_cache_file_tag_group::is_in_group(
	s_cache_file_tag_group &group) const
{
	return group_tags[0] == group.group_tags[0]
		|| group_tags[1] == group.group_tags[0]
		|| group_tags[2] == group.group_tags[0];
}


bool cache_file_allocate_and_load(
	char const *filename,
	s_cache_file_loaded_state *loaded_state,
	c_allocation_interface *allocation)
{
	assert(filename);
	assert(loaded_state);
	assert(allocation);

	c_file_path path;
	path.set_filename(filename);

	//
	// Open the cache file
	//

	s_file_accessor file;
	file_open(&path, FLAG(_file_open_read_bit), _file_error_mode_none, &file);

	//
	// Read the cache file header
	//

	file_set_position(&file, 0, _file_error_mode_none);
	
	if (!file_read(&file, sizeof(s_cache_file_header), _file_error_mode_none, &loaded_state->header))
	{
		file_close(&file);
		return false;
	}

	//
	// Allocate and read the cache file sections
	//

	for (auto i = 0; i < k_number_of_cache_file_sections; i++)
	{
		auto section_offset =
			loaded_state->header.section_offsets[i] +
			loaded_state->header.section_bounds[i].offset;

		auto section_size =
			loaded_state->header.section_bounds[i].size;

		loaded_state->sections[i] = c_basic_buffer(
			allocation->allocate(section_size, __FILE__, __LINE__),
			section_size);

		file_set_position(&file, section_offset, _file_error_mode_none);
		
		if (!file_read(&file, section_size, _file_error_mode_none, loaded_state->sections[i]))
		{
			file_close(&file);
			return false;
		}
	}

	//
	// Close the file accessor
	//

	file_close(&file);

	return true;
}

void cache_file_unload_and_deallocate(
	s_cache_file_loaded_state *loaded_state,
	c_allocation_interface *allocation)
{
	assert(loaded_state);
	assert(allocation);

	for (auto i = 0; i < k_number_of_cache_file_sections; i++)
	{
		auto address = loaded_state->sections[i].get_elements();

		if (address)
			allocation->deallocate(address, __FILE__, __LINE__);
	}

	csmemset(loaded_state, 0, sizeof(s_cache_file_loaded_state));
}

c_cache_file_reach::c_cache_file_reach(
	char const *filename) :
	c_cache_file(filename),
	m_header(),
	m_address_mask(0)
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

	auto debug_section_offset =
		m_header.section_offsets[_cache_file_section_debug] +
		m_header.section_bounds[_cache_file_section_debug].offset;

	auto debug_section_size =
		m_header.section_bounds[_cache_file_section_debug].size;

	m_debug_section_buffer = c_basic_buffer(new uchar[debug_section_size], debug_section_size);

	file_set_position(&file, debug_section_offset, _file_error_mode_none);
	file_read(&file, debug_section_size, _file_error_mode_none, m_debug_section_buffer);

	auto tags_section_offset =
		m_header.section_offsets[_cache_file_section_tags] +
		m_header.section_bounds[_cache_file_section_tags].offset;

	auto tags_section_size =
		m_header.section_bounds[_cache_file_section_tags].size;

	m_tags_section_buffer = c_basic_buffer(new uchar[tags_section_size], tags_section_size);

	file_set_position(&file, tags_section_offset, _file_error_mode_none);
	file_read(&file, tags_section_size, _file_error_mode_none, m_tags_section_buffer);

	m_address_mask = ((ulonglong)m_tags_section_buffer.get_elements() - m_header.virtual_base_address);

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
	delete[] m_debug_section_buffer;
	delete[] m_tags_section_buffer;
}

s_cache_file_header *c_cache_file_reach::get_header()
{
	return &m_header;
}

s_cache_file_tags_header *c_cache_file_reach::get_tags_header()
{
	return get_tags_section_pointer<s_cache_file_tags_header>(
		m_header.tags_header_address);
}

char const *c_cache_file_reach::get_string(
	string_id id)
{
	auto set = (id >> k_number_of_string_id_sets) & k_uint8_max;
	auto index = id & ((1 << k_number_of_string_id_sets) - 1);

	assert(VALID_INDEX(set, k_number_of_string_id_sets));

	auto string_id_indices = get_debug_section_pointer<long>(
		m_header.string_id_indices_offset);

	auto string_ids_buffer = get_debug_section_pointer<char>(
		m_header.string_ids_buffer_offset);

	auto set_base_index = 0;

	if (set == 0 && index >= k_string_id_set_string_counts[set])
	{
		for (auto i = 0; i < k_number_of_string_id_sets; i++)
			set_base_index += k_string_id_set_string_counts[i];

		index -= k_string_id_set_string_counts[set];
	}
	else
	{
		assert(VALID_INDEX(index, k_string_id_set_string_counts[set]));

		for (auto i = 0; i < set; i++)
			set_base_index += k_string_id_set_string_counts[i];
	}

	auto absolute_index = set_base_index + index;
	assert(VALID_INDEX(absolute_index, m_header.string_id_count));

	auto string_offset = string_id_indices[set_base_index + index];
	assert(VALID_INDEX(string_offset, m_header.string_ids_buffer_size));

	return offset_pointer(string_ids_buffer, string_offset);
}

char const *c_cache_file_reach::get_tag_name(
	long index)
{
	auto tags_header = get_tags_header();
	
	auto absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(index);
	assert(VALID_INDEX(absolute_index, m_header.tag_name_count));

	auto tag_name_indices = get_debug_section_pointer<long>(
		m_header.tag_name_indices_offset);

	auto tag_names_buffer = get_debug_section_pointer<char>(
		m_header.tag_names_buffer_offset);

	auto string_offset = tag_name_indices[absolute_index];
	
	if (string_offset < 0 || string_offset > m_header.tag_names_buffer_size)
		return nullptr;

	return tag_names_buffer + tag_name_indices[absolute_index];
}

long c_cache_file_reach::find_tag_group(
	tag group_tag)
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

s_cache_file_tag_group *c_cache_file_reach::get_tag_group(
	long index)
{
	auto tags_header = get_tags_header();

	if (index < 0 || index >= tags_header->groups.count)
		return nullptr;

	auto tag_groups = get_tags_section_pointer<s_cache_file_tag_group>(
		tags_header->groups.address);

	return &tag_groups[index];
}

s_cache_file_tag_instance *c_cache_file_reach::get_tag_instance(
	long index)
{
	auto tags_header = get_tags_header();

	auto identifier = DATUM_INDEX_TO_IDENTIFIER(index);
	auto absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(index);

	if (!VALID_INDEX(absolute_index, tags_header->instances.count))
		return nullptr;

	auto instances = get_tags_section_pointer<s_cache_file_tag_instance>(
		tags_header->instances.address);

	return &instances[absolute_index];
}

ulonglong c_cache_file_reach::get_page_offset(
	ulong address)
{
	return ((ulonglong)address * 4) - (m_header.virtual_base_address - 0x50000000);
}

ulong c_cache_file_reach::make_page_offset(
	ulonglong address)
{
	return (ulong)((address + (m_header.virtual_base_address - 0x50000000)) / 4);
}
