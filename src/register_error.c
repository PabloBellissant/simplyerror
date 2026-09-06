#include "internal_simply_error.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

int vasprintf(char **ret, const char *format, va_list ap); 

__attribute__((format(printf, 4, 5)))
void	register_error(const char *file_name, int line, const char *function, const char *format, ...)
{
	va_list	info;
	va_start(info, format);

	simply_error	*instance = get_instance();
	if (instance->error_count == 0)
		on_exit(print_error_graph, NULL);
	if (instance->error_count == MAX_ERROR_COUNT)
		return ;
	instance->errors[instance->error_count].need_free = true;
	if (vasprintf(&instance->errors[instance->error_count].error_msg, format, info) == -1)
	{
		instance->errors[instance->error_count].error_msg = NULL;
		instance->errors[instance->error_count].need_free = false;
	}
	instance->errors[instance->error_count].file = file_name;
	instance->errors[instance->error_count].line = line;
	instance->errors[instance->error_count].function = function;
	++instance->error_count;
	va_end(info);
}
