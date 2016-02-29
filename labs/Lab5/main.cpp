#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" size_t first_func(void);
extern "C" size_t second_func(void);
extern "C" size_t third_func(void);
extern "C" size_t fourth_func(void);
extern "C" size_t fifth_func(void);
extern "C" size_t sixth_func(void);
extern "C" size_t seventh_func(void);

extern "C" unsigned char value[] = {0x9f, 0xb9, 0xaf, 0xaf, 0xa9, 0xbf, 0xbf, 0xed};
extern "C" char* value_outbuf = NULL;

#define EQ(x,y)\
do { if(x == y) printf("[*] Success! Values are equal!\n"); \
else printf("[x] Test Failed! Value %zu does not match value %zu!\n", x, y); } while(0)

int main(int argc, char** argv)
{

    if(NULL == (value_outbuf = (char*)malloc(sizeof(value) + 1))) {
        printf("Out of memory, please try running again! :(\n");
        return -1;
    }

    memset(value_outbuf, 0, sizeof(value) + 1);

    printf("Preparing to run first function (using and)\n");
    EQ((size_t)0x10, first_func());

    printf("Preparing to run second function (using or)\n");
    EQ((size_t)0, second_func());

    printf("Preparing to run third function (shifting left)\n");
    EQ((size_t)0, third_func());

    printf("Preparing to run fourth function (XOR)\n");
    EQ((size_t)0, fourth_func());

    printf("Preparing to run fifth function (bitshifting)\n");
    EQ((size_t)0, fifth_func());

    printf("Preparing to run sixth function (rotating bytes)\n");
    EQ((size_t)0, sixth_func());

    printf("Preparing to run seventh function (decode value)\n");
    EQ((size_t)0, seventh_func());

    printf("Output: %s\n", value_outbuf);

    free(value_outbuf);

    return 0;
}
