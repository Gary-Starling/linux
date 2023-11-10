#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    if(-1 == nice(5))
    {
        fprintf(stderr, "nice error\n");
        return 1;
    }

    execlp("bash", "bash", NULL);
    fprintf(stderr, "error exec\n");
    
    return 0;
}
