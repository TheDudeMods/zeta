#pragma once

#include <cseries/cseries.h>
#include <datatypes/enum.h>
#include <datatypes/flags.h>
#include <sound/sound_classes.h>
#include <tag_files/tag_groups.h>

/* ---------- constants */

enum
{
	k_sound_group_tag = 'snd!',
	k_sound_looping_group_tag = 'lsnd',
};

/* ---------- types */

enum e_sound_sample_rate
{
	_sound_sample_rate_22khz,
	_sound_sample_rate_44khz,
	_sound_sample_rate_32khz,
	k_number_of_sound_sample_rates
};

enum e_sound_encoding
{
	_sound_encoding_mono,
	_sound_encoding_stereo,
	_sound_encoding_surround,
	_sound_encoding_5_1_surround,
	k_number_of_sound_encodings
};

#pragma pack(push, 1)
struct s_sound_platform_codec
{
	c_enum<e_sound_sample_rate, char> sample_rate;
	c_enum<e_sound_encoding, char> encoding;
	char : 8;
};
#pragma pack(pop)
static_assert(sizeof(s_sound_platform_codec) == 0x3);

struct s_sound_definition_playback_parameters
{

};

struct s_sound_cache_file_gestalt_definition
{
	c_tag_block<s_sound_platform_codec> platform_codecs;

};

enum e_cache_file_sound_flags
{
	_cache_file_sound_fit_to_adpcm_blocksize_bit,
	_cache_file_sound_split_long_sound_into_permutations_bit,
	_cache_file_sound_unknown2_bit,
	_cache_file_sound_unknown3_bit,
	_cache_file_sound_unknown4_bit,
	_cache_file_sound_unknown5_bit,
	_cache_file_sound_unknown6_bit,
	_cache_file_sound_unknown7_bit,
	_cache_file_sound_unknown8_bit,
	_cache_file_sound_unknown9_bit,
	_cache_file_sound_unknown10_bit,
	_cache_file_sound_unknown11_bit,
	_cache_file_sound_unknown12_bit,
	_cache_file_sound_unknown13_bit,
	_cache_file_sound_unknown14_bit,
	_cache_file_sound_unknown15_bit,
	k_number_of_cache_file_sound_flags
};

struct s_cache_file_sound_definition
{
	c_flags<e_cache_file_sound_flags, ushort> flags;
	c_enum<e_sound_class, char> sound_class;
	char : 8;

};
