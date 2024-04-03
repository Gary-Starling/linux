//compile gcc -static trace.c -o trace

#include <stdio.h>


#define SIZE    (32)
int data[SIZE];

int main(int argc, char const *argv[])
{
    for (unsigned int i = 0; i < SIZE; i++)
        printf("data[%d] = %d\n", i, data[i]);
        
    printf("ptrace data addr %p\n", &data[0]);
    return 0;
}
