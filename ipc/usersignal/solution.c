#include <signal.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>


void mysignal_handler(int signalno)
{
    static int sigusr1 = 0, sigusr2 = 0; 

    switch (signalno)
    {
    case SIGTERM:
        printf("%d %d\n", sigusr1, sigusr2);
         exit(0);
        break;

    case SIGUSR1:
        sigusr1++;
        break;

    case SIGUSR2:
       sigusr2++;
        break;

    default:
        break;
    }

    //printf("Calll with %d\n", signalno);
    
}

int main(int argc, char const *argv[])
{
    //pid_t my_pid = getpid();

    signal(SIGTERM, mysignal_handler);
    signal(SIGUSR1, mysignal_handler);
    signal(SIGUSR2, mysignal_handler);

    while (1)
    {
        //printf("I am: %d\n", my_pid);
        //usleep(100);
    }
    return 0;
}
