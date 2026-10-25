#include "internal_simply_error.h"

#include <stdio.h>
#include <stdlib.h>

#define RESET "\033[0m"
#define RED "\033[31m"
#define CYAN "\033[36m"

#define TRACEBACK_HEADER RED"┌ ERRORS TRACEBACK ─\n│\n"RESET
#define TRACEBACK_NL RED"│"RESET
#define TRACEBACK_FOOTER RED"\n└───────────────────\n\n"RESET

void	print_error_graph(void)
{
	simply_error	*instance = get_instance();
	int				error_count = instance->error_count;
	
	dprintf(2, TRACEBACK_HEADER);
	while (error_count > 0)
	{
		dprintf(2, TRACEBACK_NL);
		for (int i = 0; i < instance->error_count - error_count; ++i)
			dprintf(2, "  ");
		dprintf(2, "└─");
		--error_count;
		if (instance->errors[error_count].error_msg == NULL)
		{
			instance->errors[error_count].error_msg = "";
			instance->errors[error_count].need_free = false;
		}
		dprintf(2, "%s:"CYAN"%d"RESET":%s: '%s'\n",
			instance->errors[error_count].file,
			instance->errors[error_count].line,
			instance->errors[error_count].function,
			instance->errors[error_count].error_msg
		);
		if (instance->errors[error_count].need_free)
			free(instance->errors[error_count].error_msg);
	}
	dprintf(2, TRACEBACK_NL);
	if (instance->error_count == MAX_ERROR_COUNT)
	{
		dprintf(2, "\n"TRACEBACK_NL);
		dprintf(2, " Too much error emitted, i'm not reporting more. Go fix your code !");
	}
	dprintf(2, TRACEBACK_FOOTER);
}
