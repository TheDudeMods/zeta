#include <datatypes/tag.h>

/* ---------- code */

char *tag_to_string(
	tag m_value,
	char *m_string)
{
	assert(m_string);

	for (int i = 0; i < sizeof(tag); i++)
		m_string[3 - i] = (char)(m_value >> (i * 8));

	m_string[sizeof(tag)] = '\0';
	return m_string;
}

tag string_to_tag(
	char const *m_string)
{
	assert(m_string);
	assert(csstrnlen(m_string, sizeof(tag)) == sizeof(tag));

	tag result = 0;

	for (int i = 0; i < sizeof(tag); i++)
		result |= (tag)(m_string[3 - i] << (i * 8));

	return result;
}
