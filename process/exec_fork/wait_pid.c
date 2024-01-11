#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

#define COUNTER (45UL)

int main(int argc, char const *argv[])
{
    /* code */
    int st; // status

    /* child */
    if (!fork())
    {
        for (unsigned int i = 0; i < COUNTER; i++)
        {
            fprintf(stderr, "/");
            sleep(1);
        }
        exit(5);
    }

    /* parent */
    while (1)
    {
        if (!waitpid(-1, &st, WNOHANG))
            fprintf(stderr, "+");
        else
        {
            fprintf(stderr, "(exit)\n");
            break;
        }

        sleep(2);
    }

    if (WIFEXITED(st))
        fprintf(stderr, "Exit with code = %d\n", WIFEXITED(st));
    else if (WIFSIGNALED(st))
        fprintf(stderr, "Exit by signal\n");

    return 0;
}
