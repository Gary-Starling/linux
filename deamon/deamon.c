#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>

int main(void)
{
    pid_t pid;
    int i;
    /* создание нового процесса */
    pid = fork();

    if (pid == -1)
        return -1;
    else if (pid != 0)
    {
       // printf("pid deamon : %d \n", pid);
        exit(EXIT_SUCCESS);
    }
    /*Тут основная задача, родитель уже не работает*/
    umask(0);

    /* создание нового сеанса и группы процессов */
    if (setsid() == -1)
        return -1;

    /* установка в качестве рабочего каталога корневого каталога */
    if (chdir("/") == -1)
        return -1;

    /* перенаправление дескрипторов файла 0,1,2 в /dev/null */
    close(STDIN_FILENO);

    pid_t pid_deamon = getpid();
    
    printf("%d\n", pid_deamon);

    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    /* всякие действия демона... */
    while(1)
    {
        sleep(10000);
    }
    return 0;
}