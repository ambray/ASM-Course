#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int run_me(int, char*, int);

void my_function(void)
{

	printf("Made it here!\n");
}

int main(int argc, char** argv, char** envp)
{
    int tmp = run_me(10, envp[0], 20);

    printf("tmp: %d\n", tmp);
    return 0;
}
