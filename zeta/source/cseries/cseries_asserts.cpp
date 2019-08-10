#include <cseries/cseries.h>
#include <cseries/cseries_asserts.h>

/* ---------- code */

void display_assert(char const *reason, char const *file, long line, bool halt)
{
	static char temp[1024];

	if (!reason)
		reason = "<no reason given>";

	memset(temp, 0, 1024);
	sprintf(temp, "EXCEPTION %s in %s,#%ld: %s", halt ? "halt" : "warn", file, line, reason);

	if (halt)
		abort();
}
