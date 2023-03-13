#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

struct sThread_args {
    char * name;
    int id;
};

typedef struct sThread_args ThreadArg;

void * thread1f(void * args)
{
    ThreadArg * InputArg = (ThreadArg *)args;

    while(1)
    {
     fprintf(stdout, "Running is %s with id = %d\n", InputArg->name, InputArg->id);
     sleep(1);
     pthread_exit(NULL);
    }
    //return 0;
}

void * thread2f(void * args)
{
    ThreadArg * InputArg = (ThreadArg *)args;
    while(1)
    {
     fprintf(stdout, "Running is %s with id = %d\n", InputArg->name, InputArg->id);
     sleep(1);
    }
    //return 0;
}


int main(int argc, char const *argv[])
{
    pthread_t thread1, thread2;
    ThreadArg t1_arg, t2_arg;

    t1_arg.name = "Thread1";
    t1_arg.id = 0;
    t2_arg.name = "Thread2";
    t2_arg.id = 1;

    if(pthread_create(&thread1, NULL, thread1f, &t1_arg) != 0)
    {
        fprintf(stderr, "Error create Thread1");
        return 1;
    }

    if(pthread_create(&thread2, NULL, thread2f, &t2_arg) != 0)
    {
        fprintf(stderr, "Error create Thread2");
        return 1;
    }

    sleep(6);
    pthread_cancel(thread1);

    if(!pthread_equal(pthread_self(), thread1))
        pthread_join(thread1, NULL);

    fprintf(stdout, "End\n");

    //PTHREAD_CANCELED


    return 0;
}
