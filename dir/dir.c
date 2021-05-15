#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    DIR *dir;
    FILE *ptrFile;
    int status;

    status = mkdir("/home/gary/embeded/linux/dir/dir1", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    if (status == -1)
    {
        printf("Error make dir\n");
        return 0;
    }
    else
        printf("create dir ok\n");

    dir = opendir("/home/gary/embeded/linux/dir/dir1");

    if (dir == NULL)
    {
        printf("Error open dir\n");
        return 0;
    }

    chdir("/home/gary/embeded/linux/dir/dir1");

    char namefile[20];
    char *numfile;

    for (int i = 0; i < 10; i++)
    {
        sprintf(numfile, "%d", i);
        snprintf(namefile, sizeof(namefile), "%s%s", "file", numfile);

        if ((ptrFile = fopen(namefile, "w")) == NULL)
            printf("not created %s\n", namefile);
        else
            printf("created %s\n", namefile);
    }

    return 0;
}
