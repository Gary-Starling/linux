#include <stdio.h>

int* f(void)
{
    return (int *)12;
}

void print(int *v)
{
    printf("value=%d\n",*v);
}

int main()
{
    print(f());
}