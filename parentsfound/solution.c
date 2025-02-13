#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <dirent.h>

#define SIZE_STR 256

int cnt = 0;

void scan_dir(const char *pid);

int main(int argc, char const *argv[])
{

    char out[SIZE_STR];

    //if (argc < 2)
      //  return 0;

    scan_dir(argv[1]);

    if(cnt!=0)
    cnt++;

    sprintf(out,"%d\n", cnt);
    fputs(out, stdout);
    return 0;
}

void scan_dir(const char *pid_inpu_str)
{
    FILE *ptrFile;

    struct dirent **namelist; //Структура списка содержимого каталога
    char dirname_str[SIZE_STR];
    char *str_pid = NULL; //Строчка пида, неизвестной нам длины
    char str[SIZE_STR];   //Для имени файла
    char str_ppid[20];

    sprintf(str_ppid, "PPid:\t%s", pid_inpu_str);

    int n = scandir("/proc", &namelist, NULL, alphasort);

    if (n < 0)
        perror("scandir");
    else // Открыли каталог
    {
        while (n--)
        {
            // printf("%s\n", namelist[n]->d_name);

            /* Если строчка начинается с цифры, мы нашли процесс */
            if (isdigit(namelist[n]->d_name[0]))
            {
                //printf(" this is a porocess dir\n");
                int i = 0;
                int len = 1;                            //длина строчки pid
                str_pid = (char *)malloc(sizeof(char)); //Выделим подё неё 1 байт
                /* Пройдёмся по всей строке получим её полное название(PID)
                без дополнительных символов*/
                for (i = 0; i < sizeof(namelist[n]->d_name); i++)
                {
                    if (namelist[n]->d_name[i])
                    {
                        str_pid[len - 1] = namelist[n]->d_name[i]; //Пишем символ
                        len++;
                        str_pid = (char *)realloc(str_pid, len);
                    }
                    /* Цифры кончились, выходим */
                    if (!isdigit(namelist[n]->d_name[i]))
                        break;
                }
                str_pid[len - 1] = '\0';

                /*Приклеим путь к имени PID получим путь*/
                sprintf(dirname_str, "/proc/%s/status", str_pid);
                // printf("%s\n", dirname_str);

                ptrFile = fopen(dirname_str, "r");

                if (ptrFile != NULL)
                {
                    while (fgets(str, sizeof(str), ptrFile) != NULL) // считать символы из файла
                    {
                        if (strstr(str, str_ppid))
                        {   /* В /proc/ нашли pid у которго  ppid совпал сискомым
                            т.е. это наш батя, отлично, возьмём теперь найденный pid 
                            и сунем в эту же функцию, которая просканирует всё снова(рекурсия)
                            и скажет для кого этот pid есть ppid*/
                            // printf("%s - > %s\n", str, str_ppid);
                            cnt++;
                            scan_dir(str_pid);
                        }
                    }
                    free(str_pid);
                    fclose(ptrFile);
                }
            }

            free(namelist[n]);
        }
        free(namelist);
    }
}
