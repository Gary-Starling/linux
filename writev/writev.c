#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/uio.h>
#include <unistd.h>

int main()
{
    struct iovec iov[3];
    ssize_t nr;
    int fd, i;
    char *buf[3] = { "Test text number 1.\n", "Second part.\n", "it's end of test.\n"};


    fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }
    /* заполняем три структуры iovec */
    for (i = 0; i < 3; i++)
    {
        iov[i].iov_base = buf[i];
        iov[i].iov_len = strlen(buf[i]) + 1;
    }
    /* записываем все данные в рамках единственного вызова */
    nr = writev(fd, iov, 3);
    if (nr == -1)
    {
        perror("writev");
        return 1;
    }
    printf("wrote %ld bytes\n", nr);
    if (close(fd))
    {
        perror("close");
        return 1;
    }
    return 0;
}