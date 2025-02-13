#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    pid_t pid;
    int cnt, c_cnt = 0;
    /*  r[0] w[1]           r[0] w[1]*/
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
        close(0);               // close stdin
        dup(pipe_to_chil[0]);   // copy fdr
        close(1);               // close stdout
        dup(pipe_to_par[1]);    // copy fdw
        close(pipe_to_par[1]);  // close fd wr pipe
        close(pipe_to_chil[0]); // close fd r pipe
        close(pipe_to_par[0]);  // ,,
        close(pipe_to_chil[1]); // ..

        while (1)
        {
            c_cnt++;
            if ((cnt = read(0, buf, sizeof(buf))) == 0)
                exit(EXIT_SUCCESS);
            sprintf(buf, "children recived msg %d, response ->", c_cnt);
            write(1, buf, strlen(buf));
        }
    }
    else if (pid < 0) /* error */
    {
        fprintf(stderr, "Fork failed\n");
        return EXIT_FAILURE;
    }
    else /* parent */
    {
        close(1);               // close stdout
        dup(pipe_to_chil[1]);   // copy fd(w)
        close(0);               // close stdin
        dup(pipe_to_par[0]);    // copy fd(r)
        close(pipe_to_par[1]);  // close fd r pipe
        close(pipe_to_chil[1]); // close fd w pipe
        close(pipe_to_chil[0]); // ..
        close(pipe_to_par[0]);  // ..
    }

    for (unsigned int i = 0; i < 15; i++)
    {
        sprintf(buf, "Paren sended msg %d ->", i);
        write(1, buf, strlen(buf));
        read(0, buf, sizeof(buf));
    }

    return 0;
}
