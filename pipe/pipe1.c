#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char const *argv[])
{
    int fd;
    char buff[512];
    char sym = 'x';

    if (argc < 2)
    {
        printf("argc < 2, please enter [read/write]\n");
        return -1;
    }

    if (access("fifo", F_OK) != 0)
    {
        if (mknod("fifo", 777, 0) < 0)
        {
            perror("mknod error");
            return -1;
        }
    }

    if (strcmp("read", argv[1]) == 0)
        fd = open("fifo", O_RDONLY);
    else if (strcmp("write", argv[1]) == 0)
        fd = open("fifo", O_WRONLY);
    else
    {
        printf("arg = [%s], enter [read/write]\n", argv[1]);
        return -1;
    }

    if (fd < 0)
    {
        perror("Error open fifo");
        return -1;
    }

    sym = getchar();
    while (sym = '\n')
    {
        write(fd, sym, 1);
        sym = getchar();
    }
    
     

    return 0;
}
