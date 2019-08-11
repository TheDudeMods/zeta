#include <cseries/cseries.h>
#include <cseries/cseries_errors.h>

/* ---------- code */

void error(e_error_message_priority priority, char const *message, ...)
{
	assert(priority >= 0 && priority < k_number_of_error_message_priorities);

	//
	// TODO: implement correctly
	//

	va_list va;
	va_start(va, message);
	vsprintf_s(global_temporary_string, message, va);
	va_end(va);

	printf("%s", global_temporary_string);

	switch (priority)
	{
	case _error_message_priority_assert:
	case _error_message_priority_critical:
	case _error_message_priority_out_of_memory:
		abort();
		break;
	case _error_message_priority_warning:
		break;
	}
}
