#pragma once

#include <cseries/cseries.h>

/* ---------- constants */

enum
{
	k_number_of_string_ids = 0x173B
};

/* ---------- enumerators */

enum e_string_id_set
{
	_string_id_set_static_globals,
	_string_id_set_ui,
	_string_id_set_ui_alerts,
	_string_id_set_events,
	_string_id_set_ui_events,
	_string_id_set_widget_events,
	_string_id_set_widgets,
	_string_id_set_properties,
	_string_id_set_cui_events,
	_string_id_set_mp_events,
	_string_id_set_result_codes,
	_string_id_set_achievements,
	_string_id_set_default_formats,
	_string_id_set_engine_globals,
	_string_id_set_ai,
	_string_id_set_hud_message,
	_string_id_set_pc_input,
	k_number_of_string_id_sets
};

/* ---------- globals */

extern long const k_string_id_set_offsets[
	k_number_of_string_id_sets];

/* ---------- prototypes/STRING_IDS.CPP */

char const *string_id_get_string(string_id id);
