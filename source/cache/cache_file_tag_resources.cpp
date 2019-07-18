#include <cache/cache_file_tag_resources.h>

/* ---------- definitions */

TAG_ARRAY(
	_field_long_integer,
	cache_file_resource_guid_array,
	4);

TAG_BLOCK(
	cache_file_resource_compression_codec_block,
	sizeof(s_cache_file_resource_compression_codec),
	NONE)
{
	{ _field_array, "guid", &cache_file_resource_guid_array },
	{ _field_terminator }
};

TAG_PADDING(
	_field_long_integer,
	cache_file_resource_physical_location_unknown_padding,
	58);

TAG_BLOCK(
	cache_file_resource_physical_location_block,
	sizeof(s_cache_file_resource_physical_location),
	NONE)
{
	{ _field_short_string, "path" },
	{ _field_padding, "unknown", &cache_file_resource_physical_location_unknown_padding },
	{ _field_terminator }
};

TAG_ENUM(
	cache_file_resource_page_instance_flags_enum,
	k_number_of_cache_file_resource_page_flags)
{
	{ "unknown0", _cache_file_resource_page_unknown0_bit },
	{ "unknown1", _cache_file_resource_page_unknown1_bit },
	{ "unknown2", _cache_file_resource_page_unknown2_bit },
	{ "unknown3", _cache_file_resource_page_unknown3_bit },
	{ "unknown4", _cache_file_resource_page_unknown4_bit },
	{ "unknown5", _cache_file_resource_page_unknown5_bit },
	{ "unknown6", _cache_file_resource_page_unknown6_bit },
	{ "unknown7", _cache_file_resource_page_unknown7_bit },
};

TAG_PADDING(
	_field_short_integer,
	cache_file_resource_page_post_physical_location_padding,
	1);

TAG_ARRAY(
	_field_long_integer,
	cache_file_resource_page_sha1_array,
	5);

TAG_BLOCK(
	cache_file_resource_page_block,
	sizeof(s_cache_file_resource_page),
	NONE)
{
	{ _field_word_integer, "identifier" },
	{ _field_byte_flags, "flags", &cache_file_resource_page_instance_flags_enum },
	{ _field_char_block_index, "compression_codec", &cache_file_resource_compression_codec_block },
	{ _field_short_block_index, "physical_location", &cache_file_resource_physical_location_block },
	{ _field_padding, "post_physical_location_padding", &cache_file_resource_page_post_physical_location_padding },
	{ _field_dword_integer, "block_offset" },
	{ _field_dword_integer, "compressed_block_size" },
	{ _field_dword_integer, "uncompressed_block_size" },
	{ _field_long_integer, "crc" },
	{ _field_array, "sha1_a", &cache_file_resource_page_sha1_array },
	{ _field_array, "sha1_b", &cache_file_resource_page_sha1_array },
	{ _field_array, "sha1_c", &cache_file_resource_page_sha1_array },
	{ _field_short_integer, "block_asset_count" },
	{ _field_short_integer, "unknown" },
	{ _field_terminator }
};

TAG_BLOCK(
	cache_file_resource_segment_sizes_block,
	sizeof(s_cache_file_resource_segment_sizes),
	NONE)
{
	{ _field_long_integer, "size1" },
	{ _field_long_integer, "size2" },
	{ _field_terminator }
};

TAG_BLOCK(
	cache_file_resource_page_sizes_block,
	sizeof(s_cache_file_resource_page_sizes),
	NONE)
{
	{ _field_long_integer, "total_size" },
	{ _field_block, "segments", &cache_file_resource_segment_sizes_block },
	{ _field_terminator }
};

TAG_BLOCK(
	cache_file_resource_segment_block,
	sizeof(s_cache_file_resource_segment),
	NONE)
{
	{ _field_short_block_index, "primary_page", &cache_file_resource_page_block },
	{ _field_short_block_index, "secondary_page", &cache_file_resource_page_block },
	{ _field_long_integer, "primary_segment_offset" },
	{ _field_long_integer, "secondary_segment_offset" },
	{ _field_short_block_index, "primary_size", &cache_file_resource_page_sizes_block },
	{ _field_short_block_index, "secondary_size", &cache_file_resource_page_sizes_block },
	{ _field_terminator }
};

TAG_GROUP(
	cache_file_resource_layout_table_group,
	k_cache_file_resource_layout_table_group_tag,
	sizeof(s_cache_file_resource_layout_table))
{
	{ _field_block, "compression_codecs", &cache_file_resource_compression_codec_block },
	{ _field_block, "physical_locations", &cache_file_resource_physical_location_block },
	{ _field_block, "pages", &cache_file_resource_page_block },
	{ _field_long_integer, "unknown1" },
	{ _field_long_integer, "unknown2" },
	{ _field_long_integer, "unknown3" },
	{ _field_block, "sizes", &cache_file_resource_page_sizes_block },
	{ _field_block, "segments", &cache_file_resource_segment_block },
	{ _field_terminator }
};

TAG_ENUM(
	cache_file_resource_location_enum,
	k_number_of_cache_file_types + 1)
{
	{ "none", _cache_file_type_none },
	{ "campaign", _cache_file_type_campaign },
	{ "mainmenu", _cache_file_type_mainmenu },
	{ "multiplayer", _cache_file_type_multiplayer },
};

