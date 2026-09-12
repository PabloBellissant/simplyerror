#pragma once

#include <stdbool.h>

#define MAX_ERROR_COUNT 16

typedef struct	error_info
{
	char		*error_msg;
	const char	*file;
	const char	*function;
	int			line;
	bool		need_free;
}	error_info;

typedef struct	simply_error
{
	int			error_count;
	error_info	errors[MAX_ERROR_COUNT];
}	simply_error;

simply_error	*get_instance();
void			print_error_graph();
