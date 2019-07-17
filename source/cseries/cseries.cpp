#include <cseries/cseries.h>

/* ---------- globals */

long const k_string_id_set_offsets[k_number_of_string_id_sets] =
{
	0x173B, 0x0, 0x4C8, 0xB2D, 0xC0A, 0xC70,
	0xD49, 0xD6F, 0xD74, 0x1433, 0x15A3,
	0x15B7, 0x1619, 0x1631, 0x163E, 0x1667
};

/* ---------- code */

char *tag_to_string(tag value, char *string)
{
	if (!value || value == NONE)
	{
		memcpy(string, "none", 4);
	}
	else
	{
		for (qword i = 0; i < sizeof(tag); i++)
			string[sizeof(tag) - (i + 1)] = (char)((value >> (i * k_bits_per_byte)) & k_byte_maximum);
	}

	string[sizeof(tag)] = '\0';

	return string;
}

tag string_to_tag(const char *string)
{
	tag result = 0;

	for (qword i = 0; i < sizeof(tag); i++)
		result |= string[sizeof(tag) - (i + 1)] << (i * k_bits_per_byte);

	return result;
}
