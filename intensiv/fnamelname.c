/*Написать программу, которая редактирует массив имен и фамилий. Если имя или фамилия начинаются с маленькой буквы, они изменяются на заглавную.*/

#include <stdio.h>
#include <ctype.h>

int main()
{

    char strfname[100] = {0};

    fgets(strfname, 100, stdin);

    int i = 0;
    int firstfl = 0, lastfl = 0;

    while (strfname[i])
    {
        while (!firstfl)
        {
            if (isalpha(strfname[i])) //Нашли первую букву имени
            {
                firstfl = 1;
                if (islower(strfname[i])) // если текущий символ строчный
                {
                    strfname[i] = toupper(strfname[i]); //сделаем заглавным
                }
            }
            i++;
        }

        if (strfname[i] == ' ')
        {
            i++;
            while (!lastfl)
            {
                if (isalpha(strfname[i])) //Нашли первую букву имени
                {
                    lastfl = 1;
                    int res;
                    if (islower(strfname[i]) ) // если текущий символ строчный
                    {
                        strfname[i] = toupper(strfname[i]); //сделаем заглавным
                    }
                }
            }
        }

        i++;
    }

    printf("%s\n",strfname);

    return 0;
}