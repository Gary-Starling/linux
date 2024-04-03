#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>


union senum {
    int val;
    struct semid_ds *buf;
    unsigned short * arrau;
    struct seminfo *__buf;
}

union senum s;

struct sembuf sem1 = {0, 1, SEM_UNDO};
struct sembuf sem2 = {0, -1, SEM_UNDO};

int main(int argc, char const *argv[])
{
    const char * send_str = "Get semaphore";
    pid_t pid;
    int id = semget(0xfafa, 1, 0666 | IPC_CREAT);

    if(id < 0)
    {
        printf("Error semger\n");
        return 1;
    }

    s.val = 1;

    if(semctl(id, 0, SETVAL, s) < 0)
    {
        printf("Error semctl");
        return 1;
    }

    if((pid=fork()) < 0)
    {
        printf("Error fork");
        return 1;
    }

    if(pid == 0)
    {

    }
    else
    {
        semop(id, &sem1, 1);
    }



    return 0;
}
