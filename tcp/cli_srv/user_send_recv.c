#include "user_send_recv.h"

/**
 *
 */
int usend(int fd, void *buf, ssize_t len, int fl)
{
    ssize_t total = 0;
    ssize_t sentb = 0;
    char slen[5] = {0}; /* preamble 5 bytes will be size of msg [1][2][3][4][/0] */

    /* check size */
    if (len > BSIZE)
    {
        printf("Data size > %d error\n", BSIZE);
        return -1;
    }

    /* send len of msg */
    sprintf(slen, "%ld", len);
    if (send(fd, slen, 5, fl) < 0)
        return -1;

    while (total < len)
    {
        sentb = send(fd, buf + total, len - total, fl);
        if (sentb == -1)
            return -1;
        total += sentb;
    }

    return 0;
}

/**
 *
 */
int urecv(int fd, void *buf, ssize_t len, int fl)
{
    ssize_t total = 0;
    ssize_t recvb = 0;
    long int msgl;

    if (len > BSIZE)
    {
        printf("Data size error\n");
        return -1;
    }

    /* get msg size */
    if (recv(fd, buf, 5, 0) < 0)
        return -1;
    msgl = strtol(buf, NULL, 10);

    while ((total < len) && (recvb < msgl))
    {
        recvb = recv(fd, buf + total, len - total, 0);

        if (recvb == -1)
            return -1;
        else if (recvb == 0)
            return 0;

        total += recvb;
    }

    return 0;
}