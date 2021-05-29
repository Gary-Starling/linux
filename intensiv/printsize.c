
/*char, char*, char**
int, int*, int**
float, float*, float**
double, double*, double***/

#include <stdio.h>

int main()
{
    printf("%lu, %lu, %lu\n%lu, %lu, %lu\n%lu, %lu, %lu\n%lu, %lu, %lu\n", sizeof(char),sizeof(char*),
sizeof(char**),sizeof(int),sizeof(int*),sizeof(int**),sizeof(float),sizeof(float*),sizeof(float**),sizeof(double),sizeof(double*),sizeof(double**));
    return 0;
}