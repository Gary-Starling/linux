#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <dirent.h>

#define SIZE_STR 256

int main(int argc, char const *argv[])
{
    int cnt = 0; //глобалка количества найденных нами процессов в данном случае "genenv"
    char dirname[SIZE_STR];
    char str[SIZE_STR];       //Для имени файла
    struct dirent **namelist; //Структура списка содержимого каталога
    char *str_ppid = NULL;    //Строчка пида, неизвестной нам длины

    int n = scandir("/proc", &namelist, 0, alphasort);

    if (n < 0)
        perror("scandir");
    else // Открыли каталог
    {
        while (n--)
        {
            //printf("%s\n", namelist[n]->d_name);

            /* Если строчка начинается с цифры, мы нашли процесс */
            if (isdigit(namelist[n]->d_name[0]))
            {
                // printf("this is a porocess dir\n");

                int i = 0;
                int len = 1;                             //длина строчки pid
                str_ppid = (char *)malloc(sizeof(char)); //Выделим подё неё 1 байт
                /* Пройдёмся по всей строке в pid получим её полное название
                без дополнительных символов*/
                for (i = 0; i < sizeof(namelist[n]->d_name); i++)
                {
                    if (namelist[n]->d_name[i])
                    {
                        str_ppid[len - 1] = namelist[n]->d_name[i]; //Пишем символ
                        len++;
                        str_ppid = (char *)realloc(str_ppid, len);
                    }
                    /* Цифры кончились, выходим */
                    if (!isdigit(namelist[n]->d_name[i]))
                        break;
                }
                str_ppid[len - 1] = '\0';

                /*Приклеим путь к имени PID полуим путь*/
                sprintf(dirname, "/proc/%s/status", str_ppid);
                free(str_ppid);

                FILE *ptrFile = fopen(dirname, "r");

                if (ptrFile != NULL)
                {
                    while (fgets(str, sizeof(str), ptrFile) != NULL) // считать символы из файла
                    {

                        //printf("comm -->> %s\n", str);
                        if (strstr(str, "genenv"))
                            cnt++;
                    }
                    fclose(ptrFile);
                }
            }

            free(namelist[n]); //По ГОСТу:)
        }
        free(namelist);
    }

    sprintf(str,"%d\n", cnt);
    fputs(str, stdout);

    return 0;
}