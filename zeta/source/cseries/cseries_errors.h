#pragma once

#include <cseries/cseries.h>

/* ---------- types */

enum e_error_message_priority
{
	_error_message_priority_out_of_memory,
	_error_message_priority_warning,
	_error_message_priority_assert,
	_error_message_priority_critical,
	k_number_of_error_message_priorities
};

/* ---------- prototypes/ERRORS.CPP */

void error(e_error_message_priority priority, char const *message, ...);
