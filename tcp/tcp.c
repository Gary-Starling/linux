#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int run = 1; //

struct sockaddr_in local;

void mysignal_handler(int signalno)
{
    printf("\nExit signal %d\n", signalno);
    run = 0;
    exit(0);
}

int server(void)
{
    int ss = socket(AF_INET, SOCK_STREAM, 0);
    int cs;

    /*Преобразовать адрес лок интерфейс в бин адр */
    inet_aton("127.0.0.1", &local.sin_addr);
    /* host to network short */
    local.sin_port = htons(1234);
    /* */
    local.sin_family = AF_INET;
    /* bind нужен, сервер не может начать слушать соединения
    пока не опредилил порт на котором он это делает*/
    int result = bind(ss, (struct sockaddr *)&local, sizeof(local));

    printf("%d\n", result);
    /* Слушаем сокет, количествое клиентов пытающихся установить соединение*/
    listen(ss, 4);

    /* Приниает соединение снаружи
    возращает новый сокет который будет связан с
    клиентом, который попытался сделать коннект*/
    cs = accept(ss, NULL, NULL);

    char buf[BUFSIZ] = {0};

    while (1)
    {
        read(cs, buf, BUFSIZ);
        printf("%s\n", buf);

        if (strstr(buf, "exit"))
            break;
    }

    close(cs);
}

int client(void)
{

    signal(SIGINT, mysignal_handler);

    /* Создвём сокет */
    int s = socket(AF_INET, SOCK_STREAM, 0);

    /*Преобразовать адрес лок интерфейс в бин адр */
    inet_aton("127.0.0.1", &local.sin_addr);
    /* host to network short */
    local.sin_port = htons(1234);
    /* */
    local.sin_family = AF_INET;

    /* not bind ос сделает bind во время connect
    пытаемся соединить сокет с сервером */
    connect(s, (struct sockaddr *)&local, sizeof(local));

    char buf[BUFSIZ] = {0};

    while (run)
    {
        fgets(buf, BUFSIZ, stdin);
        write(s, buf, strlen(buf));
    }

    close(s);
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Use : %s [s|c]\n", argv[0]);
        return 0;
    }

    if (argv[1][0] == 's') //server
    {
        server();
    }
    else if (argv[1][0] == 'c')
    {
        client();
    }
    else
    {
        printf("not chosen c or s\n");
        return -1;
    }

    return 0;
}
