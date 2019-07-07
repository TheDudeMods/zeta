/*
CSERIES.CPP
*/

/* ---------- headers */

#include <cseries/cseries.h>

/* ---------- code */

bool cseries_initialize()
{
	return true;
}

void cseries_dispose()
{
}

char *tag_to_string(
	tag value,
	char *string)
{
	for (int i = 0; i < sizeof(tag); i++)
		string[sizeof(tag) - i - 1] = (value >> (i * k_byte_bits)) & k_byte_maximum;

	string[sizeof(tag)] = '\0';

	return string;
}

tag string_to_tag(
	char const *string)
{
	tag result = 0;

	for (int i = 0; i < sizeof(tag); i++)
		result |=  string[sizeof(tag) - i - 1] << (i * k_byte_bits);

	return result;
}
