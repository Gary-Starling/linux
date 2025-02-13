#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void signFunc(int sign)
{
    if (sign != SIGINT)
    {
        printf("\nSignnal recived -> %d\n", sign);
        return;
    }
    else
    {
        printf("SIGINT recived\n"
               "Entet 'y' to exit program\n");
        while (getchar() != 'y')
            return;

        exit(EXIT_SUCCESS);
    }
}

int main(int argc, char const *argv[])
{

    if (SIG_ERR == signal(SIGINT, signFunc))
        exit(EXIT_FAILURE);

    if (SIG_ERR == signal(SIGTSTP, signFunc))
        exit(EXIT_FAILURE);

    printf("Enter CTRL+C to exit program\n");
    while (1)
        ;

    return 0;
}
