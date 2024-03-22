#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/wait.h>

#define TR_SETUP 0
#define TR_WRITE 5
#define TR_RESUME 7

int addr;

int main(int argc, char const *argv[])
{
    int i, pid;

     sscanf(argv[1], "%x", &addr);
     printf("ptrace data addr %p\n", addr);

    if ((pid = fork()) == 0)
    {
        ptrace(TR_SETUP, 0, 0, 0);
        execl("./trace", "trace", 0, NULL);
        exit(0);
    }

    for (unsigned int i = 0; i < 32; i++)
    {
        wait(NULL);
        if (ptrace(TR_WRITE, pid, (int *)0x4c3300, i) == -1)
            exit(0);
        addr += sizeof(int);
    }

    ptrace(TR_RESUME, pid, 1, 0);

    // return 0;
}
