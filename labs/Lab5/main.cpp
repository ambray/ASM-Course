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
extern "C" char second_value[] = {'e', 's', 's', '!', 'S', 'u', 'c', 'c'};
#define VALUE_ALLOC_SIZE   24
extern "C" char* value_outbuf = NULL;
extern "C" char* second_outbuf = NULL;


#define EQ(x,y)\
do { if(x == y) printf("[*] Success! Values are equal!\n"); \
else printf("[x] Test Failed! Value %zu does not match value %zu!\n", x, y); } while(0)

int main(int argc, char** argv)
{

    if(NULL == (value_outbuf = (char*)malloc(VALUE_ALLOC_SIZE))) {
        printf("Out of memory, please try running again! :(\n");
        return -1;
    }

    if(NULL == (second_outbuf = (char*)malloc(VALUE_ALLOC_SIZE))) {
        printf("Out of memory, please try running again! :(\n");
        return -2;
    }
    memset(value_outbuf, 0, VALUE_ALLOC_SIZE);
    memset(second_outbuf, 0, VALUE_ALLOC_SIZE);

    printf("Preparing to run first function (using and)\n");
    EQ((size_t)1, first_func());

    printf("Preparing to run second function (using or)\n");
    EQ((size_t)3740139503, second_func());

    printf("Preparing to run third function (Zeroing RAX)\n");
    EQ((size_t)0, third_func());

    printf("Preparing to run fourth function (Bitshift Multiplication)\n");
    EQ((size_t)64, fourth_func());

    printf("Preparing to run fifth function (Bitshift Division)\n");
    EQ((size_t)2, fifth_func());

    printf("Preparing to run sixth function (rotating bytes)\n");
    sixth_func();
    printf("Rotated output: %s\n", second_outbuf);

    printf("Preparing to run seventh function (decode value)\n");
    seventh_func();
    printf("Decoded Output: %s\n", value_outbuf);

    free(second_outbuf);
    free(value_outbuf);

    return 0;
}
