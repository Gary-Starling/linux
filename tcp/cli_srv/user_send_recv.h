#ifndef _USER_SEND_RECV_H_
#define _USER_SEND_RECV_H_
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BSIZE   (1024U)
int usend(int fd, void * buf, ssize_t len, int fl);
int urecv(int fd, void * buf, ssize_t len, int fl);
#endif