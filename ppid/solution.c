#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>

#define SIZE_STR 128

int main(int argc, char const *argv[])
{
    pid_t my_pid = getpid(); //id текущешго процесса
    char str[SIZE_STR];      //Для имени файла

    sprintf(str, "/proc/%d/status", my_pid);

#ifdef DEBUG
    fputs(str, stdout);
    printf("\n");
#endif

    FILE *ptrFile = fopen(str, "r");

    if (ptrFile != NULL) //Открыли
    {
#ifdef DEBUG
        printf("path <%s> opened\n", str);
#endif

        while (fgets(str, sizeof(str), ptrFile) != NULL) // считать символы из файла
        {                                                /* Считываем строчку до \n */
            //Ищем без учёта регистра
            if (strncasecmp(str, "ppid:", 5) == 0)
            {
                //Нашли строчку ppid:
                char *str_ppid = NULL;                   //Строчка пида, неизвестной нам длины
                int len = 1;                             //длина строчки ppid
                str_ppid = (char *)malloc(sizeof(char)); //Выделим подё неё 1 байт
                int i = 0;
                /* Пройдёмся по всей строке в поисках ppid цифр*/
                for (i = 0; i < SIZE_STR - 1; i++)
                {
                    if (isdigit(str[i]))
                    {
                        str_ppid[len - 1] = str[i]; //Пишем символ
                        len++;
                        str_ppid = (char *)realloc(str_ppid, len);
                    }

                    if (str[i] == '\n')
                        break;
                }
                str_ppid[len - 1] = '\n'; //Конец строки
                len ++ ;
                str_ppid = (char *)realloc(str_ppid, len);
                str_ppid[len - 1] = '\0';
                fputs(str_ppid, stdout);
                break;
            }
        }
    }
    else
        printf("error open path -> %s\n", str);

    return 0;
}
