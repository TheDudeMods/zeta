#include <cseries/cseries.h>

/* ---------- code */

char *tag_to_string(tag value, char *string)
{
	for (long i = 0; i < sizeof(tag); i++)
		string[sizeof(tag) - (i + 1)] = (char)((value >> (i * k_bits_per_byte)) & k_byte_maximum);

	string[sizeof(tag)] = '\0';
	return string;
}

tag string_to_tag(char *string)
{
	tag result = 0;

	for (long i = 0; i < sizeof(tag); i++)
		result |= string[sizeof(tag) - (i + 1)] << (i * k_bits_per_byte);

	return result;
}
