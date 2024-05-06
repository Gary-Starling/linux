#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define PORT ((unsigned short)(1234))

//TODO: while send all msg/ while recv all msg

int main(int argc, char const *argv[])
{
    int sd, ns, res_at;
    char buf[1024];
    const char *server_msg = "Ack from the server\n";
    const unsigned int smsg_len = strlen(server_msg) + 1;

    struct sockaddr_in serv_info;
    struct sockaddr_in cli_info;

    const char *srv_msg = "server recived data";
    size_t len_srv_msg = sizeof(srv_msg);

    char client_name[128];
    socklen_t cli_len;

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
        if (recv(ns, buf, sizeof(buf), 0) == -1)
        {
            printf("Server recive error\n");
            break;
        }

        printf("Recived msg: %s\n", buf);


        if (send(ns, server_msg, smsg_len, 0) == -1)
        {
            printf("Server send error\n");
            break;
        }

        if (strstr(buf, "exit") != NULL)
            break;

        printf("Stop session...\n");

        memset(buf, 0, sizeof(buf));
    }

    printf("Stop server\n");

    close(ns);
    close(sd);

    exit(0);
}
