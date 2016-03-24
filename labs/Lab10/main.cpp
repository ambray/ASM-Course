#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" size_t first_func(char*, char, size_t);
extern "C" size_t second_func(char*, char*, size_t);
extern "C" size_t third_func(char*);

#define EQ(x,y)\
do { if(x == y) printf("[*] Success! Values are equal!\n"); \
else printf("[x] Test Failed! Value %zu does not match value %zu!\n", x, y); } while(0)

int main(int argc, char** argv)
{
    return 0;
}
