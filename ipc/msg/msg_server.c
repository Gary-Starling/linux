#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#define MSGKEY (0xff)

typedef struct
{
    long type;
    char text[1024];
} sMsg;

int main(int argc, char const *argv[])
{
    sMsg msg;
    int msgid, pid, *pint;
    time_t ctime;
    struct tm *now;

    if (msgid = msgget(MSGKEY, IPC_CREAT | 0777) == -1)
    {
        printf("Error msgget IPC_CREAT\n");
        return 1;
    }

    while (1)
    {
        msgrcv(msgid, &msg, 1024, 1, 0);
        pint = (int *)msg.text; // copy pointer from msg
        pid = *pint;
        printf("Request from proc(pid):%d\n", pid);

        msg.type = 1;
        ctime = time(NULL);
        now = localtime(&ctime);
        sprintf( msg.text + sizeof(int), "Date : %d.%d.%d\nTime: %d:%d:%d\n",
                now->tm_mday, now->tm_mon + 1, now->tm_year + 1900, now->tm_hour, now->tm_min, now->tm_sec);
        
        msgsnd(msgid, &msg, sizeof(int) + strlen(msg.text + sizeof(int)), 0);
    }
}
