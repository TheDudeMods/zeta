#pragma once

#include <cseries/cseries.h>

/* ---------- structures */

struct s_tag_iterator
{
	tag group_tag;
	long index;
};

/* ---------- prototypes/TAG_FILES.CPP */

void tag_iterator_initialize(s_tag_iterator *iterator, tag group_tag);
long tag_iterator_next(s_tag_iterator *iterator);

/* ---------- inline headers */

#include <tag_files/tag_iterator.inl>
