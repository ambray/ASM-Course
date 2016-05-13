#include <stdio.h>
#include <string.h>

extern int run_me(char*);


int main(int argc, char** argv, char** envp)
{
    int tmp = run_me(envp[0]);

    printf("Length is: %d, vs %d\n", tmp, strlen(envp[0]));
    return 0;
}
