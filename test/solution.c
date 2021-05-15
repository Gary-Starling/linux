#include "stddef.h"
#include "solution.h"
#include <string.h>

int stringStat(const char *string, size_t multiplier, int *count)
{
	(*count)++;
	return ( strlen(string) * multiplier );
}