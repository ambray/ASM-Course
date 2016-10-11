#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>

#define BUFSZ 129

struct Node;

struct Node {
    Node* next;
    size_t data;
};

char* needles[] = {
	"String",
	"works",
	"the",
	"\n",
	NULL,
};

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

#define IS_LARGEST(c1, ar, sz)\
    do {\
        int lg=ar[0];\
        for(int i=1; i<sz; ++i)\
            lg = (ar[i] > lg) ? ar[i] : lg;\
        EQ(lg, c1);\
    } while(0)

#define EQ_STRING(s1, s2)\
	do {\
	(s1 == s2 && (NULL == s1 || (0 == strcmp(s1, s2)))) ?\
		printf("[*] %s | %d - PASS - Values are equal!\n", __FUNCTION__, __LINE__) :\
		printf("[x] %s | %d - FAIL - Values are not equal!\n", __FUNCTION__, __LINE__);\
	} while(0)

#define GET_SEED(s)\
    do {\
        unsigned int a,d;\
        asm("rdtsc" : "=a"(a), "=d"(d));\
        s = (a | (d << 32));\
    } while(0)

extern "C" size_t ex_strlen(char*);
extern "C" void ex_memcpy(void*, void*, size_t);
extern "C" void ex_memset(void*, unsigned char, size_t);
extern "C" void* ex_memchr(void*, unsigned char, size_t);
extern "C" char* ex_strchr(char*, char);
extern "C" int ex_strcmp(char*, char*);
extern "C" int ex_memcmp(void*, void*, size_t);
extern "C" void ex_strcpy(char*, char*);
extern "C" int ex_atoi(char*);
extern "C" char* ex_strstr(char*, char*);

extern "C" int find_largest(int*, int);
extern "C" int walk_list(Node*, size_t);

// BONUS LABS
extern "C" void ex_isort(int*, size_t);
extern "C" void ex_qsort(int*, size_t);


void find_largest_test()
{
    int count = 5;

    int* tmp = NULL;
    int nums[] = {20, 1, 4, 17, 42, 18, 49, 12};
    int res = find_largest(nums, sizeof(nums) / sizeof(int));
    IS_LARGEST(res, nums, sizeof(nums)/sizeof(int));
    for(int i =0; i < 5; ++i) {
        if(NULL == (tmp = (int*)malloc(sizeof(int) * count))) {
            printf("[x] Low memory!\n");
            continue;
        }
        memset(tmp, 0x00, sizeof(int) * count);
        for(int j = 0; j < count; ++j)
            tmp[j] = rand();
        res = find_largest(tmp, count);
        IS_LARGEST(res, tmp, count);
        free(tmp);
    }
}

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

void strstr_test()
{
   for(int i=0; stringlist[i] != NULL; ++i){
	for(int j=0; needles[j] != NULL; ++j){
	    char* tmp1 = strstr(stringlist[i], needles[j]);
	    char* tmp2 = ex_strstr(stringlist[i], needles[j]);
	    EQ_STRING(tmp1, tmp2);
	}
   }
}

void string_tests()
{
    char buf1[BUFSZ] = {0};
    int canary = 0xc0ffee;
    char buf2[BUFSZ] = {0};
    printf("Beginning string tests:\n\n");
    printf("Calling ex_strlen:\n");
    FOR_EACH_STRING(stringlist, strlen, ex_strlen);
    printf("Calling ex_strchr:\n");
    FOR_EACH_STRING2(stringlist, strchr, ex_strchr, 'i');
    FOR_EACH_STRING2(stringlist, strchr, ex_strchr, 'U');
    printf("Calling ex_strcmp:\n");
    for(int i = 0; stringlist[i] != NULL; ++i) {
        EQ((size_t)0, ex_strcmp(stringlist[i], stringlist[i]));
    }
    printf("Calling ex_strcpy:\n");
    for(int i = 0; stringlist[i] != NULL; ++i) {
        ex_strcpy(buf2, stringlist[i]);
        strcpy(buf1, stringlist[i]);
        if(canary != 0xc0ffee) {
            printf("[x] Out of bounds copy in %s | %d", __FUNCTION__, __LINE__);
            break;
        }
        EQ((size_t)0, strcmp(buf1, buf2));
    }
    printf("Calling ex_atoi:\n");
    FOR_EACH_STRING(numlist, atoi, ex_atoi);
    strstr_test();
}

void allocate_list(Node** start, size_t* needle, size_t list_len)
{
    Node* tmp = NULL;
    Node* current = NULL;
    Node* prev = NULL;
    size_t track = 0;

    if(NULL == (tmp = (Node*)malloc(sizeof(Node)))) {
        printf("[x] Failed to allocate Node!\n");
        return;
    }
    memset(tmp, 0, sizeof(Node));
    track = rand();
    current = tmp;
    for(int i = 0; i < list_len; ++i) {
        prev = current;
        if(NULL == (current = (Node*)malloc(sizeof(Node)))) {
            printf("[x] Allocation failed! %d\n", __LINE__);
            continue;
        }
        memset(current, 0, sizeof(Node));
        current->data = rand();
        prev->next = current;
        track = (track > current->data) ? track : current->data;
    }

    *start = tmp;
    *needle = track;
}

void deallocate_list(Node* list)
{
    Node* current = NULL;
    Node* next = NULL;
    while(NULL != current && NULL != (next = current->next)) {
        free(current);
        current = next;
    }

}

void print_data(Node* n)
{
    while(n != NULL) {
        printf("Current: %d\n", n->data);
        n = n->next;
    }
}

void test_walk_list()
{
    Node* list = NULL;
    size_t needle = 0;
    size_t result = 0;
    allocate_list(&list, &needle, 20);
    //print_data(list);
    result = walk_list(list, needle);
    EQ(needle, result);
    deallocate_list(list);
}

int intcmp(const void* first, const void* second)
{
    if(*((int*)first) == *((int*)second))
        return 0;

    return (*((int*)first) > *((int*)second)) ? 1 : -1;

}

#define SORT_COUNT  5
void sort_tests(void(*tf)(int*, size_t))
{
    int buf[SORT_COUNT] = {0};

    int sorted[SORT_COUNT] = {0};

    for(int i = 0; i < SORT_COUNT; ++i)
        buf[i] = rand();

    memcpy(sorted, buf, sizeof(buf));
    tf(buf, SORT_COUNT);
    qsort(sorted, SORT_COUNT, sizeof(int), intcmp);
    

    EQ(0, memcmp(sorted, buf, sizeof(buf)));
}

int main(int argc, char** argv)
{
    unsigned int seed = 0;
    GET_SEED(seed);
    srand(seed);
    off_t
   // find_largest_test();
   // string_tests();
   // mem_tests();
    //test_walk_list();
    //printf("Preparing to run Quicksort tests (BONUS)\n");
    //sort_tests(ex_qsort);
    //printf("Preparing to run Insertion Sort tests (BONUS)\n");
    //sort_tests(ex_isort);
    return 0;
}
