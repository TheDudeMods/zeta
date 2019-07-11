#include <cseries/cseries.h>
#include <cache/cache_files.h>
#include <objects/object_definitions.h>

int main()
{
	auto file = new c_cache_file("C:\\Halo\\Reach\\maps\\m35.map");

	auto object = file->get_tag_definition<s_object_definition>(0x36B1);
	auto attachments = file->get_page_data<s_object_attachment>(object->attachments.address);

	delete file;

	return 0;
}
