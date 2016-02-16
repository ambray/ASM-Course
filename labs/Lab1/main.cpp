#include <stdio.h>
#include <stdlib.h>

extern "C" int first_func(void);

#define EQ(x,y)\
do { if(x == y) printf("[*] Success! Values are equal!\n"); \
else printf("[x] Test Failed! Value %d does not match expected value %d!\n", x, y); } while(0)

int main(int argc, char** argv)
{
    printf("Preparing to run the first test (moving a value to a register)\n");
    EQ(first_func(), 16);

	return 0;
}
