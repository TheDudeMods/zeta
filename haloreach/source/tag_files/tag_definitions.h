#pragma once

#include <cseries/cseries.h>
#include <tag_files/tag_definitions_base.h>

class c_cache_file_reach;

/* ---------- prototypes/TAG_DEFINITIONS.CPP */

ulonglong field_get_size(e_field_type type, void *definition);
void field_print(c_cache_file_reach *file, e_field_type type, char const *name, void *definition, void *address);
void field_next(s_field_definition **out_field, void **out_address);
bool field_parse(c_cache_file_reach *file, e_field_type type, char const *name, void *definition, void *address, long arg_count, char const **arg_values);

void *struct_print(c_cache_file_reach *file, s_struct_definition *definition, void *address, char const *filter);
s_field_definition *struct_get_field(s_struct_definition *definition, char const *name, void **out_address);

s_tag_group_definition *tag_group_definition_get(tag group_tag);
