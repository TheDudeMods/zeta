#include <cache/cache_files.h>
#include <memory/data_base.h>
#include <tag_files/string_ids.h>
#include <tag_files/tag_groups.h>

/* ---------- code */

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

		memset(cache_file_path, 0, 1024);
		fgets(cache_file_path, 1024, stdin);

		auto newline = strchr(cache_file_path, '\n');
		if (newline) *newline = '\0';

		//
		// If empty cache file path, start over
		//

		if (strlen(cache_file_path) == 0)
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

void cache_files_close()
{
}

c_cache_file_reach::c_cache_file_reach(char const *filename) :
	c_cache_file(filename),
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

c_cache_file_reach::~c_cache_file_reach()
{
	if (m_tag_names_buffer) delete[] m_tag_names_buffer;
	if (m_tag_name_indices) delete[] m_tag_name_indices;
	if (m_string_ids_buffer) delete[] m_string_ids_buffer;
	if (m_string_id_indices) delete[] m_string_id_indices;
	if (m_memory_buffer) delete[] m_memory_buffer;
}

s_cache_file_header *c_cache_file_reach::get_header()
{
	return &m_header;
}

s_cache_file_tags_header *c_cache_file_reach::get_tags_header()
{
	return get_buffer_data<s_cache_file_tags_header>(m_header.tags_header_address);
}

char const *c_cache_file_reach::get_string(string_id id)
{
	auto set_min = (unsigned long)0x4C8;
	auto set_max = (unsigned long)0x1FFFF;
	auto set = STRING_ID_SET(id);
	auto index = STRING_ID_INDEX(id);

	if (set < 0 || set >= k_number_of_string_id_sets)
		return nullptr;

	if (set == 0 && index >= set_max)
		return m_string_ids_buffer + m_string_id_indices[index];

	return m_string_ids_buffer + m_string_id_indices[index + k_string_id_set_offsets[set]];
}

char const *c_cache_file_reach::get_tag_name(long index)
{
	auto tags_header = get_tags_header();
	auto absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(index);

	if (absolute_index < 0 || absolute_index >= tags_header->tag_count)
		return nullptr;

	return m_tag_names_buffer + m_tag_name_indices[absolute_index];
}

long c_cache_file_reach::find_tag_group(tag group_tag)
{
	auto tags_header = get_tags_header();

	for (auto i = 0; i < tags_header->group_count; i++)
	{
		auto group = get_tag_group(i);
		
		if (group->tags[0] == group_tag)
			return i;
	}

	return NONE;
}

s_tag_group *c_cache_file_reach::get_tag_group(long index)
{
	auto tags_header = get_tags_header();

	if (index < 0 || index >= tags_header->group_count)
		return nullptr;

	return &get_buffer_data<s_tag_group>(tags_header->groups_address)[index];
}

s_cache_file_tag_instance *c_cache_file_reach::get_tag_instance(long index)
{
	auto tags_header = get_tags_header();
	auto absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(index);
	auto identifier = DATUM_INDEX_TO_IDENTIFIER(index);

	if (absolute_index < 0 || absolute_index >= tags_header->tag_count)
		return nullptr;

	return &get_buffer_data<s_cache_file_tag_instance>(tags_header->tags_address)[absolute_index];
}

qword c_cache_file_reach::get_page_offset(dword address)
{
	return ((qword)address * 4) - (m_header.virtual_base_address - 0x10000000);
}

dword c_cache_file_reach::make_page_offset(qword address)
{
	return (dword)((address + (m_header.virtual_base_address - 0x10000000)) / 4);
}
