#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#define     BUFFER_SIZE     (1024U) //1KB

char buf[BUFFER_SIZE + 1];

int main(int argc, char const *argv[])
{
    ssize_t bytes; 
    int fd;


    fd = open("/home/gary/linux/file_read/test.txt", O_RDONLY);
    
    if(fd == -1)
        fprintf(stderr, "Error opening file\n");

    while ((bytes = read(fd, buf, BUFFER_SIZE)) > 0)
    {
        buf[bytes] = '\0';
        printf("%s", buf);
    }

    close(fd);
    return 0;
    
}
