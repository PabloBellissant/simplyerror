#include <stdio.h>
#include <errno.h>
#include <string.h>
#define SERROR_IMPLEMENTATION
#include "serror.h"

int	parse_obj(const char *path)
{
	FILE *f= fopen(path, "r");
	CHECK_USER_ERROR("Failed to open input file '%s', %s", path, strerror(errno));
	// ...
	fclose(f);
	return (0);
}

int main(void)
{
	// Classic user error (wrong input file)
	{
		int	result = parse_obj("rabbit.obj");
		if (result != 0)
		{
			REGISTER_USER_ERROR("Failed to parse obj file.");
			return (1);
		}
	}
	// System error, like out of memory.
	{
		char *str = malloc(sizeof(char) * 2048);
		CHECK_ERROR(!str, "Failed to allocate memory, %s", strerror(errno)); // <-- Will be remplaced by (void *)0, if NDEBUG is defined.
	}
	return (0);
}
