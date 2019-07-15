#include <cseries/cseries.h>
#include <cache/cache_files.h>
#include <commands/commands.h>

int main()
{
	//
	// Allocate and load the cache file
	//

	auto cache_file = new c_cache_file("C:\\Halo\\Reach\\maps\\m35.map");

	//
	// Allocate and initialize a command context, name buffer and input buffer
	//

	c_command_context test = { "test" };

	auto command_context = new c_command_context("tags", &test);
	auto name_buffer = new char[1024];
	auto input_buffer = new char[1024];

	//
	// Perform the command loop
	//

	while (command_context)
	{
		//
		// Display the full command context path
		//

		memset(name_buffer, 0, 1024);
		printf("%s> ", command_context->get_name(name_buffer));
		
		//
		// Read the command input
		//

		memset(input_buffer, 0, 1024);
		fgets(input_buffer, 1024, stdin);
		
		auto newline = strchr(input_buffer, '\n');
		if (newline) *newline = '\0';

		//
		// Parse and execute the command input
		//

		if (strcmp(input_buffer, "exit") == 0)
			command_context = command_context->get_parent();
		
		puts("");
	}

	//
	// Deallocate and dispose the command context, name buffer and input buffer
	//

	delete[] input_buffer;
	delete[] name_buffer;
	delete command_context;
	
	//
	// Deallocate and dispose the cache file
	//

	delete cache_file;

	return EXIT_SUCCESS;
}
