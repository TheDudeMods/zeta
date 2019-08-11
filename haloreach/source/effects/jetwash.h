#pragma once

#include <cseries/cseries.h>
#include <math/real_math.h>

/* ---------- constants */

enum
{
	k_maximum_number_of_jetwash_definitions = 4
};

/* ---------- structures */

struct s_jetwash_definition
{
	string_id marker;
	real radius;
	long maximum_traces;
	real maximum_emission_length;
	angle_bounds trace_yaw_angle;
	angle_bounds trace_pitch_angle;
	real particle_offset;
};
static_assert(sizeof(s_jetwash_definition) == 0x24);
