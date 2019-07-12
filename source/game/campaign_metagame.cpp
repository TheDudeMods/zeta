#include <game/campaign_metagame.h>

/* ---------- definitions */

TAG_ENUM(
    campaign_metagame_bucket_flags_enum,
    k_number_of_campaign_metagame_bucket_flags)
{
    { "only_counts_with_riders", _campaign_metagame_bucket_only_counts_with_riders_bit },
};

TAG_ENUM(
    campaign_metagame_bucket_type_enum,
    k_number_of_campaign_metagame_bucket_types)
{
    { "brute", _campaign_metagame_bucket_type_brute },
    { "grunt", _campaign_metagame_bucket_type_grunt },
    { "jackal", _campaign_metagame_bucket_type_jackal },
    { "skirmisher", _campaign_metagame_bucket_type_skirmisher },
    { "marine", _campaign_metagame_bucket_type_marine },
    { "spartan", _campaign_metagame_bucket_type_spartan },
    { "bugger", _campaign_metagame_bucket_type_bugger },
    { "hunter", _campaign_metagame_bucket_type_hunter },
    { "flood_infection", _campaign_metagame_bucket_type_flood_infection },
    { "flood_carrier", _campaign_metagame_bucket_type_flood_carrier },
    { "flood_combat", _campaign_metagame_bucket_type_flood_combat },
    { "flood_pure", _campaign_metagame_bucket_type_flood_pure },
    { "sentinel", _campaign_metagame_bucket_type_sentinel },
    { "elite", _campaign_metagame_bucket_type_elite },
    { "engineer", _campaign_metagame_bucket_type_engineer },
    { "mule", _campaign_metagame_bucket_type_mule },
    { "turret", _campaign_metagame_bucket_type_turret },
    { "mongoose", _campaign_metagame_bucket_type_mongoose },
    { "warthog", _campaign_metagame_bucket_type_warthog },
    { "scorpion", _campaign_metagame_bucket_type_scorpion },
    { "hornet", _campaign_metagame_bucket_type_hornet },
    { "pelican", _campaign_metagame_bucket_type_pelican },
    { "revenant", _campaign_metagame_bucket_type_revenant },
    { "seraph", _campaign_metagame_bucket_type_seraph },
    { "shade", _campaign_metagame_bucket_type_shade },
    { "watchtower", _campaign_metagame_bucket_type_watchtower },
    { "ghost", _campaign_metagame_bucket_type_ghost },
    { "chopper", _campaign_metagame_bucket_type_chopper },
    { "mauler", _campaign_metagame_bucket_type_mauler },
    { "wraith", _campaign_metagame_bucket_type_wraith },
    { "banshee", _campaign_metagame_bucket_type_banshee },
    { "phantom", _campaign_metagame_bucket_type_phantom },
    { "scarab", _campaign_metagame_bucket_type_scarab },
    { "guntower", _campaign_metagame_bucket_type_guntower },
    { "tuning_fork", _campaign_metagame_bucket_type_tuning_fork },
    { "broadsword", _campaign_metagame_bucket_type_broadsword },
    { "mammoth", _campaign_metagame_bucket_type_mammoth },
    { "lich", _campaign_metagame_bucket_type_lich },
    { "mantis", _campaign_metagame_bucket_type_mantis },
    { "wasp", _campaign_metagame_bucket_type_wasp },
    { "phaeton", _campaign_metagame_bucket_type_phaeton },
    { "bishop", _campaign_metagame_bucket_type_bishop },
    { "knight", _campaign_metagame_bucket_type_knight },
    { "pawn", _campaign_metagame_bucket_type_pawn },
    { "soldier", _campaign_metagame_bucket_type_soldier },
    { "packmaster", _campaign_metagame_bucket_type_packmaster },
    { "cavalier", _campaign_metagame_bucket_type_cavalier },
};

TAG_ENUM(
    campaign_metagame_bucket_class_enum,
    k_number_of_campaign_metagame_bucket_classes)
{
    { "infantry", _campaign_metagame_bucket_class_infantry },
    { "leader", _campaign_metagame_bucket_class_leader },
    { "hero", _campaign_metagame_bucket_class_hero },
    { "specialist", _campaign_metagame_bucket_class_specialist },
    { "light_vehicle", _campaign_metagame_bucket_class_light_vehicle },
    { "heavy_vehicle", _campaign_metagame_bucket_class_heavy_vehicle },
    { "giant_vehicle", _campaign_metagame_bucket_class_giant_vehicle },
    { "standard_vehicle", _campaign_metagame_bucket_class_standard_vehicle },
};

TAG_PADDING(_field_char_integer, campaign_metagame_bucket_post_class_padding, 1);
TAG_PADDING(_field_short_integer, campaign_metagame_bucket_post_point_count_padding, 1);

TAG_BLOCK(
    campaign_metagame_bucket_block,
    sizeof(s_campaign_metagame_bucket),
    k_maximum_number_of_campaign_metagame_buckets)
{
    { _field_byte_flags, "flags", &campaign_metagame_bucket_flags_enum },
    { _field_char_enum, "type", &campaign_metagame_bucket_type_enum },
    { _field_char_enum, "class", &campaign_metagame_bucket_class_enum },
    { _field_padding, "post_class_padding", &campaign_metagame_bucket_post_class_padding },
    { _field_short_integer, "point_count" },
    { _field_padding, "post_point_count_padding", &campaign_metagame_bucket_post_point_count_padding },
    { _field_terminator }
};
