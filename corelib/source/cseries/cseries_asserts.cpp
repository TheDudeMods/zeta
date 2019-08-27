#include <cseries/cseries_asserts.h>
#include <cstdio>
#include <cstdlib>

/* ---------- code */

[[noreturn]]
void assert_halt(
	char const *message,
	char const *file,
	unsigned long line)
{
	printf("ERROR: %s, FILE: %s, LINE: %ull\n", message, file, line);
	exit(-1);
}
