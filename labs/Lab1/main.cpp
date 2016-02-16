#include <stdio.h>
#include <stdlib.h>

extern "C" int first_func(void);
extern "C" int second_func(void);
extern "C" int third_func(void);
extern "C" int fourth_func(void);

#define EQ(x,y)\
do { if(x == y) printf("[*] Success! Values are equal!\n"); \
else printf("[x] Test Failed! Value %d does not match expected value %d!\n", x, y); } while(0)

extern "C" int value = 0;

int main(int argc, char** argv)
{
    printf("Preparing to run the first test (moving a value to a register)\n");
    EQ(first_func(), 16);

    printf("Preparing to run the second test (moving the contents of one register into another)\n");
    EQ(second_func(), 32);

    printf("Preparing to run the third test (moving a value from a register to memory)\n");
    third_func();
    EQ(value, 16);

    value = 255;
    printf("Preparing to run the fourth test (moving a value from memory into a register)\n");
    EQ(255, fourth_func());


	return 0;
}
