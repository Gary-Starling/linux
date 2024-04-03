#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int result;

    result = execl("/bin/nano", "", NULL);

    if(result == -1)
     perror("execl");
    
    return 0;
}
