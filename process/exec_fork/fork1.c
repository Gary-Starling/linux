#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    pid_t res = fork();

    if (res == -1)
    {
        fprintf(stderr, "Error fork\n");
        return 1;
    }

    if(res == 0)
    {
        printf("I'm child with pid = %d\n", getpid());
        printf("my ppid = %d\n", getppid());
    }
    else
    {
        printf("I'm parent with pid = %d\n", getpid());
        printf("my ppid = %d\n", getppid());
    }
    
    return 0;
}
