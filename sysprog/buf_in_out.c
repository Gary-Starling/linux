#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

char buf[4096];

int main(int argc, char const *argv[])
{
    FILE *stream;
    int fd;
    int sym;

    fd = open("/home/gary/embeded/linux/sysprog/hello.txt", O_RDONLY);
    if (fd == -1)
    {
        return 1;
        /* ошибка */
    }

    stream = fdopen(fd, "r");

    if (!stream)
    {
        return 1;
        /* ошибка */
    }

    while (1)
    {
        // Чтение одного байта из файла
        sym = fgetc(stream);

        //Проверка на конец файла или ошибку чтения
        if (sym == EOF)
        {
            // Проверяем что именно произошло: кончился файл
            // или это ошибка чтения
            if (feof(stream) != 0)
            {
                //Если файл закончился, выводим сообщение о завершении чтения
                //и выходим из бесконечного цикла
                printf("\nЧтение файла закончено\n");
                break;
            }
            else
            {
                //Если при чтении произошла ошибка, выводим сообщение об
                // ошибке и выходим из бесконечного цикла
                printf("\nОшибка чтения из файла\n");
                break;
            }
        }
        //Если файл не закончился, и не было ошибки чтения
        //выводим код считанного символа на экран
        printf("%c", sym);
    }

    fclose(stream);

}