TAG_ENUM(
	cache_file_resource_gestalt_flags_enum,
	k_number_of_cache_file_resource_gestalt_flags)
{
	{ "unknown0", _cache_file_resource_gestalt_unknown0_bit },
	{ "unknown1", _cache_file_resource_gestalt_unknown1_bit },
	{ "unknown2", _cache_file_resource_gestalt_unknown2_bit },
	{ "unknown3", _cache_file_resource_gestalt_unknown3_bit },
	{ "unknown4", _cache_file_resource_gestalt_unknown4_bit },
	{ "unknown5", _cache_file_resource_gestalt_unknown5_bit },
	{ "unknown6", _cache_file_resource_gestalt_unknown6_bit },
	{ "unknown7", _cache_file_resource_gestalt_unknown7_bit },
	{ "unknown8", _cache_file_resource_gestalt_unknown8_bit },
	{ "unknown9", _cache_file_resource_gestalt_unknown9_bit },
	{ "unknown10", _cache_file_resource_gestalt_unknown10_bit },
	{ "unknown11", _cache_file_resource_gestalt_unknown11_bit },
	{ "unknown12", _cache_file_resource_gestalt_unknown12_bit },
	{ "unknown13", _cache_file_resource_gestalt_unknown13_bit },
	{ "unknown14", _cache_file_resource_gestalt_unknown14_bit },
	{ "unknown15", _cache_file_resource_gestalt_unknown15_bit },
};

TAG_BLOCK(
	cache_file_resource_type_block,
	sizeof(s_cache_file_resource_type),
	NONE)
{
	{ _field_array, "guid", &cache_file_resource_guid_array },
	{ _field_short_integer, "unknown10" },
	{ _field_short_integer, "unknown12" },
	{ _field_short_integer, "unknown14" },
	{ _field_short_integer, "unknown16" },
	{ _field_string_id, "name" },
	{ _field_terminator }
};

TAG_BLOCK(
	cache_file_resource_structure_type_block,
	sizeof(s_cache_file_resource_structure_type),
	NONE)
{
	{ _field_array, "guid", &cache_file_resource_guid_array },
	{ _field_string_id, "name" },
	{ _field_terminator }
};

TAG_ENUM(
	cache_file_tag_resource_flags_enum,
	k_number_of_cache_file_tag_resource_flags)
{
	{ "unknown0", _cache_file_tag_resource_unknown0_bit },
	{ "unknown1", _cache_file_tag_resource_unknown1_bit },
	{ "unknown2", _cache_file_tag_resource_unknown2_bit },
	{ "unknown3", _cache_file_tag_resource_unknown3_bit },
	{ "unknown4", _cache_file_tag_resource_unknown4_bit },
	{ "unknown5", _cache_file_tag_resource_unknown5_bit },
	{ "unknown6", _cache_file_tag_resource_unknown6_bit },
	{ "unknown7", _cache_file_tag_resource_unknown7_bit },
};

TAG_BLOCK(
	cache_file_tag_resource_fixup_block,
	sizeof(s_cache_file_tag_resource_fixup),
	NONE)
{
	{ _field_dword_integer, "block_offset" },
	{ _field_dword_integer, "address" },
	{ _field_terminator }
};

TAG_REFERENCE(
	cache_file_tag_resource_parent_tag_reference,
	1)
{
	NONE
};

TAG_BLOCK(
	cache_file_tag_resource_block,
	sizeof(s_cache_file_tag_resource),
	NONE)
{
	{ _field_tag_reference, "parent_tag", &cache_file_tag_resource_parent_tag_reference },
	{ _field_word_integer, "salt" },
	{ _field_char_block_index, "resource_type_index", &cache_file_resource_type_block },
	{ _field_byte_flags, "flags", &cache_file_tag_resource_flags_enum },
	{ _field_long_integer, "fixup_information_offset" },
	{ _field_long_integer, "fixup_information_length" },
	{ _field_long_integer, "secondary_fixup_information_offset" },
	{ _field_short_integer, "unknown20" },
	{ _field_short_block_index, "segment_index", &cache_file_resource_segment_block },
	{ _field_dword_integer, "unknown24" },
	{ _field_block, "resource_fixups", &cache_file_tag_resource_fixup_block },
	{ _field_block, "resource_definition_fixups", &cache_file_tag_resource_fixup_block },
	{ _field_terminator }
};

TAG_GROUP(
	cache_file_resource_gestalt_group,
	k_cache_file_resource_gestalt_group_tag,
	sizeof(s_cache_file_resource_gestalt))
{
	{ _field_short_enum, "location", &cache_file_resource_location_enum },
	{ _field_word_flags, "flags", &cache_file_resource_gestalt_flags_enum },
	{ _field_block, "resource_types", &cache_file_resource_type_block },
	{ _field_block, "resource_structure_types", &cache_file_resource_structure_type_block },
	{ _field_struct, "layout_table", &cache_file_resource_layout_table_group },
	{ _field_block, "tag_resources", &cache_file_tag_resource_block },
	{ _field_terminator }
};
