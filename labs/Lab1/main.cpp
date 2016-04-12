#include <stdio.h>
#include <stdlib.h>

extern "C" size_t first_func(void);
extern "C" size_t second_func(void);
extern "C" void third_func(void);
extern "C" size_t fourth_func(void);
extern "C" size_t fifth_func(void);
extern "C" void sixth_func(void);

#define EQ(x,y)\
do { if(x == y) printf("[*] Success! Values are equal!\n"); \
else printf("[x] Test Failed! Value %zu does not match value %zu!\n", x, y); } while(0)

extern "C" size_t value = 0;
extern "C" size_t buf[] = {10,20,30,40};

extern "C" size_t val1 = 10;
extern "C" size_t val2 = 40;

int main(int argc, char** argv)
{
    printf("Preparing to run the first test (moving a value to a register)\n");
    EQ(first_func(), (size_t)16);

    printf("Preparing to run the second test (moving the contents of one register into another)\n");
    EQ(second_func(), (size_t)32);

    printf("Preparing to run the third test (moving a value from a register to memory)\n");
    third_func();
    EQ(value, (size_t)16);

    value = 255;
    printf("Preparing to run the fourth test (moving a value from memory into a register)\n");
    EQ((size_t)255, fourth_func());

    printf("Preparing to run the fifth test (using lea to calculate the next item in a list)\n");
    EQ(buf[1], fifth_func());

    printf("Preparing to run the sixth test (using xchg to swap two array values)\n");
    sixth_func();
    EQ((size_t)10, val2);
    EQ((size_t)40, val1);
	return 0;
}
