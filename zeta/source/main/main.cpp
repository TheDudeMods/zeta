#include <cseries/cseries.h>
#include <cache/cache_files.h>
#include <objects/object_definitions.h>

int main()
{
	//
	// Allocate and initialize the reach cache file
	//

	auto file = new c_cache_file("C:\\Halo\\Reach\\maps\\m35.map");

	//
	// Get the object definition of 'objects\characters\spartans\spartans.biped'
	//

	auto object = file->get_tag_definition<s_object_definition>(0x36B1);
	
	//
	// Dispose and deallocate the cache file
	//

	delete file;

	return 0;
}
