#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" size_t first_func(void);
extern "C" size_t second_func(void);
extern "C" size_t value = 30;

#define EQ(x,y)\
do { if(x == y) printf("[*] Success! Values are equal!\n"); \
else printf("[x] Test Failed! Value %zu does not match value %zu!\n", x, y); } while(0)

int main(int argc, char** argv)
{

    printf("Preparing to run first function (stack allocation)\n");
    EQ((size_t)0x10, first_func());

    printf("Preparing to run second function (register preservation)\n");
    EQ((size_t)1, second_func());
    EQ((size_t)3, value);
    return 0;
}