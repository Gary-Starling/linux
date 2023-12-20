#include <stdio.h>
#include <stdlib.h>

//extern char ** environ;

int main(int argc, char const **argv)
{
    /* print all env */
    /*
    int i;

    for (i = 0; environ[i] != NULL; i++)
     printf ("%s\n", environ[i]);

    return 0;
    */

   if(argc < 2)
   {
    fprintf(stderr, "enter env nane\n");
    exit(1);
   }

   char * env_val = (char *)getenv(argv[1]);

   if(env_val == NULL)
    printf("Don't found %s\n", argv[1]);
   else
    printf("%s=%s\n", argv[1], env_val);

   return 0;
}
