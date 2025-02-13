#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const **argv)
{
    char buff[100];
    size_t sz = 0;

    if (argc != 2)
    {
        printf("\nPls enter\n\t%s filename\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY | O_NOFOLLOW | __O_PATH);
    perror("fd");
    printf("fd=%d\n", fd);
    sz = read(fd, buff,100);

    printf("sz=%ld\n",sz);

    return 0;
}
