/*
MAIN.CPP
TODO: Refactor all of this crap, it's test code
*/

#include <cseries/cseries.h>
#include <cache/cache_files_reach.h>

int main()
{
	long_string cache_file_path;

	struct
	{
		tag header_signature;
		long file_version;
		long file_length;
	} cache_file_info;

	puts("Zeta v0.0.1");

	while (true)
	{
		puts("");
		puts("Enter the path to a Halo cache file:");
		printf("> ");

		gets_s(cache_file_path.ascii);

		if (strlen(cache_file_path.ascii) == 0)
			continue;

		FILE *stream = nullptr;

		if (stream = fopen(cache_file_path.ascii, "rb+"))
		{
			fseek(stream, 0, SEEK_SET);
			fread(&cache_file_info, sizeof(cache_file_info), 1, stream);
			fclose(stream);

			if (cache_file_info.header_signature != k_cache_header_signature &&
				_byteswap_ulong(cache_file_info.header_signature) != k_cache_header_signature)
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
	// TODO: read build name to further verify cache version
	//

	c_cache_file *cache_file = nullptr;

	switch (cache_file_info.file_version)
	{
	case 12:
		cache_file = new c_cache_file_reach(cache_file_path.ascii);
		break;

	default:
		printf("ERROR: Unsupported cache version: %i\n", cache_file_info.file_version);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
