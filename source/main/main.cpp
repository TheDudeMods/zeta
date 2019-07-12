#include <cseries/cseries.h>
#include <cache/cache_files.h>
#include <items/item_definitions.h>

int main()
{
	//
	// Allocate and initialize the reach cache file
	//

	auto file = new c_cache_file("C:\\Halo\\Reach\\maps\\m35.map");
	
	auto tags_header = file->get_tags_header();

	if (!tags_header)
	{
		delete file;
		return EXIT_FAILURE;
	}

	//
	// Get the first item tag definition
	//

	s_item_definition *item = nullptr;

	for (qword i = 0; i < tags_header->tag_count; i++)
	{
		auto instance = file->get_tag_instance(i);

		if (!instance || instance->group_index == NONE)
			continue;
		
		auto group = file->get_tag_group(instance->group_index);

		if (!group)
			continue;
		
		if (group->is_in_group('item'))
		{
			printf("[0x%04llX] %s.%s\n", i, file->get_tag_name(i), file->get_string(group->name));
			item = file->get_tag_definition<s_item_definition>(i);
			break;
		}
	}

	//
	// Dispose and deallocate the cache file
	//

	delete file;

	return EXIT_SUCCESS;
}
