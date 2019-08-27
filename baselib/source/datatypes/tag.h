#pragma once

#include <cseries/cseries.h>

/* ---------- types */

typedef unsigned long tag;
static_assert(sizeof(tag) == 0x4);

/* ---------- prototypes/TAG.CPP */

char *tag_to_string(tag m_value, char *m_string);
tag string_to_tag(char const *m_string);
