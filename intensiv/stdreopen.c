#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    fclose(stdout);
    stdout = fopen("somefile", "w");
    if (stdout == NULL)
        abort();

    printf("Hey Hey Hey!\n");
    
    return 0;
}
