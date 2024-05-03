#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

#define PORT ((unsigned short)(1234))

int main(int argc, char const *argv[])
{
    struct sockaddr_in server;
    struct hostent *s;
    int sd, res_at;
    char buf[1024];

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

    bzero((char *)&server, sizeof(server));
    server.sin_port = htons(PORT);
    server.sin_family = AF_INET;
    bcopy((char *)s->h_addr, (char *)&server.sin_addr.s_addr,
          s->h_length);

    if (connect(sd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Error connect");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        fgets(buf, sizeof(buf), stdin);
        send(sd, buf, strlen(buf), 0);
        memset(buf, 0, sizeof(buf));

        recv(sd, buf, sizeof(buf), 0);
        printf("server recived: -> %s\n", buf);
        memset(buf, 0, sizeof(buf));
    }

    close(sd);
    return 0;
}
