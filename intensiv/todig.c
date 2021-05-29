#include <stdio.h>
#include <ctype.h>

int main()
{

    char str[200];

    fgets(str, 200, stdin);

    int i = 0;

    while (str[i])
    {
        if (isdigit(str[i]))
            printf("%c ", str[i]);
        i++;
    }

    //printf("%s\n", str);
    return 0;
}