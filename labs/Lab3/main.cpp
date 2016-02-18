#include <stdio.h>
#include <stdlib.h>

extern "C" size_t first_func(void);
extern "C" size_t second_func(void);
extern "C" size_t third_func(void);
extern "C" size_t fourth_func(void);
extern "C" size_t fifth_func(void);

#define EQ(x,y)\
do { if(x == y) printf("[*] Success! Values are equal!\n"); \
else printf("[x] Test Failed! Value %zu does not match value %zu!\n", x, y); } while(0)


int main(int argc, char** argv)
{
    printf("Preparing to run the first function (adding values)\n");
    EQ((size_t)20, first_func());


    printf("Preparing to run the second function (subtracting values)\n");
    EQ((size_t)10, second_func());

    printf("Preparing to run the third function (multiplying)\n");
    EQ((size_t)100, third_func());

    printf("Preparing to run the fourth function (division)\n");
    EQ((size_t)5, fourth_func());

    printf("Preparing to run the fifth function (remainder)\n");
    EQ((size_t)1, fifth_func());

    return 0;
}
