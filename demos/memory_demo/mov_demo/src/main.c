#include <stdio.h>

extern int movin(int* a, int* b);

int main(int argc, char** argv, char** envp)
{
    int t1 = 10;
    int t2 = 20;
    printf("Before: %d, %d\n", t1, t2);
    int val = movin(&t1, &t2);
    printf("Result: %d, %d\n", t1, t2);

    return 0;
}
