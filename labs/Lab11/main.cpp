#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define FIRST_EXPECTED (float)3.5795002
#define SECOND_EXPECTED (float)11.23450005

extern "C" float out1;
extern "C" double out2;
extern "C" size_t first_func(void);
extern "C" size_t second_func(int);

#define EQ(x,y)\
do { if(x == y) printf("[*] Success! Values are equal!\n"); \
else printf("[x] Test Failed! Value %.8g does not match value %.8g!\n", x, y); } while(0)

int main(int argc, char** argv)
{
    printf("Preparing to run first_func (Add floating point numbers)\n");
    first_func();
    printf("Result: %.8g\n", out1);
    EQ(FIRST_EXPECTED, out1);

    printf("Preparing to run second_func (Add floats and integers)\n");
    second_func(10);
    printf("Result: %.16g\n", out2);
    EQ(SECOND_EXPECTED, (float)out2);
    return 0;
}
