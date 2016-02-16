#include <stdio.h>
#include <stdlib.h>

extern "C" size_t first_func(void);

extern "C" size_t value = -20;

#define EQ(x,y)\
do { if(x == y) printf("[*] Success! Values are equal!\n"); \
else printf("[x] Test Failed! Value %zu does not match value %zu!\n", x, y); } while(0)

int main(int argc, char** argv)
{
    printf("Preparing to run first function (copying a byte)\n");
    EQ((size_t)4, first_func());
    return 0;
}