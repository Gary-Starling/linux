#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    FILE * infile;
    int ch;
    long int nback;

    if(argc <  3)
    {
        fprintf(stderr, "To few arg(s)\n");
        return 1;
    }

    if((infile = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "Cannot open input file (%s)\n", argv[1]);
        return 1;
    }
    else
    {
        nback = abs(atoi(argv[2]));
        fseek(infile, 0, SEEK_END);     //в конец файла

        if(nback > ftell(infile))       //если количество символов для чтения больше чем в самом файле
            fseek(infile, 0, SEEK_SET); //установим в начало
        else
            fseek(infile, -nback, SEEK_END); //установка в конец, минус количество символов
        
        while((ch = fgetc(infile))!=EOF)
            fputc(ch, stdout);

        fputc('\n', stdout);
    }

    fclose(infile);

    return 0;
}
