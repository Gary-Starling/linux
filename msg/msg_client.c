#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
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

    if ((msgid = msgget(MSGKEY, 0777)) == -1)
        return 1;

    msg.type = 1;

    pid = getpid();
    pint = (int *)msg.text;
    *pint = pid; // copy pid to msg txt

    printf("enter \"req\" for get time or \"exit\"\n");

    while (1)
    {

    input:
        if (fgets(msg.text + sizeof(int), 10, stdin) != NULL)
        {
            if (!(strcmp(msg.text + sizeof(int), "req\n")))
                msgsnd(msgid, &msg, sizeof(int) + 10, 0);
            else if (!(strcmp(msg.text + sizeof(int), "exit\n")))
            {
                printf("Exit\n");
                return 0;
            }
            else
                goto input;
        }
        else
            return 1;

        msgrcv(msgid, &msg, 1024, 1, 0);
        printf("Server response: %s\n", msg.text + sizeof(int));
    }

    return 0;
}
