#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char *argv[])
{

    extern int opterr;
    opterr = 0;

    int is_brackets = 0;
    int optindex = 0;
    int opchar = 0;
    int lenght = 0;
    int status = 0;

    struct option opts[] = {
        {"query", required_argument, 0, 'q'},
        {"longinformationrequest", no_argument, 0, 'i'},
        {"version", no_argument, 0, 'v'},
        {0, 0, 0, 0},
    };

    while ((opchar = getopt_long(argc, argv, "q:iv", opts, &optindex)) != -1)
    {
        switch (opchar)
        {
        case 0:
            //printf("-\n");

            break;

        case 'q':
            // printf("+\n");
            break;

        case 'i':
            // printf("+\n");
            break;

        case 'v':
            // printf("+\n");
            break;

        case '?':
            status++;
            break;
        }
    }

    if (status == 0)
        printf("+\n");
    else
        printf("-\n");

    return 0;
}
