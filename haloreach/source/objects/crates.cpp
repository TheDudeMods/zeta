#include <objects/crates.h>

extern s_tag_group object_group;
extern s_tag_block_definition campaign_metagame_bucket_block;

/* ---------- definitions */

TAG_ENUM(
    crate_flags_enum,
	k_number_of_crate_flags)
{
	{ "does_not_block_aoe", _crate_does_not_block_aoe_bit },
	{ "attach_texture_camera_hack", _crate_attach_texture_camera_hack_bit },
	{ "targetable", _crate_targetable_bit },
	{ "walls_block_aoe", _crate_walls_block_aoe_bit },
	{ "blocks_damage_flash_damage_response", _crate_blocks_damage_flash_damage_response_bit },
	{ "blocks_rumble_damage_response", _crate_blocks_rumble_damage_response_bit },
	{ "takes_top_level_aoe_damage", _crate_takes_top_level_aoe_damage_bit },
	{ "blocks_forced_projectile_overpenetration", _crate_blocks_forced_projectile_overpenetration_bit },
	{ "unimportant", _crate_unimportant_bit },
	{ "always_check_children_collision", _crate_always_check_children_collision_bit },
	{ "allow_friendly_team_to_pass_through_inside", _crate_allow_friendly_team_to_pass_through_inside_bit },
	{ "allow_ally_team_to_pass_through_inside", _crate_allow_ally_team_to_pass_through_inside_bit },
	{ "allow_friendly_team_to_pass_through_outside", _crate_allow_friendly_team_to_pass_through_outside_bit },
	{ "allow_ally_team_to_pass_through_outside", _crate_allow_ally_team_to_pass_through_outside_bit },
	{ "reject_all_contact_points_inside", _crate_reject_all_contact_points_inside_bit },
	{ "reject_all_contact_points_outside", _crate_reject_all_contact_points_outside_bit },
};

TAG_PAD(
    _field_short_integer,
    crate_post_crate_flags_padding,
    1);

TAG_GROUP(
    crate_group,
    k_crate_group_tag,
    sizeof(s_crate_definition) - sizeof(s_object_definition),
    &object_group)
{
	{ _field_word_flags, "crate_flags", &crate_flags_enum },
	{ _field_padding, "post_crate_flags_padding", &crate_post_crate_flags_padding },
	{ _field_block, "campaign_metagame_bucket", &campaign_metagame_bucket_block },
	{ _field_long_integer, "self_destruction_timer" },
    { _field_terminator }
};
