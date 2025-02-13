#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char buff_args[1024];
    FILE *pipe_read;

    /* Клеим имя проги и аргументы для вызова popen */
    sprintf(buff_args, "%s %s", argv[1], argv[2]);
   // printf("%s\n", buff_args);

    /* Пробуем открыть трубу */
    if ((pipe_read = popen(buff_args, "r")) == NULL)
    {
        printf("Ошибка открытия трубы.....\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        int c, cnt = 0;
        /* Связь "труба простите" есть, считаем поток */
        while (c != EOF)
        {
            c = fgetc(pipe_read);

            if (c == '0')
                cnt++;
        }
        pclose(pipe_read);

        char str[128];

        sprintf(str, "%d\n", cnt);
        fputs(str, stdout);
    }

    return 0;
}
