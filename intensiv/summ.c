#include <stdio.h>

int main(){
    
    int mass[15] = {0};
    int max = 0;
    
    int i = 0;
    
    for (i = 0; i < 15; i++)
    {
        scanf("%d", &mass[i]);
    }
    
    max = mass[0];

    for (i = 0; i < 15; i++)
    {
      if(mass[i] >= max)
        max = mass[i];
    }

    printf("%d\n", max);
    
    return 0;
}