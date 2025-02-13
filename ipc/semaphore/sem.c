#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/wait.h>

union senum
{
    int val;
    struct semid_ds *buf;
    unsigned short *arrau;
    struct seminfo *__buf;
};

union senum s;

struct sembuf sem_send = {0, 1, SEM_UNDO};
struct sembuf sem_recv = {0, -1, SEM_UNDO};

int main(int argc, char const *argv[])
{

    pid_t pid;
    int id = semget(0xfafa, 1, 0666 | IPC_CREAT);

    if (id < 0)
    {
        printf("Error semger\n");
        return 1;
    }

    s.val = 10;

    if (semctl(id, 0, SETVAL, s) < 0)
    {
        printf("Error semctl");
        return 1;
    }

    if ((pid = fork()) < 0)
    {
        printf("Error fork");
        return 1;
    }

    if (pid == 0)
    {
        int n = 1;
        int semv;

        while (n < 21)
        {
           semv = semctl(id, 0, GETVAL, 0); 
           semop(id, &sem_recv, 1); 
           printf("get task %d : value = %d\n", n, semv);
           n++;
        }
    }
    else
    {
        for (unsigned int i = 0; i < 10; i++)
        {
            semop(id, &sem_send, 1);
            sleep(1);
        }
        wait(NULL);
    }

    return 0;
}
