#include <stdio.h>

int main(){
    
    int mass[15];
    
    int i = 0;
    
    for (i = 0; i < 15; i++)
    {
        scanf("%d", &mass[i]);
    }
    
    
    for (i = 14; i >= 0; i--)
    {
     printf("%d ", mass[i] );
    }
    
    return 0;
}