#pragma once

#include <cseries/cseries.h>
#include <datatypes/enum.h>
#include <datatypes/flags.h>
#include <math/real_math.h>

/* ---------- enumerators */

enum e_scenario_type
{
	_scenario_type_none = NONE,
	_scenario_type_campaign,
	_scenario_type_multiplayer,
	_scenario_type_mainmenu,
	_scenario_type_shared,
	_scenario_type_shared_campaign,
	_scenario_type_shared_multiplayer,
	k_number_of_scenario_types
};

enum e_scenario_load_type
{
	_scenario_load_none = NONE,
	_scenario_load_default,
	_scenario_load_shared,
	_scenario_load_shared_campaign,
	_scenario_load_shared_multiplayer,
	k_number_of_scenario_load_types
};

enum e_scenario_flags
{

};

/* ---------- structures */

struct s_scenario
{
	c_enum<e_scenario_type, short> scenario_type;

};

/* ---------- prototypes/SCENARIO.CPP */
