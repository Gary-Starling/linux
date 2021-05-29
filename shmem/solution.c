#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int key1_reg = atoi(argv[1]);
    int key2_reg = atoi(argv[2]);

    int shmid1 = 0, shmid2 = 0, shmid3 = 0; /* IPC дескриптор для области разделяемой памяти */
    int *shared1 = NULL, *shared2 = NULL, *shared3 = NULL;

    /* Передаём ключ региона, размер, флаг чтения
    Если всё ок, то получим дескриптор */
    shmid1 = shmget(key1_reg, 1000 * sizeof(char), 0400);
    shmid2 = shmget(key2_reg, 1000 * sizeof(char), 0400);

    key_t uni_key = 55955;
    shmid3 = shmget(uni_key, 1000 * sizeof(char), IPC_CREAT | 0666);

    /* Получим указатель на введённый регион
    по аналогии сделаем с другими*/
    if (shmid1 != -1)
        shared1 = shmat(shmid1, NULL, SHM_RDONLY);
    else
        return 0;

    if (shmid2 != -1)
        shared2 = shmat(shmid2, NULL, SHM_RDONLY);
    else
        return 0;

    if (shmid3 != -1)
        shared3 = shmat(shmid3, NULL, 0);
    else
        return 0;

    int i = 0;

    for (i = 0; i < 100; i++)
    {
        shared3[i] = shared2[i] + shared1[i];
    }

    
    printf("%i\n",(int)uni_key);

    shmdt(shared1);
    shmdt(shared2);
    shmdt(shared3);

    return 0;
}
