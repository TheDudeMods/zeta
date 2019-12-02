#include <commands/commands.h>
#include <commands/tag_commands.h>

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>

/* ---------- public globals */

c_command_context *g_command_context = nullptr;

/* ---------- private globals */

static char name_buffer[1024];
static char input_buffer[1024];

static char *g_command_arg_values[64];

/* ---------- code */

c_command_context::c_command_context(
	char const *name,
	long command_set_count,
	s_command_set *command_sets,
	c_cache_file_reach *file,
	c_command_context *parent) :
	m_name(name),
	m_command_set_count(command_set_count),
	m_command_sets(command_sets),
	m_file(file),
	m_parent(parent)
{
}

char *c_command_context::get_name(
	char *buffer) const
{
	if (m_parent)
		sprintf(buffer, "%s\\%s", m_parent->get_name(buffer), m_name.get_buffer());
	else
		sprintf(buffer, "%s", m_name.get_buffer());

	return buffer;

}

long c_command_context::get_command_count() const
{
	long count = 0;

	for (auto i = 0; i < m_command_set_count; i++)
		count += m_command_sets[i].command_count;

	return count;
}

s_command *c_command_context::get_command(
	char const *name)
{
	if (!name)
		return nullptr;

	for (auto i = 0; i < m_command_set_count; i++)
	{
		auto command_set = &m_command_sets[i];

		for (auto j = 0; j < command_set->command_count; j++)
			if (csstrcmp(name, command_set->commands[j].name) == 0)
				return &command_set->commands[j];
	}

	if (m_parent)
		return m_parent->get_command(name);

	return nullptr;
}

c_command_context *c_command_context::get_parent() const
{
	return m_parent;
}

c_cache_file_reach *c_command_context::get_file() const
{
	return m_file;
}

void command_loop_execute(c_cache_file_reach *file)
{
	g_command_context = create_tag_command_context(file);

	while (g_command_context)
	{
		// Display the full command context path
		csmemset(name_buffer, 0, 1024);
		printf("%s> ", g_command_context->get_name(name_buffer));

		// Read the command input
		csmemset(input_buffer, 0, 1024);
		fgets(input_buffer, 1024, stdin);

		// Strip newline characters from input buffer
		auto newline = csstrchr(input_buffer, '\n');
		if (newline) *newline = '\0';

		//
		// Tokenize the command input buffer
		//

		csmemset(g_command_arg_values, 0, sizeof(char *) * 64);

		auto g_command_arg_count = 0;

		auto command_name = csstrtok(input_buffer, " ");
		auto command = g_command_context->get_command(command_name);

		for (char *arg_token = nullptr; arg_token = csstrtok(nullptr, " "); )
			g_command_arg_values[g_command_arg_count++] = arg_token;

		//
		// Parse and execute the command input
		//

		if (command)
		{
			if (!command->execute(g_command_arg_count, (char const **)g_command_arg_values))
				printf("Usage: %s\n", command->usage);
		}
		else if (csstrcmp(input_buffer, "exit") == 0)
		{
			auto old_context = g_command_context;
			g_command_context = g_command_context->get_parent();
			delete old_context;
		}
		else
		{
			printf("ERROR: \"%s\" is not a valid command name.\n", command_name);
		}

		puts("");
	}
}
