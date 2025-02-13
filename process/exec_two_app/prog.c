#include <stdio.h>
#include <unistd.h>


extern char **environ;
int main(int argc, char const *argv[])
{
    int i;
    printf("ENVIRONMENT:\n");
    for (i = 0; environ[i] != NULL; i++)
    {
        printf("env[%d]=%s\n", i, environ[i]);
    }

    printf("ARGUMENTS:\n");
    for (i = 0; i < argc; i++)
    {
        printf("argv[%d]=%s\n", i, argv[i]);
    }
    
    printf("New PID: %d\n", getpid());
    
    return 0;
}
