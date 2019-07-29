#pragma once

#include <cseries/cseries.h>

/* ---------- structures */

struct s_tag_resource_structure
{
	dword address;
	dword runtime_address;
	dword definition_address;
};
static_assert(sizeof(s_tag_resource_structure) == 0xC);

/* ---------- inline headers */

#include <tag_files/tag_resource_structure.inl>
