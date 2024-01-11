#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

extern char **environ;

int main(int argc, char const *argv[])
{
    pid_t res;
    char * sleep_args[] = {
        "sleep",
        "5",
        NULL
    };

    res = fork();

    if(res == -1)
    {
        fprintf(stderr, "fork error\n");
        return 1;
    }

    if(res== 0)
    {
        execve("/bin/sleep", sleep_args, environ);
        fprintf(stderr, "execve error\n");
        return 1;
    }

    fprintf(stderr, "I'm parent with PID: %d\n", getpid());


    return 0;
}
