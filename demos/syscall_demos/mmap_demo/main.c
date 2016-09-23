#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#define NUM_PAGES   ((size_t)4)
#define BAD_MAP     ((void*)-1)

const char filepath[] = "example.txt";

void* map_anon(size_t count);
void* map_named(const char* fname);
void copy_env(char** envp, char* buf, size_t size);

int main(int argc, char** argv, char** envp)
{
    char* mapped_file = NULL;
    char* mapped_buffer = NULL;

    size_t bufsz = getpagesize() * NUM_PAGES;

    if(BAD_MAP == (mapped_file = (char*)map_named(filepath))) {
        fprintf(stderr, "%d:%d\n", errno, __LINE__);
        return -2;
    }

    if(BAD_MAP == (mapped_buffer = (char*)map_anon(bufsz))) {
        return -3;
    }

    copy_env(envp, mapped_buffer, bufsz);

    printf("File contents: %s\n", mapped_file);
    printf("Buffer contents: %s\n", mapped_buffer);
    return 0;
}


void* map_anon(size_t count)
{
    void* tmp = NULL;

    if(BAD_MAP == (tmp = mmap(NULL, count, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, 0, 0))) {
        fprintf(stderr, "Map failed! %d on %d!\n", errno, __LINE__);
    }

    return tmp;
}

void* map_named(const char* fname)
{
    struct stat finfo = {0};
    void* tmp = NULL;
    int   fd = -1;

    if(NULL == fname) {
        fprintf(stderr, "[x] Invalid input provided on %d!\n", __LINE__);
        return tmp;
    }

    if(-1 == (fd = open(fname, O_RDONLY))) {
        fprintf(stderr, "Open failed with %d on line %d!\n", errno, __LINE__);
        return tmp;
    }

    if(-1 == fstat(fd, &finfo)) {
        fprintf(stderr, "Stat failed with %d on %d\n", errno, __LINE__);
        close(fd);
        return tmp;
    }
    /* map the file into memory */ 
    if(BAD_MAP == (tmp = mmap(NULL, finfo.st_size, PROT_READ, MAP_SHARED, fd, 0))) {
        fprintf(stderr, "Mmap failed with %d on line %d!\n", errno, __LINE__);
        close(fd);
        return tmp;
    }

    close(fd);
    return tmp;
}

void copy_env(char** envp, char* buf, size_t size)
{
    size_t count = 0;

    memset(buf, 0x00, size);

    for(size_t i = 0; envp[i] != NULL && count < size; ++i) {
        count += snprintf(&buf[count], (size - count), "%s\n", envp[i]);
    }
}
