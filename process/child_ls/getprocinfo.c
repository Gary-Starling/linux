#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>

int main(int argc, char const *argv[])
{
    int uid = getuid();
    struct passwd *pwdp = getpwuid(uid);

    if(pwdp == NULL)
    {
        fprintf(stderr, "Wrong username\n");
        return 1;
    }

    printf("PID: %d\n", getpid());
    printf("PPID: %d\n", getppid());
    printf("UID: %d\n", getuid());
    printf("usarname: %s\n", pwdp->pw_name);
    sleep(15);
    return 0;
}
