#include "internal_simply_error.h"

simply_error	*get_instance()
{
	static simply_error	simply_error = {0};
	return (&simply_error);
}


