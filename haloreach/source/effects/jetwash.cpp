#include <effects/jetwash.h>
#include <tag_files/tag_groups.h>

/* ---------- definitions */

TAG_BLOCK(
	jetwash_definition_block,
	sizeof(s_jetwash_definition),
	k_maximum_number_of_jetwash_definitions)
{
	{ _field_string_id, "marker" },
	{ _field_real, "radius" },
	{ _field_long_integer, "maximum_traces" },
	{ _field_real, "maximum_emission_length" },
	{ _field_angle_bounds, "trace_yaw_angle" },
	{ _field_angle_bounds, "trace_pitch_angle" },
	{ _field_real, "particle_offset" },
	{ _field_terminator }
};
