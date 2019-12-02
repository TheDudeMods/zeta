#include <cache/cache_files.h>
#include <datatypes/data_array.h>
#include <tag_files/string_ids.h>
#include <tag_files/tag_groups.h>

#include <cstdio>
#include <cstdlib>

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
	FILE *stream = nullptr;
	fopen_s(&stream, filename, "rb+");

	//
	// Read the cache file header
	//

	fseek(stream, 0, SEEK_SET);
	fread(&m_header, sizeof(s_cache_file_header), 1, stream);

	//
	// Allocate and read the debug section
	//

	m_memory_buffers[_cache_file_section_debug] =
		new char[m_header.section_bounds[_cache_file_section_debug].size];

	auto debug_section_offset =
		m_header.section_offsets[_cache_file_section_debug] +
		m_header.section_bounds[_cache_file_section_debug].offset;

	auto debug_section_size =
		m_header.section_bounds[_cache_file_section_debug].size;

	fseek(stream, debug_section_offset, SEEK_SET);
	fread(m_memory_buffers[_cache_file_section_debug], debug_section_size, 1, stream);

	//
	// Allocate and read the tags section
	//

	m_memory_buffers[_cache_file_section_tags] =
		new char[m_header.section_bounds[_cache_file_section_tags].size];

	auto tags_section_offset =
		m_header.section_offsets[_cache_file_section_tags] +
		m_header.section_bounds[_cache_file_section_tags].offset;

	auto tags_section_size =
		m_header.section_bounds[_cache_file_section_tags].size;

	fseek(stream, tags_section_offset, SEEK_SET);
	fread(m_memory_buffers[_cache_file_section_tags], tags_section_size, 1, stream);

	m_address_mask = ((ulonglong)m_memory_buffers[_cache_file_section_tags] - m_header.virtual_base_address);

	//
	// Close the file stream
	//

	fclose(stream);
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

	auto debug_section_offset = m_header.section_bounds[_cache_file_section_debug].offset;

	auto string_id_indices_offset = m_header.string_id_indices_offset - debug_section_offset;
	auto string_id_indices = (long *)(m_memory_buffers[_cache_file_section_debug] + string_id_indices_offset);

	auto string_ids_buffer_offset = m_header.string_ids_buffer_offset - debug_section_offset;
	auto m_string_ids_buffer = m_memory_buffers[_cache_file_section_debug] + string_ids_buffer_offset;

	if (set == 0 && (index < set_min || index > set_max))
		return m_string_ids_buffer + string_id_indices[index];

	auto buffer = m_string_ids_buffer;

	for (auto i = 0; i < m_header.string_id_count; i++)
	{
		while (buffer[0] != '\0')
			buffer++;
		
		buffer++;

		if (csstrcmp("render_model", buffer) == 0)
		{
			auto offset = buffer - m_string_ids_buffer;
			break;
		}
	}

	return m_string_ids_buffer + string_id_indices[(index - set_min) + k_string_id_set_offsets[set]];
}

char const *c_cache_file_reach::get_tag_name(long index)
{
	auto tags_header = get_tags_header();
	auto absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(index);

	auto debug_section_offset = m_header.section_bounds[_cache_file_section_debug].offset;

	auto tag_name_indices_offset = m_header.tag_name_indices_offset - debug_section_offset;
	auto m_tag_name_indices = (long *)(m_memory_buffers[_cache_file_section_debug] + tag_name_indices_offset);

	auto tag_names_buffer_offset = m_header.tag_names_buffer_offset - debug_section_offset;
	auto m_tag_names_buffer = m_memory_buffers[_cache_file_section_debug] + tag_names_buffer_offset;

	if (absolute_index < 0 || absolute_index >= tags_header->instances.count)
		return nullptr;

	return m_tag_names_buffer + m_tag_name_indices[absolute_index];
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

ulonglong c_cache_file_reach::get_page_offset(ulong address)
{
	return ((ulonglong)address * 4) - (m_header.virtual_base_address - 0x50000000);
}

ulong c_cache_file_reach::make_page_offset(ulonglong address)
{
	return (ulong)((address + (m_header.virtual_base_address - 0x50000000)) / 4);
}

[[nodiscard]]
c_cache_file_reach *cache_file_load()
{
	static char cache_file_path[1024];

	//
	// Look up the cache file to open
	//

	while (true)
	{
		puts("");
		puts("Enter the path to a Halo cache file:");
		printf("> ");

		//
		// Read the cache file path
		//

		csmemset(cache_file_path, 0, 1024);
		fgets(cache_file_path, 1024, stdin);

		auto newline = csstrchr(cache_file_path, '\n');
		if (newline) *newline = '\0';

		//
		// If empty cache file path, start over
		//

		if (csstrlen(cache_file_path) == 0)
			continue;

		//
		// Verify the cache file format
		//

		FILE *stream = nullptr;
		if (fopen_s(&stream, cache_file_path, "rb+") == 0 && stream)
		{
			//
			// Read limited cache file header info
			//

			struct {
				tag header_signature;
				long file_version;
				long file_length;
			} cache_file_info;

			fseek(stream, 0, SEEK_SET);
			fread(&cache_file_info, sizeof(cache_file_info), 1, stream);
			fclose(stream);

			//
			// Check cache file header signature
			//

			if (cache_file_info.header_signature != k_cache_file_header_signature &&
				_byteswap_ulong(cache_file_info.header_signature) != k_cache_file_header_signature)
			{
				puts("ERROR: Invalid cache file!");
				continue;
			}
			else
			{
				puts("");
				break;
			}
		}
	}

	//
	// Allocate and load the cache file
	//

	return new c_cache_file_reach(cache_file_path);
}
