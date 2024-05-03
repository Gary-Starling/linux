#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define PORT ((unsigned short)(1234))

int main(int argc, char const *argv[])
{
    int sd, ns, res_at;
    char buf[1024];

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

    printf("Client = %s\n", client_name);
    printf("Start session...\n");
    while (1)
    {
        recv(ns, buf, sizeof(buf),0);
        printf("server recived: -> %s\n", buf);
        send(ns, "Server resp\n", strlen("Server resp\n"), 0);

        if (strstr(buf, "exit") != NULL)
            break;
        memset(buf, 0, sizeof(buf));
    }

    printf("Stop server\n");

    close(ns);
    close(sd);
    
    exit(0);
}
