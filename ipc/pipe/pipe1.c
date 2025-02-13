#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void read_fifo(int fd);
void write_fifo(int fd);

int main(int argc, char const *argv[])
{
    int fd;

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
    {
        fd = open("fifo", O_RDONLY);
        if (fd < 0)
            goto err;
        read_fifo(fd);
    }
    else if (strcmp("write", argv[1]) == 0)
    {
        fd = open("fifo", O_WRONLY);
        if (fd < 0)
            goto err;
        write_fifo(fd);
    }
    else
    {
        printf("arg = [%s], enter [read/write]\n", argv[1]);
        return -1;
    }

    return 0;
err:
    perror("Error open fifo");
    return -1;
}

void write_fifo(int fd)
{
    char sym = 'x';

    printf("Enter [~] to exit program\n");
    while ((sym = getchar()) != '~')
        write(fd, &sym, 1);
}

void read_fifo(int fd)
{
    char byte;
    int res;

    while (1)
    {
        res = read(fd, &byte, 1);
        if (res < 0) break;
        if(res == 1) putchar(byte);
        usleep(200);
    }
}