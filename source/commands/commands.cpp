#include <commands/commands.h>

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
		sprintf(buffer, "%s\\%s", m_parent->get_name(buffer), m_name);
	else
		sprintf(buffer, "%s", m_name);

	return buffer;
}
