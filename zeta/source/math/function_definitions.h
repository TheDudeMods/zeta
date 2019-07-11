#pragma once

#include <cseries/cseries.h>
#include <math/real_math.h>
#include <tag_files/tag_groups.h>

/* ---------- enums */

enum e_function_output_modifier
{
	_function_output_modifier_none,
	_function_output_modifier_plus,
	_function_output_modifier_times,

	k_number_of_function_output_modifiers
};

enum e_function_variable_type
{
	_function_variable_particle_age,
	_function_variable_emitter_age,
	_function_variable_particle_random,
	_function_variable_emitter_random,
	_function_variable_particle_random1,
	_function_variable_particle_random2,
	_function_variable_particle_random3,
	_function_variable_particle_random4,
	_function_variable_emitter_random1,
	_function_variable_emitter_random2,
	_function_variable_emitter_time,
	_function_variable_system_lod,
	_function_variable_game_time,
	_function_variable_effect_a_scale,
	_function_variable_effect_b_scale,
	_function_variable_physics_rotation,
	_function_variable_location_random,
	_function_variable_distance_from_emitter,
	_function_variable_particle_simulation_a,
	_function_variable_particle_simulation_b,
	_function_variable_particle_velocity,
	_function_variable_invalid,

	k_number_of_function_variable_types
};

enum e_function_runtime_m_flags
{
	_function_runtime_m_unknown0_bit,
	_function_runtime_m_unknown1_bit,
	_function_runtime_m_unknown2_bit,
	_function_runtime_m_unknown3_bit,
	_function_runtime_m_unknown4_bit,
	_function_runtime_m_unknown5_bit,
	_function_runtime_m_unknown6_bit,
	_function_runtime_m_unknown7_bit,

	k_number_of_function_runtime_m_flags
};

/* ---------- structures */

class c_function_definition
{
public:
	c_enum<e_function_variable_type, char> input_variable;
	c_enum<e_function_variable_type, char> range_variable;
	c_enum<e_function_output_modifier, char> output_modifier;
	c_enum<e_function_variable_type, char> output_modifier_input;
	s_tag_data data;
	real runtime_m_constant_value;
	c_flags<e_function_runtime_m_flags, byte> runtime_m_flags;
	char : 8;
	short : 16;
};
static_assert(sizeof(c_function_definition) == 0x20);
