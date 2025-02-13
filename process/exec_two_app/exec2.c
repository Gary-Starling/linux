#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    char * prog_args[] = {"arg1", "arg2", "arg3", NULL};
    char * prog_env[] = { "USER=new_user", "Home=/home/new_user", NULL};

    printf("Old PID: %d\n", getpid());
    execve("./prog", prog_args, prog_env);
    fprintf(stderr,"Error execve\n");

    return 1;
}
