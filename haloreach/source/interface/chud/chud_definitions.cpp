#include <interface/chud/chud_definitions.h>
#include <tag_files/tag_groups.h>

/* ---------- definitions */

TAG_ENUM(
	motion_tracker_noise_enum,
	k_motion_tracker_noise_count)
{
	{ "edge", _motion_tracker_noise_edge },
	{ "inner", _motion_tracker_noise_inner },
	{ "silent", _motion_tracker_noise_silent }
};
