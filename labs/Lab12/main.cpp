#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

extern "C" size_t first_func(int*, int*, int*);
extern "C" size_t second_func(int*, int*, int*);
extern "C" int third_func(int, int);

#define EQ(x,y)\
do { if(x == y) printf("[*] Success! Values are equal!\n"); \
else printf("[x] Test Failed! Value %d does not match value %d!\n", x, y); } while(0)

void first_test()
{
    int vals[] = {10, 20, 30, 40};
    int vals2[] = {20, 30 , 40, 50};
    int out[4] = {0};
    int exp[] = {30, 50, 70, 90};

    printf("Preparing to run first_func (Add two vectors)\n");
    first_func(vals, vals2, out);
    printf("Result: %d, %d, %d, %d\n", out[0], out[1], out[2], out[3]);
    EQ(0, memcmp(out, exp, sizeof(out)));
}

void second_test()
{
    int v1[] = {10, 30, 40, 70};
    int v2[] = {10, 20, 40, 20};
    int out[4] = {0};

    printf("Preparing to run second_func (Compare vectors)\n");
    second_func(v1, v2, out);
    printf("%d, %d, %d, %d\n", out[0], out[1], out[2], out[3]);
    EQ(out[0], -1);
    EQ(out[1], 0);
    EQ(out[2], -1);
    EQ(out[3], 0);
}

void third_test()
{
    int x = 10;
    int y = 42;
    int res = third_func(x, y);
    printf("%d\n", res);
    EQ(y, res);

    x = 32;
    y = 21;
    res = third_func(x, y);
    EQ(x, res);
}

int main(int argc, char** argv)
{

    first_test();
    second_test();
    third_test();
    return 0;
}
