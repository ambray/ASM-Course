#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" size_t first_func(char*, char, size_t);
extern "C" size_t second_func(char*, char*, size_t);
extern "C" size_t third_func(char*);

#define BUFF_SIZE   (size_t)256

char buf[] = "Has anyone ever been as far as decided to look more like";
int  values[] = { 10, 20, 30, 40, 50 };

#define EQ(x,y)\
do { if(x == y) printf("[*] Success! Values are equal!\n"); \
else printf("[x] Test Failed! Value %zu does not match value %zu!\n", x, y); } while(0)

int main(int argc, char** argv)
{
    { 
        char buf1[BUFF_SIZE] = {0};
        char buf2[BUFF_SIZE] = {0};

        memset(buf1, 0x41, BUFF_SIZE);
        printf("Preparing to run first function (Initialize Memory)\n");
        first_func(buf2, 0x41, BUFF_SIZE);
        EQ((size_t)0, memcmp(buf1, buf2, BUFF_SIZE));
    }
    {
        char fbuf[BUFF_SIZE+1] = {0};
        char sbuf[BUFF_SIZE+1] = {0};
    
        memset(buf, 0x41, BUFF_SIZE);
        printf("Preparing to run second function (Copy memory)\n");
        second_func(sbuf, fbuf, BUFF_SIZE);
        EQ((size_t)0, memcmp(fbuf, sbuf, BUFF_SIZE));
    }
    {
        char strbuf[] = "abcdef1234";
        printf("Preparing to run third function (String length)\n");
        EQ((size_t)strlen(strbuf), third_func(strbuf));
    }
    
    return 0;
}
