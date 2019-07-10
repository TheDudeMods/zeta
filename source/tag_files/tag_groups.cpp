#include <tag_files/tag_groups.h>

bool s_tag_group::is_in_group(tag group_tag) const
{
	return tags[0] == group_tag
		|| tags[1] == group_tag
		|| tags[2] == group_tag;
}

bool s_tag_group::is_in_group(s_tag_group &group) const
{
	return tags[0] == group.tags[0]
		|| tags[1] == group.tags[0]
		|| tags[2] == group.tags[0];
}
