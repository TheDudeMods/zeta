#include <cseries/cseries.h>
#include <cache/cache_files.h>
#include <commands/commands.h>

/* ---------- globals */

static c_command_context *command_context;
static char cache_file_path[1024];
static char name_buffer[1024];
static char input_buffer[1024];

static struct
{
	tag header_signature;
	long file_version;
	long file_length;
} cache_file_info;

/* ---------- code */

int main()
{
	puts("Zeta v0.0.1");

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

		if (stream = fopen(cache_file_path, "rb+"))
		{
			//
			// Read limited cache file header info
			//

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

	auto cache_file = new c_cache_file(cache_file_path);

	//
	// Allocate and initialize the command context
	//

	command_context = new c_command_context("tags");

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
	// Dispose and deallocate the command context
	//

	delete command_context;

	//
	// Dispose and deallocate the cache file
	//

	delete cache_file;

	return EXIT_SUCCESS;
}
