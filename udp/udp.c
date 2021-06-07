#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>


/* адрес ip сети, олицетворяющий наш локальный адрес */
struct sockaddr_in local;

int main(int argc, char const *argv[])
{
                    /* ipv4 fix len protcol*/
    int s = socket(AF_INET, SOCK_DGRAM, 0);

    printf("socket = %d\n", s);

    /*Преобразовать адрес лок интерфейс в бин адр */
    inet_aton("127.0.0.1", &local.sin_addr);
    /* host to network short */
    local.sin_port = htons(1234);
    /* */
    local.sin_family = AF_INET;

    int result = bind(s, (struct  sockaddr*) &local, sizeof(local));

    printf("%d\n", result);

    char buf[BUFSIZ];
    read(s, buf, 100);

    printf("%s\nrecived \n", buf);
    
    return 0;
}

