#include <cseries/cseries.h>
#include <cache/cache_files.h>
#include <objects/object_definitions.h>

int main()
{
	auto file = new c_cache_file("C:\\Halo\\Reach\\maps\\m35.map");

	/*for (long i = 0; i < file->get_tags_header()->tag_count; i++)
	{
		auto instance = file->get_tag_instance(i);

		if (!instance || instance->address == 0)
			continue;

		auto group = file->get_tag_group(instance->group_index);

		if (!group)
			continue;

		auto group_name = file->get_string(group->name);

		printf("[Index: 0x%04X] %s.%s\n", i, file->get_tag_name(i), group_name);
	}*/

	auto spartans_biped = file->get_tag_definition<s_object_definition>(0x36B1);

	delete file;

	return 0;
}
