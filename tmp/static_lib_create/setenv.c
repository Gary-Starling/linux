#include <stdlib.h>
#include <stdio.h>
#include "myenv.h"

void mysetenv(const char * name, const char * val)
{
    printf("Setting variable %s\n", name);
    setenv(name, val, 1);
}