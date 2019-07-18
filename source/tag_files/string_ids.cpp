#include <cache/cache_files.h>
#include <tag_files/string_ids.h>

/* ---------- globals */

long const k_string_id_set_offsets[
	k_number_of_string_id_sets] =
{
	0x1273, 0x0, 0x4C8, 0xB2D, 0xC0A, 0xC70,
	0xD49, 0xD6F, 0xD74, 0x1433, 0x15A3,
	0x15B7, 0x1619, 0x1631, 0x163E, 0x1667
};

/* ---------- code */

char const *string_id_get_string(
	string_id id)
{
	return g_cache_file->get_string(id);
}
