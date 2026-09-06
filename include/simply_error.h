#pragma once

#define MAX_ERROR_COUNT 16

typedef struct	error_info
{
	const char	*error_msg;
	const char	*file;
	const char	*function;
	int			line;
}	error_info;

typedef struct	simply_error
{
	int			error_count;
	error_info	errors[MAX_ERROR_COUNT];
}	simply_error;

void	register_error(const char *msg, const char *file_name, int line, const char *function);
void	print_error_graph(int return_value, void *data);

#define REGISTER_ERROR(msg) register_error(msg, __FILE__, __LINE__, __FUNCTION__)
