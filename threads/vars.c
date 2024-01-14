#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char const *argv[])
{
    int i = 111;
    int exit_status;
    pid_t status = fork();

    //child
    if(!status)
    {
        i++;
        printf("Child var(i) = %d\n",i);
        return 0;
    }

    //parent
    wait(&exit_status);
    printf("Parent var(i)=%d\n",i);
    return 0;
}
