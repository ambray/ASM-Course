#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" size_t first_func(void);
extern "C" size_t second_func(void);
extern "C" size_t value = -20;

#define EQ(x,y)\
do { if(x == y) printf("[*] Success! Values are equal!\n"); \
else printf("[x] Test Failed! Value %zu does not match value %zu!\n", x, y); } while(0)

#define EQ_C(x,y)\
do { if(x == y) printf("[*] Success! Values are equal!\n"); \
else printf("[x] Test Failed! Value %c does not match value %c!\n", x, y); } while(0)


int main(int argc, char** argv)
{
	char vals[] = { 'B', 'A' };
    printf("Preparing to run first function (copying a byte)\n");
    EQ((size_t)4, first_func());
    printf("Preparing to run the second function (swapping low and high)\n");
    size_t res = second_func();
    
    EQ_C(((char*)&res)[0], vals[0]);
    EQ_C(((char*)&res)[1], vals[1]);

    return 0;
}