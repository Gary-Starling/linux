#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#define BUF_SIZE    (1024U)

char buffer[BUF_SIZE];

int main(int argc, char const *argv[])
{
    int inFd, outFd;
    ssize_t bytes;

    if(argc < 3)
    {
        fprintf(stderr,"Pls, write 2 args, <input file> and <output_file>\n");
        return 1;
    }

    inFd  = open(argv[1], O_RDONLY);

    if(inFd == -1)
    {
        fprintf(stderr,"Error open  (%s)\n", argv[1]);
        return 1;
    }


    outFd = open(argv[2], O_WRONLY, O_CREAT, O_TRUNC, 0640);

    if(outFd == -1)
    {
        fprintf(stderr,"Error open  (%s)\n", argv[2]);
        return 1;
    }

    while((bytes = read(inFd, buffer, BUF_SIZE)) > 0)
        write(outFd, buffer, bytes);

    close(inFd);
    close(outFd);

    return 0;
}
