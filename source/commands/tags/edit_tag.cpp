#include <commands/tags/tag_commands.h>
#include <items/projectiles.h>

/* ---------- code */

void edit_tag(
	long index)
{
	//
	// TODO: implement edit tag, remove test code
	//

	auto definition = g_cache_file->get_tag_definition<s_projectile_definition>(index);
	printf("%f", definition->acceleration_range.upper);
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
