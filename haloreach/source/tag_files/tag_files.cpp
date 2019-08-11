#include <cache/cache_files.h>
#include <tag_files/tag_files.h>
#include <tag_files/tag_groups.h>

/* ---------- code */

void tag_iterator_initialize(
	s_tag_iterator *iterator,
	tag group_tag)
{
	assert(iterator);

	iterator->index = 0;
	iterator->group_tag = group_tag;
}

long tag_iterator_next(
	c_cache_file_reach *file,
	s_tag_iterator *iterator)
{
	assert(iterator);

	auto group_tag = iterator->group_tag;
	auto tags_header = file->get_tags_header();

	for (; iterator->index < tags_header->tag_count; iterator->index++)
	{
		auto index = iterator->index;
		auto instance = file->get_tag_instance(index);

		if (!instance || !instance->address || instance->group_index == NONE)
			continue;

		auto group = file->get_tag_group(instance->group_index);

		if (group->is_in_group(group_tag))
			return index;
	}

	return NONE;
}
