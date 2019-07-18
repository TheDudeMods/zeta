#include <commands/commands.h>
#include <commands/tag_commands.h>

/* ---------- public globals */

c_command_context *g_command_context = nullptr;

/* ---------- private globals */

static char name_buffer[1024];
static char input_buffer[1024];

static char *g_command_arg_values[64];

/* ---------- code */

c_command_context::c_command_context(
	char const *name,
	long command_count,
	s_command *commands,
	c_command_context *parent) :
	m_name(name),
	m_command_count(command_count),
	m_commands(commands),
	m_parent(parent)
{
}

s_command *c_command_context::get_command(
	char const *name)
{
	if (!name)
		return nullptr;

	for (auto i = 0; i < m_command_count; i++)
		if (strcmp(name, m_commands[i].name) == 0)
			return &m_commands[i];

	for (auto parent = m_parent; parent; parent = parent->m_parent)
		for (auto i = 0; i < parent->m_command_count; i++)
			if (strcmp(name, parent->m_commands[i].name) == 0)
				return &parent->m_commands[i];

	return nullptr;
}

char *c_command_context::get_name(char *buffer) const
{
	if (m_parent)
		sprintf(buffer, "%s\\%s", m_parent->get_name(buffer), m_name.ascii);
	else
		sprintf(buffer, "%s", m_name.ascii);

	return buffer;
}

void command_loop_execute()
{
	g_command_context = create_tag_command_context();

	while (g_command_context)
	{
		// Display the full command context path
		memset(name_buffer, 0, 1024);
		printf("%s> ", g_command_context->get_name(name_buffer));

		// Read the command input
		memset(input_buffer, 0, 1024);
		fgets(input_buffer, 1024, stdin);

		// Strip newline characters from input buffer
		auto newline = strchr(input_buffer, '\n');
		if (newline) *newline = '\0';

		//
		// Tokenize the command input buffer
		//

		memset(g_command_arg_values, 0, sizeof(char *) * 64);

		auto g_command_arg_count = 0;
		char* arg_token = strtok(input_buffer, " ");

		auto command = g_command_context->get_command(arg_token);

		while (arg_token = strtok(nullptr, " "))
			g_command_arg_values[g_command_arg_count++] = arg_token;

		//
		// Parse and execute the command input
		//

		if (command)
		{
			if (!command->execute(g_command_arg_count, (char const **)g_command_arg_values))
				printf("Usage: %s\n", command->usage);
		}
		else if (strcmp(input_buffer, "exit") == 0)
		{
			auto old_context = g_command_context;
			g_command_context = g_command_context->get_parent();
			delete old_context;
		}

		puts("");
	}
}
