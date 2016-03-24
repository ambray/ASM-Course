#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" size_t first_func(void);
extern "C" char* second_func(void*, char*);
extern "C" size_t third_func(size_t);

char str[] = "Super awesome test string.\0";

char* copystring(char* src, int len)
{
    char* tmp = NULL;

    if(NULL == src || 0 == len)
        return NULL;
    
    if(NULL == (tmp = (char*)malloc(len + 1))) {
        printf("[x] Allocation failed!\n");
        return tmp;
    } 

    memset(tmp, 0x00, len+1);
    memcpy(tmp, src, len);

    return tmp;
}

#define EQ(x,y)\
do { if(x == y) printf("[*] Success! Values are equal!\n"); \
else printf("[x] Test Failed! Value %zu does not match value %zu!\n", x, y); } while(0)

int main(int argc, char** argv)
{
    char* tmp = NULL;

    printf("Calling first function (printf)\n");
    first_func();

    printf("Calling the second function (function pointer)\n");
    if(NULL == (tmp = second_func((void*)copystring, str))) {
        printf("[x] Failed to copy string!\n");
        return -1;
    }
    EQ((size_t)0, strcmp(tmp, str));    

    printf("Calling the third function (fibonacci)\n");
    EQ((size_t)55, third_func(10));

    return 0;
}
