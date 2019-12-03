#include <devices/devices.h>
#include <effects/effects.h>
#include <sound/sound_definitions.h>

extern s_tag_group object_group;

/* ---------- definitions */

TAG_ENUM(
    device_flags_enum,
    k_number_of_device_flags)
{
    { "position_loops", _device_position_loops_bit },
    { "use_multiplayer_boundary", _device_use_multiplayer_boundary_bit },
    { "allow_interpolation", _device_allow_interpolation_bit },
    { "allow_attached_players", _device_allow_attached_players_bit },
    { "control_uses_parent_interact_scripts", _device_control_uses_parent_interact_scripts_bit },
    { "requires_line_of_sight_for_interaction", _device_requires_line_of_sight_for_interaction_bit },
    { "only_active_when_parent_is_hostile", _device_only_active_when_parent_is_hostile_bit },
    { "is_targetable", _device_is_targetable_bit },
    { "ignore_important_work_just_for_vs", _device_ignore_important_work_just_for_vs_bit },
    { "huge_device", _device_huge_device_bit },
};

TAG_ENUM(
    device_lightmap_flags_enum,
    k_number_of_device_lightmap_flags)
{
    { "dont_use_in_lightmap", _device_dont_use_in_lightmap_bit },
    { "dont_use_in_lightprobe", _device_dont_use_in_lightprobe_bit },
};

TAG_PAD(
    _field_short_integer,
    device_post_lightmap_flags_padding,
    1);

TAG_REFERENCE(
    device_effect_sound_reference,
    2)
{
    k_sound_group_tag,
    k_effect_group_tag
};

TAG_GROUP(
    device_group,
    k_device_group_tag,
    sizeof(s_device_definition) - sizeof(s_object_definition),
    &object_group)
{
    { _field_long_flags, "device_flags", &device_flags_enum },
    { _field_real, "power_transition_time" },
    { _field_real, "power_acceleration_time" },
    { _field_real, "position_transition_time" },
    { _field_real, "position_acceleration_time" },
    { _field_real, "depowered_position_transition_time" },
    { _field_real, "depowered_position_acceleration_time" },
    { _field_word_flags, "lightmap_flags", &device_lightmap_flags_enum },
    { _field_padding, "post_lightmap_flags_padding", &device_post_lightmap_flags_padding },
    { _field_tag_reference, "open", &device_effect_sound_reference },
    { _field_tag_reference, "close", &device_effect_sound_reference },
    { _field_tag_reference, "opened", &device_effect_sound_reference },
    { _field_tag_reference, "closed", &device_effect_sound_reference },
    { _field_tag_reference, "depowered", &device_effect_sound_reference },
    { _field_tag_reference, "repowered", &device_effect_sound_reference },
    { _field_real, "delay_time" },
    { _field_tag_reference, "delay_effect", &device_effect_sound_reference },
    { _field_real, "automatic_activation_radius" },
    { _field_terminator }
};
