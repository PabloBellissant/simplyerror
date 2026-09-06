#include "internal_simply_error.h"
#include "simply_error.h"

#include <stdlib.h>
#include <stdio.h>

// __attribute__((format(printf, 1, 2)))
void	register_error(const char *msg, const char *file_name, int line, const char *function)
{
	simply_error	*instance = get_instance();
	if (instance->error_count == 0)
		on_exit(print_error_graph, NULL);
	if (instance->error_count == MAX_ERROR_COUNT)
		return ;
	instance->errors[instance->error_count].error_msg = msg;
	instance->errors[instance->error_count].file = file_name;
	instance->errors[instance->error_count].line = line;
	instance->errors[instance->error_count].function = function;
	++instance->error_count;
}
