#include <stdio.h>
#include <string.h>
#include "reader.h"

int reader(char * str)
{
    int i;

    FILE * fp = fopen("/proc/version", "r");

    if(fp == NULL) 
    {
      fprintf(stderr, "can't open /proc/version\n");
      return 1;
    }

    for(i = 0; i < STR_SIZE; i++)
    {
      if((str[i] = fgetc(fp)) == EOF)
        break;
    }

    fclose(fp);

    return 0;
}