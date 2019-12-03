#include <devices/device_controls.h>

extern s_tag_group device_group;
extern s_tag_reference_definition device_effect_sound_reference;

/* ---------- definitions */

TAG_ENUM(
	control_type_enum,
	k_number_of_control_types)
{
	{ "toggle", _control_type_toggle },
	{ "on", _control_type_on },
	{ "off", _control_type_off },
	{ "call", _control_type_call },
	{ "generator", _control_type_generator },
};

TAG_ENUM(
	control_trigger_enum,
	k_number_of_control_triggers)
{
	{ "touched_by_player", _control_triggers_when_touched_by_player },
	{ "destroyed", _control_triggers_when_destroyed },
};

TAG_GROUP(
	control_group,
	k_control_group_tag,
	sizeof(s_control_definition) - sizeof(s_device_definition),
	&device_group)
{
	{ _field_short_enum, "control_type", &control_type_enum },
	{ _field_short_enum, "triggers_when", &control_trigger_enum },
	{ _field_real, "call_value" },
	{ _field_string_id, "action_string" },
	{ _field_tag_reference, "on", &device_effect_sound_reference },
	{ _field_tag_reference, "off", &device_effect_sound_reference },
	{ _field_tag_reference, "deny", &device_effect_sound_reference },
	{ _field_terminator }
};
