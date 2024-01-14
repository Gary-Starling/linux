#include <stdio.h>
#include <unistd.h>

extern char **environ;

int main(int argc, char const *argv[])
{
    
    char *uname_args[] = {"uname", "-a", NULL};

    execve("/bin/uname", uname_args, environ);
    fprintf(stderr, "Error execve\n");
    return 0;
}
