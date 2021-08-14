#include <stdio.h>

typedef struct 
{
    char name[100];
    unsigned int reward;    //Награда
    unsigned int cnt_crime; //Количество преступлений
}bandit;

 

int main(int argc, char const *argv[])
{
    FILE *in, *out;

    bandit gary = { "Gary Starling", 100, 10};
    bandit muhin = { "Alex Muhin", 1000 , 1};
    bandit sp;

    out = fopen("data.txt","w");
    if(!out) 
    {
        perror("fopen");
        return 1;
    }

    if(!fwrite(&gary, sizeof(bandit), 1, out))
    {
        perror("fwrite");
        return 1;
    }

    if(fclose(out))
    {
        perror("fclose");
        return 1;
    }

    in = fopen("data.txt", "r");
    if(!in)
    {
        perror("fopen");
        return 1;
    }

    if(!fread(&sp,sizeof(bandit), 1, in))
    {
        perror("fread");
        return 1;
    }

    if(fclose(in))
    {
        perror("fclose");
        return 1;
    }

    printf("name = %s\nreward = %d$\ncnt crime = % d\n", sp.name, sp.reward, sp.cnt_crime);





    return 0;
}
