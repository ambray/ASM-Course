#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct dirent {
    unsigned long   d_ino;
    unsigned long   d_off;
    unsigned short  d_reclen;
    char            d_name[];
};

extern int dent_me(int fd, struct dirent*, unsigned int size);
extern size_t file_size(char*);
extern int add_nums(int*, int);
extern int add_2(int, int);
extern int is_set(int);

int stuff = 0;
int main(int argc, char** argv, char** envp)
{
    char buf[1024] = {0};
    int num_read = 0;
    int current = 0;
    struct dirent* tmp = (struct dirent*)buf;
    int fd = open("/proc/self", O_RDONLY);
    num_read = dent_me(fd, tmp, sizeof(buf));
     
    while(current < num_read) {
        fprintf(stdout, "%s\n", tmp->d_name);
        current += tmp->d_reclen; 
        tmp = (struct dirent*)(buf + current);     
    } 
    
    close(fd);
    unsigned long s = file_size("/proc/self/environ");
    printf("File Size: %lu\n", s);
    int a = 10;
    add_nums(&a, 20);
    printf("%d\n", a);
    printf("%d\n", add_2(10, 20));
    char* out = (is_set(&stuff)) ? "Is set!\n" : "Isn't set!\n";
    printf(out);
    out = (is_set(&stuff)) ? "Is set!\n" : "Isn't set!\n";
    printf(out);
    return 0;
}

