#include <signal.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>


void mysignal_handler(int signalno)
{
    printf("Calll with %d\n", signalno);
   // exit(0);
}


int main(int argc, char const *argv[])
{
    pid_t my_pid = getpid();

    signal(SIGINT, mysignal_handler);

    while(1)
        {
            printf("I am: %d\n", my_pid);
            usleep(1000000);
        }
    return 0;
}
