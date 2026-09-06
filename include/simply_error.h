#pragma once

__attribute__((format(printf, 4, 5)))
void	register_error(const char *file_name, int line, const char *function, const char *format, ...);

#ifdef NDEBUG
	#define REGISTER_ERROR(...) ((void *)0)
#else
	#define REGISTER_ERROR(...) register_error(__FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#endif

#define REGISTER_USER_ERROR(...) register_error(__FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
