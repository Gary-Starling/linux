#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

const char str[] = "Share msg";

int main(int argc, char const *argv[])
{
    pid_t pid;
    int cnt;
    int pipe_to_par[2], pipe_to_chil[2];
    char buf[256] = {0};

    if (pipe(pipe_to_par) < 0)
    {
        fprintf(stderr, "Pipe parent failed\n");
        return EXIT_FAILURE;
    }

    if (pipe(pipe_to_chil) < 0)
    {
        fprintf(stderr, "Pipe children failed\n");
        return EXIT_FAILURE;
    }

    pid = fork();

    if (pid == 0) /* children */
    {
        close(0);             // close stdin
        dup(pipe_to_chil[0]); // copy fd read
        close(1);             // close stdout
        dup(pipe_to_par[0]);
        close(pipe_to_par[1]);  // close fd wr pipe
        close(pipe_to_chil[0]); // close fd r pipe
        close(pipe_to_par[0]);
        close(pipe_to_chil[1]);

        if ((count = read(0, buf, sizeof(buf)) == 0))
            exit();
        write(1, buff, count);
    }
    else if (pid < 0) /* error */
    {
        fprintf(stderr, "Fork failed\n");
        return EXIT_FAILURE;
    }
    else /* parent */
    {
        close(1);             // close stdout
        dup(pipe_to_chil[1]); //
        close(0);             // close stdin
        dup(pipe_to_par[1]);
        close(pipe_to_par[1]);  // close fd wr pipe
        close(pipe_to_chil[0]); // close fd r pipe
        close(pipe_to_par[0]);
        close(pipe_to_chil[1]);
    }

    for(unsigned int i = 0; i < 15; i++)
    {
        write(1, str, strlen(str));
        read(0, buf, sizeof(buff));
    }

    return 0;
}
