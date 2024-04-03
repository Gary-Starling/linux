#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int fd;
    mode_t fmode = S_IRUSR;
    
    if(argc < 2)
    {
        fprintf(stderr, "Too few arg(s)\n");
        return 1;
    }
    else
    {
        fd = creat(argv[1], fmode);
        if(fd == -1)
        {
            fprintf(stderr, "Error create file (%s)\n", argv[1]);
            return 1;
        }
        
        close(fd);
        return 0;
    }

    return 0;
}
