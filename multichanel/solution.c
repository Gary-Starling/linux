#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>
#include <stdlib.h>

/* global summ */
int summ = 0;
int fifo1_fl1 = 1, fifo1_fl2 = 1;

void read_and_report(int fd, int *fifo1_fl)
{

    char buff[4096];

    //printf("FD %d is ready to read\n", fd);
    int bytes = read(fd, buff, sizeof(buff) - 1);

    if (bytes == 0)
    {
        *fifo1_fl = 0;
    }
    else
    {
        buff[bytes] = '\0';
        summ += atoi(buff);
    }

    buff[bytes] = 0;
    //printf("Get %d bytes from %d : %s\n", bytes, fd, buff);
    //printf("summ = %d\n", summ);
}

int main(int argc, char const *argv[])
{

    int f1 = open("./in1", O_RDONLY | O_NONBLOCK);
    int f2 = open("./in2", O_RDONLY | O_NONBLOCK);

    if ((f1 == -1) || (f2 == -1))
    {
        printf("%d\n", errno);
        perror("Error:");
        printf("Error with opening pipes %d %d\n", f1, f2);
        return 0;
    }

    //printf("Descr: %d %d\n", f1, f2);
    // return 0;

    fd_set read_set;

    while (fifo1_fl1 && fifo1_fl2)
    {

        FD_ZERO(&read_set);

        if (fifo1_fl1)
            FD_SET(f1, &read_set);

        if (fifo1_fl2)
            FD_SET(f2, &read_set);

        int result = select(f2 + 1, &read_set, NULL, NULL, NULL);

        if (result)
        {
            if (FD_ISSET(f1, &read_set))
                read_and_report(f1, &fifo1_fl1);

            if (fifo1_fl1 == 0)
            {

                FD_CLR(f1, &read_set);
                close(f1);
            }

            if (FD_ISSET(f2, &read_set))
                read_and_report(f2, &fifo1_fl2);

            if (fifo1_fl2 == 0)
            {

                FD_CLR(f2, &read_set);
                close(f2);
            }
        }
    }

    char str_out[10];

    sprintf(str_out, "%d\n", summ);
    fputs(str_out, stdout);

    return 0;
}
