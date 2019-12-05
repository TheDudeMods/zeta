#include <objects/scenery.h>

extern s_tag_group object_group;

/* ---------- definitions */

TAG_ENUM(
    scenery_pathfinding_policy_enum,
    k_number_of_scenery_pathfinding_policies)
{
    { "cut_out", _scenery_pathfinding_policy_cut_out },
    { "static", _scenery_pathfinding_policy_static },
    { "dynamic", _scenery_pathfinding_policy_dynamic },
    { "none", _scenery_pathfinding_policy_none },
};

TAG_ENUM(
    scenery_flags_enum,
    k_number_of_scenery_flags)
{
    { "not_physical", _scenery_not_physical_bit },
    { "use_complex_activation", _scenery_use_complex_activation_bit },
};

TAG_ENUM(
    scenery_lightmapping_policy_enum,
    k_number_of_scenery_lightmapping_policies)
{
    { "per_vertex", _scenery_lightmapping_policy_per_vertex },
    { "per_pixel", _scenery_lightmapping_policy_per_pixel },
    { "dynamic", _scenery_lightmapping_policy_dynamic },
};

TAG_PAD(
    _field_short_integer,
    scenery_post_lightmapping_policy_padding,
    1);

TAG_GROUP(
    scenery_group,
    k_scenery_group_tag,
    sizeof(s_scenery_definition) - sizeof(s_object_definition),
    &object_group)
{
    { _field_short_enum, "pathfinding_policy", &scenery_pathfinding_policy_enum },
    { _field_word_flags, "scenery_flags", &scenery_flags_enum },
    { _field_short_enum, "lightmapping_policy", &scenery_lightmapping_policy_enum },
    { _field_pad, "post_lightmapping_policy_padding", &scenery_post_lightmapping_policy_padding },
    { _field_terminator }
};
