#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void * print_msg_func(void * arg)
{
    int a = *(int *)arg;
    fprintf(stdout, "Argiments : %d\n", a);
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t thread;
    int arg, res;
    
    if(argc < 2)
    {
        fprintf(stderr, "To few arg(s)\n");
        return 1;
    }

    arg = atoi(argv[1]);

    res = pthread_create(&thread, NULL, print_msg_func, &arg);
    if(res !=0 )
    {
        fprintf(stderr, "Error\n");
        return 1;
    }

    fprintf(stdout, "Buy!\n");
    while(1);

    return 0;
}
