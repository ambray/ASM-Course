#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BUFSZ 129

char* stringlist[] = {
        "The First String.\n",
        "My Second String\0and stuff.",
        "the third one... hopefully this works!",
        "the more stings,\n\t the better!",
        "Hopefully not NULL! We'll see, though.",
        NULL,
};

char* numlist[] = {
        "1",
        "10",
        "12345",
        "9999999",
        "8675309",
        NULL,
};

#define EQ(x, y)\
    do { x == y ? printf("[*] %s %d - PASS - Values are equal!\n", \
                        __FUNCTION__, __LINE__) :\
                 printf("[x] %s %d - FAIL - Values are not equal!\n", \
                        __FUNCTION__, __LINE__);\
    } while(0)

#define FOR_EACH_STRING(sl, x, y)\
    do {\
    for(int i=0; sl[i] != NULL; ++i) {\
        y(sl[i]) == x(sl[i]) ?\
                 printf("[*] %s %d - PASS - Values are equal!\n", \
                        __FUNCTION__, __LINE__) :\
                 printf("[x] %s %d - FAIL - Values are not equal!\n", \
                        __FUNCTION__, __LINE__);\
    }\
 } while (0)

#define FOR_EACH_STRING2(sl, x, y, ...)\
    do {\
    for(int i=0; sl[i] != NULL; ++i) {\
        y(sl[i], __VA_ARGS__) == x(sl[i], __VA_ARGS__) ?\
                 printf("[*] %s %d - PASS - Values are equal!\n", \
                        __FUNCTION__, __LINE__) :\
                 printf("[x] %s %d - FAIL - Values are not equal!\n", \
                        __FUNCTION__, __LINE__);\
    }\
 } while (0)

extern "C" size_t ex_strlen(char*);
extern "C" void ex_memcpy(void*, void*, size_t);
extern "C" void ex_memset(void*, unsigned char, size_t);
extern "C" void* ex_memchr(void*, unsigned char, size_t);
extern "C" char* ex_strchr(char*, char);
extern "C" int ex_strcmp(char*, char*);
extern "C" int ex_memcmp(void*, void*, size_t);
extern "C" void ex_strcpy(char*, char*);
extern "C" int ex_atoi(char*);
extern "C" void ex_sort(int*, size_t);

// BONUS LABS
extern "C" char* ex_strstr(char*, char*);
extern "C" void ex_qsort(int*, size_t);

void string_tests()
{
    char buf1[BUFSZ] = {0};
    int canary = 0xc0ffee;
    char buf2[BUFSZ] = {0};
    printf("Beginning string tests:\n\n");
    FOR_EACH_STRING(stringlist, strlen, ex_strlen);
    FOR_EACH_STRING2(stringlist, strchr, ex_strchr, 'i');
    FOR_EACH_STRING2(stringlist, strchr, ex_strchr, 'U');

    for(int i = 0; stringlist[i] != NULL; ++i) {
        EQ((size_t)0, ex_strcmp(stringlist[i], stringlist[i]));
    }

    for(int i = 0; stringlist[i] != NULL; ++i) {
        ex_strcpy(buf2, stringlist[i]);
        strcpy(buf1, stringlist[i]);
        if(canary != 0xc0ffee) {
            printf("[x] Out of bounds copy in %s | %d", __FUNCTION__, __LINE__);
            break;
        }
        EQ((size_t)0, strcmp(buf1, buf2));
    }

    FOR_EACH_STRING(numlist, atoi, ex_atoi);
}


int main(int argc, char** argv)
{
    string_tests();
    return 0;
}
