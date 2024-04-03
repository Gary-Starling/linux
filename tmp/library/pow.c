#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{
    if(argc < 3)
    {
        fprintf(stderr, "to few arguments\n");
        return 1;
    }

    printf("%f\n", pow(atof(argv[1]), atof(argv[2])));

}


