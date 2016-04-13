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
        char* c1 = (char*)y((char*)sl[i], __VA_ARGS__);\
        char* c2 = (char*)x((char*)sl[i], __VA_ARGS__);\
        c1 == c2 ?\
                 printf("[*] %s %d - PASS - Values are equal!\n", \
                        __FUNCTION__, __LINE__) :\
                 printf("[x] %s %d - FAIL - Values are not equal! %s | %s\n", \
                        __FUNCTION__, __LINE__, c1, c2);\
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


// BONUS LABS
extern "C" char* ex_strstr(char*, char*);
extern "C" void ex_isort(int*, size_t);
extern "C" void ex_qsort(int*, size_t);

void mem_tests()
{
    char* first = NULL;
    char* second = NULL;
    char buf1[BUFSZ] = {0};
    int canary = 0xc0ffee;
    char buf2[BUFSZ] = {0};

    for(int i = 0; stringlist[i] != NULL; ++i) {
        ex_memcpy(buf2, stringlist[i], (strlen(stringlist[i]) - 1));
        memcpy(buf1, stringlist[i], strlen(stringlist[i]) - 1);
        if(canary != 0xc0ffee) {
            printf("[x] Out of bounds copy in %s | %d\n", __FUNCTION__, __LINE__);
            break;
        }
        EQ((size_t)0, strcmp(buf1, buf2));
        memset(buf1, 0, BUFSZ);
        memset(buf2, 0, BUFSZ);
    }

    memset(buf1, 0x41, BUFSZ);
    ex_memset(buf2, 0x41, BUFSZ);
    if(canary != 0xc0ffee) {
        printf("[x] Out of bounds copy in %s | %d\n", __FUNCTION__, __LINE__);
        return;
    }

    EQ((size_t)0, memcmp(buf1, buf2, BUFSZ));
    memset(buf1, 0xcc, BUFSZ);
    memset(buf2, 0xcc, BUFSZ);
    EQ((size_t)0, ex_memcmp(buf1, buf2, BUFSZ));

    for(int i = 0; stringlist[i] != NULL; ++i) {
        first = (char*)memchr((void*)stringlist[i], 'i', strlen(stringlist[i]) - 1);
        second = (char*)ex_memchr((void*)stringlist[i], 'i', strlen(stringlist[i]) - 1);
        EQ((size_t)first, (size_t)second);
    }
}

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
    mem_tests();
    return 0;
}
