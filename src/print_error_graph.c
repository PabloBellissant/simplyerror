#include "internal_simply_error.h"

#include <stdio.h>
#include <stdlib.h>

#define RESET "\033[0m"
#define RED "\033[31m"
#define CYAN "\033[36m"

#define TRACEBACK_HEADER RED"┌ ERRORS TRACEBACK ─\n│\n"RESET
#define TRACEBACK_NL RED"│"RESET
#define TRACEBACK_FOOTER RED"\n└───────────────────\n\n"RESET

void	print_error_graph(int return_value, void *data)
{
	(void) data;
	simply_error	*instance = get_instance();
	int				error_count = instance->error_count;
	
	printf(TRACEBACK_HEADER);
	while (error_count > 0)
	{
		printf(TRACEBACK_NL);
		for (int i = 0; i < instance->error_count - error_count; ++i)
			printf("  ");
		printf("└─");
		--error_count;
		if (instance->errors[error_count].error_msg == NULL)
		{
			instance->errors[error_count].error_msg = "";
			instance->errors[error_count].need_free = false;
		}
		printf("%s:"CYAN"%d"RESET":%s: '%s'\n",
			instance->errors[error_count].file,
			instance->errors[error_count].line,
			instance->errors[error_count].function,
			instance->errors[error_count].error_msg
		);
		if (instance->errors[error_count].need_free)
			free(instance->errors[error_count].error_msg);
	}
	printf(TRACEBACK_NL"\n");
	if (instance->error_count == MAX_ERROR_COUNT)
	{
		printf(TRACEBACK_NL);
		printf(" Too much error emitted, i'm not reporting more. Go fix your code !\n");
	}
	printf(TRACEBACK_NL);
	printf(" Program returned with value "CYAN"%d"RESET"\n", return_value);
	printf(TRACEBACK_NL);
	printf(TRACEBACK_FOOTER);
}
