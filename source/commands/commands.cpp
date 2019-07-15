#include <commands/commands.h>

/* ---------- code */

c_command::c_command(
	char const *name,
	char const *usage,
	char const *description,
	bool inherited) :
	m_name(name),
	m_usage(usage),
	m_description(description),
	m_inherited(inherited)
{
}

c_command_context::c_command_context(
	char const *name,
	c_command_context *parent) :
	m_name(name),
	m_command_count(0),
	m_commands(nullptr),
	m_parent(parent)
{
}

c_command_context::~c_command_context()
{
	if (m_commands)
		delete[] m_commands;
}

void c_command_context::add_command(
	c_command *command)
{
	for (auto i = 0; i < m_command_count; i++)
	{
		if (m_commands[i] == nullptr)
		{
			m_commands[i] = command;
			return;
		}
	}

	auto commands = new c_command *[++m_command_count];

	for (auto i = 0; i < m_command_count - 1; i++)
		commands[i] = m_commands[i];

	commands[m_command_count - 1] = command;
	m_commands = commands;
}

c_command *c_command_context::get_command(
	char const *name)
{
	for (auto i = 0; i < m_command_count; i++)
		if (m_commands[i] && strcmp(name, m_commands[i]->get_name()) == 0)
			return m_commands[i];

	for (auto parent = m_parent; parent; parent = parent->m_parent)
		for (auto i = 0; i < parent->m_command_count; i++)
			if (parent->m_commands[i] && strcmp(name, parent->m_commands[i]->get_name()) == 0)
				return parent->m_commands[i];

	return nullptr;
}

char *c_command_context::get_name(char *buffer) const
{
	if (m_parent)
		sprintf(buffer, "%s\\%s", m_parent->get_name(buffer), m_name);
	else
		sprintf(buffer, "%s", m_name);

	return buffer;
}
