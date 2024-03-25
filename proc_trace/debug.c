/* trce.c compile with -static key */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/wait.h>


int main(int argc, char const *argv[])
{
    int i, pid;
    int status;
    int addr;

    sscanf(argv[1], "%x", &addr);
    printf("ptrace data addr %p\n", addr);

    if ((pid = fork()) == 0)
    {
        /* child */
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        execl("./trace", "trace", 0, NULL);
        printf("Error child proc\n");
        exit(1);
    }

    /* wait child */
    waitpid(pid, &status, 0);

    for (unsigned int i = 0; i < 32; i++)
    {

        if (ptrace(PTRACE_POKEDATA, pid, addr, i * 10) == -1)
        {
            /* if we'll be here , some error occur */
            printf("Error2, %d\n", i);
            exit(1);
        }
        addr += sizeof(int);
        ptrace(PTRACE_SINGLESTEP, pid, 1, 0);
        waitpid(pid, &status, 0);
    }

    ptrace(PTRACE_CONT, pid, 1, 0);

    exit(0);
}
