#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" size_t get_flags(void);
extern "C" size_t first_func(void);
extern "C" size_t second_func(void);
extern "C" size_t third_func(void);


#define CF_SET(x)  x & (1 << 0)
#define OF_SET(x)  x & (1 << 11)

#define T(x)\
do { if(x) printf("[*] Success!\n"); \
else printf("[x] Test Failed! Value did not evaluate to true\n"); } while(0)

int main(int argc, char** argv)
{
    size_t flags = 0;
    printf("Preparing to run first function (Carrying)\n");
    first_func();
    flags = get_flags();
    T(CF_SET(flags));

    printf("Preparing to run second function (Overflow)\n");
    second_func();
    flags = get_flags();
    T(OF_SET(flags));

    printf("Preparing to run third function (Setting both OF and CF)\n");
    third_func();
    flags = get_flags();
    T(OF_SET(flags) && CF_SET(flags));

    return 0;
}
