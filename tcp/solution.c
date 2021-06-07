#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char const *argv[])
{
    struct sockaddr_in local;

    int ss = socket(AF_INET, SOCK_STREAM, 0);
    int cs;

    /*Преобразовать адрес лок интерфейс в бин адр */
    inet_aton("127.0.0.1", &local.sin_addr);
    /* host to network short */
    int port = atoi(argv[1]);
    local.sin_port = htons(port);
    /* */
    local.sin_family = AF_INET;
    /* bind нужен, сервер не может начать слушать соединения
    пока не опредилил порт на котором он это делает*/
    int result = bind(ss, (struct sockaddr *)&local, sizeof(local));

    //printf("%d\n", result);
    /* Слушаем сокет, количествое клиентов пытающихся установить соединение*/
    listen(ss, 4);

    /* Приниает соединение снаружи
    возращает новый сокет который будет связан с
    клиентом, который попытался сделать коннект*/
    cs = accept(ss, NULL, NULL);

    char buf[BUFSIZ] = {0};
    char temp = 0;
    int cnt_byte_read = 0;

    while (1)
    {
        int j = 0, i = 0;

        cnt_byte_read = read(cs, buf, BUFSIZ);

        if (strstr(buf, "OFF\n"))
            break;
        // printf("%s\n", buf);
        /* Пузырька с ударением на Ы*/
        for (i = 0; i < cnt_byte_read - 1; i++)
        {
            for (j = 0; j < cnt_byte_read- 2; j++) //
            {
                if (buf[j] < buf[j + 1])
                {
                    temp = buf[j];
                    buf[j] = buf[j + 1];
                    buf[j + 1] = temp;
                }
            }
        }

        write(cs, buf, cnt_byte_read);

        cnt_byte_read = 0;
        i = 0;
        j = 0;
        memset(buf, '\0', BUFSIZ);
    }

    close(cs);
    close(ss);

    return 0;
}
