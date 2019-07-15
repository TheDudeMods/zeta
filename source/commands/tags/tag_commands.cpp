#include <commands/tags/tag_commands.h>
#include <commands/tags/list_tags.h>

/* ---------- globals */

static c_list_tags_command *list_tags_command;

/* ---------- code */

void tag_commands_initialize(c_command_context *context, c_cache_file *cache_file)
{
	if (!list_tags_command)
		list_tags_command = new c_list_tags_command(cache_file);

	if (!context)
		return;

	context->add_command(list_tags_command);
}

void tag_commands_dispose()
{
	if (list_tags_command)
		delete list_tags_command;
}
