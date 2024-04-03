
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <stdio.h>
#include "string_up.h"

void string_up(char * str)
{
    for(uint32_t i = 0; i < strlen(str); i++)
     str[i] = toupper(str[i]);
}