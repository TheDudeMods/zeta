#include <items/item_definitions.h>

extern s_tag_group_definition object_group;

/* ---------- definitions */

TAG_ENUM(
	item_definition_flags_enum,
	k_number_of_item_definition_flags)
{
    { "always_maintains_z_up", _item_always_maintains_z_up_bit },
    { "blocks_headshots", _item_blocks_headshots_bit },
    { "use_ground_scale_for_all_unspecified_attachments", _item_use_ground_scale_for_all_unspecified_attachments_bit },
    { "fixup_position_upon_detaching_from_parent", _item_fixup_position_upon_detaching_from_parent_bit },
    { "fixup_position_after_attaching_to_parent", _item_fixup_position_after_attaching_to_parent_bit },
    { "item_considered_high_value", _item_item_considered_high_value_bit },
    { "item_requires_a_child_to_be_a_pickup_item", _item_item_requires_a_child_to_be_a_pickup_item_bit },
};

TAG_BLOCK(
	item_predicted_bitmaps_block,
	sizeof(s_item_predicted_bitmap),
	k_maximum_number_of_item_predicted_bitmaps)
{
	{ _field_tag_reference, "bitmap" }
};

TAG_GROUP(
	item_group,
	k_item_group_tag,
	sizeof(s_item_definition),
	&object_group)
{
	{ _field_long_flags, "item_flags", &item_definition_flags_enum },
	{ _field_short_integer, "old_message_index" },
	{ _field_short_integer, "sort_order" },
	{ _field_real, "old_multiplayer_on_ground_scale" },
	{ _field_real, "old_campaign_on_ground_scale" },
	{ _field_string_id, "pickup_message" },
	{ _field_string_id, "swap_message" },
	{ _field_string_id, "pickup_or_dual_wield_message" },
	{ _field_string_id, "swap_or_dual_wield_message" },
	{ _field_string_id, "picked_up_message" },
	{ _field_string_id, "switch_to_message" },
	{ _field_string_id, "switch_to_from_ai_message" },
	{ _field_string_id, "notify_empty_message" },
	{ _field_string_id, "notify_overheated_message" },
	{ _field_tag_reference, "collision_sound" },
	{ _field_block, "predicted_bitmaps", &item_predicted_bitmaps_block },
	{ _field_tag_reference, "detonation_damage_effect" },
	{ _field_real_bounds, "detonation_delay" },
	{ _field_tag_reference, "detonating_effect" },
	{ _field_tag_reference, "detonation_effect" },
	{ _field_real, "ground_scale" },
	{ _field_real, "human_hold_scale" },
	{ _field_real, "human_holster_scale" },
	{ _field_real, "covenant_hold_scale" },
	{ _field_real, "covenant_holster_scale" },
	{ _field_real, "boss_hold_scale" },
	{ _field_real, "boss_holster_scale" },
	{ _field_real, "player_hold_scale" },
	{ _field_real, "player_holster_scale" },
	{ _field_terminator }
};
