/*
Постановка задачи.
Необходимо реализовать клиент-серверное приложение под Linux.
Клиент - программа, запускаемая из консоли
Сервер - демон, корректно завершающийся по сигналам SIGTERM и SIGHUP.
Клиент должен передать содержимое текстового файла через TCP.
Сервер должен принять и сохранить в файл.
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/wait.h>

struct sockaddr_in local;
int serv_sock, client_sock;

void mysignal_handler(int signal)
{
    pid_t pid_deamon = getpid();

    switch (signal)
    {
    case SIGTERM:
        printf("%d\n", pid_deamon); // Выведем PID демона
        close(client_sock);
        close(serv_sock);
        exit(0); // Завершим работу
        break;

    case SIGHUP:
        printf("%d\n", pid_deamon);
        close(client_sock);
        close(serv_sock);
        exit(0);
        break;

    default:
        break;
    }
}

void sig_child(int sig) //--функция ожидания завершения дочернего процесса
{
    pid_t pid;
    int stat;

    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
    {
    }
    return;
}

int server(void)
{
    pid_t pid;
    char cwd[1024];

    /* создание нового процесса */
    pid = fork();

    if (pid == -1)
        exit(EXIT_FAILURE);
    else if (pid != 0)
        exit(EXIT_SUCCESS); // Родитель заверщает свою работу

    /* создание нового сеанса и группы процессов */
    if (setsid() == -1)
        exit(EXIT_FAILURE);

    /* установка в качестве рабочего каталога корневого каталога */
    if (chdir("/") == -1)
        exit(EXIT_FAILURE);

    /* перенаправление дескрипторов файла 0,1,2 в /dev/null */
    close(STDIN_FILENO);

    pid_t pid_deamon = getpid();
    /* Покажем свой pid */
    printf("Deamon start, pid = %d\n", pid_deamon);
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);
    /* Далее, создание tcp сервера */
    serv_sock = socket(AF_INET, SOCK_STREAM, 0); // TCP socket

    /*Преобразовать адрес лок интерфейс в бин адр */
    inet_aton("127.0.0.1", &local.sin_addr);
    local.sin_port = htons(2048);
    local.sin_family = AF_INET;

    int res = bind(serv_sock, (struct sockaddr *)&local, sizeof(local));

    if (res == -1)
    {
        printf("Error\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Socket created : 127.0.0.1:2048\n");
    }

    /* Слушаем сокет, максимум 5 запросов одновременно*/
    listen(serv_sock, 5);

    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    signal(SIGTERM, mysignal_handler);
    signal(SIGHUP, mysignal_handler);

    char buf[BUFSIZ] = {0};
    pid_t pid_proc;
    FILE *fptr;

    while (1) /* Тут демон что-то делает */
    {
        signal(SIGCHLD, sig_child); //--если клиент уже поработал и отключился ждем завершение его дочернего процесса
        client_sock = accept(serv_sock, NULL, NULL);

        if (client_sock > 0)
        {
            if ((pid_proc = fork()) == 0) //--то мы создаем копию нашего сервера
            {

                fptr = fopen("./recive.txt", "wb");
                if (fptr == NULL)
                    exit(-1);
                do
                {
                    ssize_t cnt_byte_read = recv(client_sock, buf, BUFSIZ, 0);
                    if (cnt_byte_read == 0)
                        break;
                    if (cnt_byte_read < 0)
                        break;
                    fwrite(buf, cnt_byte_read, 1, fptr);
                } while (1);

                fclose(fptr);
                close(client_sock);
                exit(0);
            }
            else if (pid_proc > 0)
                close(client_sock);
        }
    }

    close(client_sock);
    close(serv_sock);

    exit(0);
}

int client(void)
{
    /* Создадимм сокет */
    int s = socket(AF_INET, SOCK_STREAM, 0);

    inet_aton("127.0.0.1", &local.sin_addr);
    local.sin_port = htons(2048);
    /* */
    local.sin_family = AF_INET;

    /* not bind ос сделает bind во время connect
    пытаемся соединить сокет с сервером */
    int res;
    res = connect(s, (struct sockaddr *)&local, sizeof(local));

    if (res == -1)
    {
        printf("Error connect\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Сonnection to 127.0.0.1:2048 success \n");
    }

    FILE *fptr;

    fptr = fopen("./send.txt", "r");

    if (fptr == NULL)
    {
        printf("Error open send.txt\n");
        exit(EXIT_FAILURE);
    }
    else
        printf("send.txt open\n");

    fseek(fptr, 0, SEEK_END);
    size_t fsize = ftell(fptr);
    rewind(fptr);

    char *buff = (char *)malloc(sizeof(char) * fsize);

    if (buff == NULL)
    {
        printf("Memory error\n");
        exit(EXIT_FAILURE);
    }

    size_t result = fread(buff, 1, fsize, fptr);

    if (result != fsize)
    {
        printf("Error read\n");
        exit(EXIT_FAILURE);
    }

    /* Отправим содержимое серверу */
    write(s, buff, strlen(buff));

    printf("send\n");

    fclose(fptr);
    close(s);
    exit(0);
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Not arguments\nUse : %s [c or s] c-client s-server\n", argv[0]);
        return 0;
    }

    if (argv[1][0] == 's')
    {
        server();
    }
    else if (argv[1][0] == 'c')
    {
        client();
    }
    else
    {
        printf("no client or server selected \n");
        return -1;
    }

    return 0;
}
