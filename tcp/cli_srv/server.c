#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "user_send_recv.h"

#define PORT ((unsigned short)(1234))

// TODO: while send all msg/ while recv all msg

int main(int argc, char const *argv[])
{
    int sd, ns, res_at;
    char buf[1024] = {0};

    struct sockaddr_in serv_info;
    struct sockaddr_in cli_info;

    char client_name[128];
    socklen_t cli_len = sizeof(cli_info);

    size_t iter = 1;
    size_t msg_len;

    /* creating socket file descriptor */
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0)
    {
        perror("Error opening socket");
        exit(EXIT_FAILURE);
    }

    /* set server settings */
    serv_info.sin_family = AF_INET;
    serv_info.sin_port = htons(PORT);
    serv_info.sin_addr.s_addr = INADDR_ANY;

    if (bind(sd, (struct sockaddr *)&serv_info, sizeof(serv_info)) < 0)
    {
        perror("Error bind");
        exit(EXIT_FAILURE);
    }

    if (listen(sd, 10) < 0)
    {
        close(sd);
        perror("Error listen");
        exit(EXIT_FAILURE);
    }

    if ((ns = accept(sd, (struct sockaddr *)&cli_info, &cli_len)) < 0)
    {
        close(sd);
        perror("Error accept");
        exit(EXIT_FAILURE);
    }

    inet_ntop(AF_INET, &cli_info.sin_addr, client_name, sizeof(client_name));
    printf("Client = %s connected\n", client_name);

    while (1)
    {
        printf("Start session...\n");

        /* recive data */
        if (urecv(ns, buf, sizeof(buf), 0) == -1)
        {
            printf("Server recive error\n");
            break;
        }

        printf("Recived msg: %s", buf);
        if (strstr(buf, "exit") != NULL)
            break;
        memset(buf, 0, sizeof(buf));

        /* send data  */
        sprintf(buf, "@Ack from the server:%ld", iter++);
        if (usend(ns, buf, strlen(buf) + 1, 0) == -1)
        {
            printf("Server send error\n");
            break;
        }
        memset(buf, 0, sizeof(buf));
        printf("Stop session...\n\n");
    }

    printf("Stop server\n");

    close(ns);
    close(sd);

    exit(EXIT_SUCCESS);
}
