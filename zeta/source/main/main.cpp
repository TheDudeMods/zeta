#include <cseries/cseries.h>
#include <cache/cache_files.h>
#include <commands/commands.h>

#include <units/biped_definitions.h>

#include <cstdio>
#include <cstdlib>

/* ---------- prototypes */

[[nodiscard]]
c_cache_file_reach *cache_file_load();

/* ---------- code */

int main()
{
	puts("Zeta v0.0.1");

	auto file = cache_file_load();
	command_loop_execute(file);
	delete file;

	return EXIT_SUCCESS;
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
