#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" size_t first_func(size_t, size_t);
extern "C" size_t second_func(int*, int);
extern "C" size_t third_func(char*);

#define SECOND_GREATER     (size_t)-1
#define FIRST_GREATER       (size_t)1
#define VALUES_EQUAL        (size_t)0


char buf[] = "Has anyone ever been as far as decided to look more like";
int  values[] = { 10, 20, 30, 40, 50 };

#define EQ(x,y)\
do { if(x == y) printf("[*] Success! Values are equal!\n"); \
else printf("[x] Test Failed! Value %zu does not match value %zu!\n", x, y); } while(0)

int main(int argc, char** argv)
{
    size_t flags = 0;
    printf("Preparing to run first function (Larger Number)\n");
    EQ(VALUES_EQUAL, first_func(2, 2));
    EQ(FIRST_GREATER, first_func(2,1));
    EQ(SECOND_GREATER, first_func(10, 20));

    printf("Preparing to run second function (Sum)\n");
    EQ((size_t)150, second_func(values, 5));

    printf("Preparing to run third function (String length)\n");
    EQ(strlen(buf), third_func(buf));

    return 0;
}
