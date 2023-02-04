#include <stdlib.h>
#include <stdio.h>
#include "myenv.h"

void myprintenv(const char * name)
{
    char * val = getenv(name);

    if(val == NULL) 
    {
      printf("Variable doesn't exist\n");
      return;
    }

    printf("%s = %s\n", name, val);
}