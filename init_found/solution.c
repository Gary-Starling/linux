#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>

#define SIZE_STR 128

FILE *ptrFile;

void pid_found(const char *str);

int main(int argc, char const *argv[])
{
    char filename[128];

    if (argc < 2 || argc > 2)
    {
        printf("pls enter program name and pid like ./solution pidname\n");
        return 0;
    }

    

    fputs(argv[1], stdout);
    printf("\n");

    sprintf(filename, "/proc/%s/status", argv[1]);
    pid_found(filename);

    return 0;
}

void pid_found(const char *str)
{
    char fname[256];

    ptrFile = fopen(str, "r");

    if (ptrFile != NULL) //Открыли
    {
#ifdef DEBUG
        printf("path <%s> opened\n", str);
#endif

        while (fgets(fname, sizeof(fname), ptrFile) != NULL) // считать символы из файла
        {                                                    /* Считываем строчку до \n */
            //Ищем без учёта регистра
            if (strncasecmp(fname, "ppid:", 5) == 0)
            {
                //Нашли строчку ppid:
                char *str_ppid = NULL;                   //Строчка пида, неизвестной нам длины
                int len = 1;                             //длина строчки ppid
                str_ppid = (char *)malloc(sizeof(char)); //Выделим подё неё 1 байт
                int i = 0;
                /* Пройдёмся по всей строке в поисках ppid цифр*/
                for (i = 0; i < SIZE_STR - 1; i++)
                {
                    if (isdigit(fname[i]))
                    {
                        str_ppid[len - 1] = fname[i]; //Пишем символ
                        len++;
                        str_ppid = (char *)realloc(str_ppid, len);
                    }

                    if (fname[i] == '\n')
                        break;
                }
                str_ppid[len - 1] = '\0';

                if (strcmp(str_ppid, "0") == 0)
                    break;

                sprintf(fname, "%s\n", str_ppid);
                fputs(fname, stdout);
                sprintf(fname, "/proc/%s/status", str_ppid);
                free(str_ppid);
                fclose(ptrFile);
                pid_found(fname);

                break;
            }
        }
    }
    else
        printf("error open path -> %s\n", str);
}
