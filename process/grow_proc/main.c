#include <signal.h>
#include <stdio.h>
#include <unistd.h>

char *cp;
int n = 0;


void mysignal_handler(int signalno)
{
    n++;
    //printf("SIGSEGV -> %d | addr-> %p | call n -> %d\n", signalno, cp, n);
    sbrk(256);
    signal(SIGSEGV,mysignal_handler);
}



int main(int argc, char const *argv[])
{
    signal(SIGSEGV,mysignal_handler);
    cp = sbrk(0);
    printf("Start brk val = %p\n", cp);
    while(1)
    {
        *cp++=0xff;
    }
    return 0;
}


