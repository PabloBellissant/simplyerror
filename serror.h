#ifndef SERROR_H
# define SERROR_H

__attribute__((format(printf, 4, 5)))
void	_register_error(const char *file_name, int line, const char *function, const char *format, ...);

#ifdef NDEBUG
	#define REGISTER_ERROR(...) ((void *)0)
#else
	#define REGISTER_ERROR(...) _register_error(__FILE__, __LINE__, __func__, __VA_ARGS__)
#endif

#define REGISTER_USER_ERROR(...) _register_error(__FILE__, __LINE__, __func__, __VA_ARGS__)

#ifdef NDEBUG
	#define CHECK_ERROR(expr, ...) ((void *)0)
#else
	#define CHECK_ERROR(expr, ...) if (expr) {REGISTER_ERROR(__VA_ARGS__); return (-1);}
#endif

#define CHECK_USER_ERROR(expr, ...) if (expr) {REGISTER_USER_ERROR(__VA_ARGS__); return (-1);}

#define SERROR_IMPLEMENTATION
#ifdef SERROR_IMPLEMENTATION

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define MAX_ERROR_COUNT 16

#define RESET "\033[0m"
#define RED "\033[31m"
#define CYAN "\033[36m"

#define TRACEBACK_HEADER RED"┌ ERRORS TRACEBACK ─\n│\n"RESET
#define TRACEBACK_NL RED"│"RESET
#define TRACEBACK_FOOTER RED"\n└───────────────────\n\n"RESET

struct	_simply_error_info
{
	char		*error_msg;
	const char	*file;
	const char	*function;
	int			line;
	bool		need_free;
};

struct	_simply_error
{
	struct _simply_error_info	errors[MAX_ERROR_COUNT];
	int							error_count;
};

struct _simply_error	*_get_instance()
{
	static struct _simply_error	simply_error = {0};
	return (&simply_error);
}

void	_print_error_graph(int return_value, void *data)
{
	(void) data;
	struct _simply_error	*instance = _get_instance();
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

int vasprintf(char **ret, const char *format, va_list ap); // Not standard

__attribute__((format(printf, 4, 5)))
void	_register_error(const char *file_name, int line, const char *function, const char *format, ...)
{
	va_list	info;
	va_start(info, format);

	struct _simply_error	*instance = _get_instance();
	if (instance->error_count == 0)
		on_exit(_print_error_graph, NULL);
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

#endif

#endif

