#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include "user_send_recv.h"

#define PORT ((unsigned short)(1234))

int main(int argc, char const *argv[])
{
    struct sockaddr_in server;
    struct hostent *s;
    int sd, res_at;
    char buf[BSIZE] = {0};
    int ress, resr;

    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0)
    {
        perror("Error opening socket");
        exit(EXIT_FAILURE);
    }

    s = gethostbyname("127.0.0.1");

    if (s == NULL)
    {
        perror("Error get hostname");
        exit(EXIT_FAILURE);
    }

    printf("Host-name:%s\n", s->h_name);

    memset((char *)&server, 0, sizeof(server));
    server.sin_port = htons(PORT);
    server.sin_family = AF_INET;
    inet_aton(s->h_name, &server.sin_addr);

    if (connect(sd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Error connect");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        /* send to server */
        fgets(buf, sizeof(buf), stdin);
        if (strstr(buf, "exit") != NULL)
            break;
        ress = usend(sd, buf, strlen(buf) + 1, 0);
        if (ress == -1)
        {
            perror("Error send");
            exit(EXIT_FAILURE);
        }
        memset(buf, 0, sizeof(buf));

        /* recive from the server */
        resr = urecv(sd, buf, sizeof(buf), 0);
        if (resr == -1)
        {
            perror("Error recv");
            exit(EXIT_FAILURE);
        }
        printf("%s\n", buf);
        memset(buf, 0, sizeof(buf));
    }

    close(sd);
    exit(EXIT_SUCCESS);
}
