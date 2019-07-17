#include <cseries/cseries.h>
#include <cache/cache_files.h>
#include <commands/commands.h>
#include <commands/tags/tag_commands.h>

/* ---------- globals */

static char name_buffer[1024];
static char input_buffer[1024];

static char *g_command_arg_values[64];

/* ---------- code */

int main()
{
	puts("Zeta v0.0.1");

	cache_files_open();

	auto command_context = create_tag_command_context();

	while (command_context)
	{
		// Display the full command context path
		memset(name_buffer, 0, 1024);
		printf("%s> ", command_context->get_name(name_buffer));

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

		auto command = command_context->get_command(arg_token);

		while (arg_token = strtok(nullptr, " "))
			g_command_arg_values[g_command_arg_count++] = arg_token;

		//
		// Parse and execute the command input
		//

		if (command)
		{
			command->execute(g_command_arg_count, (char const **)g_command_arg_values);
		}
		else if (strcmp(input_buffer, "exit") == 0)
		{
			auto old_context = command_context;
			command_context = command_context->get_parent();
			delete old_context;
		}

		puts("");
	}

	cache_files_close();

	return EXIT_SUCCESS;
}
