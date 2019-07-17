#include <commands/tag_commands.h>
#include <items/projectiles.h>

/* ---------- code */

void edit_tag(
	long index)
{
	//
	// TODO
	//
}

bool edit_tag_execute(
	long arg_count,
	char const **arg_values)
{
	if (arg_count != 1)
		return false;

	auto tag_index = strtoul(arg_values[0], nullptr, 0);
	edit_tag(tag_index);

	return true;
}
