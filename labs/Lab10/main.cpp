#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

extern "C" size_t first_func(void);
extern "C" size_t second_func(char*);

size_t gettsc()
{
    size_t lowbits, highbits;
    asm("rdtsc" : "=a" (lowbits), "=d" (highbits));
    return (lowbits | (highbits << 32));
}

void getvstr(char** buf)
{
    uint32_t p1,p2,p3;
    char* tmp = NULL;
    if(NULL == buf)
        return;

    if(NULL == (tmp = (char*)malloc(13))) {
        printf("[x] Out of memory!\n");
        return;
    }
    memset(tmp, 0x00, 13);
    asm("xor %rax,%rax");
    asm("cpuid" : "=b" (p1),
                  "=d" (p2),
                  "=c" (p3));
    memcpy(tmp, &p1, sizeof(p1));
    memcpy((tmp+4), &p2, sizeof(p2));
    memcpy((tmp+8), &p3, sizeof(p3)); 
    *buf = tmp;
}

#define EQ(x,y)\
do { if(x == y) printf("[*] Success! Values are equal!\n"); \
else printf("[x] Test Failed! Value %zu does not match value %zu!\n", x, y); } while(0)

#define CLOSE(x,y)\
do { if((x - y) <= 1000) printf("[*] Success! values %zu and %zu are close!\n", x, y); \
else printf("[x] Test failed! Values %zu and %zu are not close!\n", x, y); \
} while(0)
int main(int argc, char** argv)
{
    size_t first = 0;
    size_t second = 0;
    char* tmp = NULL;
    char idbuf[13] = {0};

    printf("Preparing to run first_func (Get timestamp)\n");
    first = gettsc();
    second = first_func();
    CLOSE(second, first);    
    
    getvstr(&tmp);
    if(NULL == tmp) {
        printf("[x] Allocation failed!\n");
        return -1;
    }
    printf("Preparing to run second_func (Get vendor string)\n");
    second_func(idbuf);
    EQ((size_t)0, (size_t)strcmp(idbuf, tmp));
    printf("Your vendor ID string is: %s\n", idbuf);
    free(tmp);

    return 0;
}
