#include <cseries/cseries.h>
#include <cache/cache_files.h>
#include <commands/commands.h>

/* ---------- code */

int main()
{
	puts("Zeta v0.0.1");

	cache_files_open();
	command_loop_execute();
	cache_files_close();

	return EXIT_SUCCESS;
}
