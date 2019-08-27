#include <cseries/cseries.h>
#include <cache/cache_files.h>
#include <commands/commands.h>

#include <cstdio>
#include <cstdlib>

/* ---------- code */

int main()
{
	puts("Zeta v0.0.1");

	auto file = cache_file_load();

	command_loop_execute(file);

	delete file;

	return EXIT_SUCCESS;
}
