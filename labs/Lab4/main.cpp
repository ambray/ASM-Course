#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" size_t first_func(void);
extern "C" char buf[33] = {0};

#define EQ(x,y)\
do { if(x == y) printf("[*] Success! Values are equal!\n"); \
else printf("[x] Test Failed! Value %zu does not match value %zu!\n", x, y); } while(0)

int main(int argc, char** argv)
{
    char buf2[33] = {0};
    memset(buf2, 0x41, 32);

    printf("Preparing to run first function (stack allocation)\n");
    first_func();
    EQ(0, strcmp(buf, buf2));
    return 0;
}