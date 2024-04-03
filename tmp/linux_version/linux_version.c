#include <stdio.h>
#include <stdlib.h>
#include <string_up.h>
#include <reader.h>

int main(int argc, char const *argv[])
{
    char * lin_ver_str = (char *)malloc(STR_SIZE * sizeof(char));

    if(lin_ver_str == NULL)
    {
      fprintf(stderr, "Error allocate memory for string\n");
      return 1;
    }

    if(reader(lin_ver_str))
    {
      fprintf(stderr, "Error read linux version\n");
      return 1;
    }

    
    string_up(lin_ver_str);
    printf("%s\n", lin_ver_str);

    free(lin_ver_str);

    return 0;
}
