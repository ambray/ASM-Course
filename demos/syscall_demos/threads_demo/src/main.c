#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>

extern pid_t create_thread(void*, void* stack, size_t size);

#define NUM_THREADS 5
#define STACK_SIZE  ((size_t)4096)
#define LOGFILE     "tmp.txt"

void print_stuff(void)
{
    for(int i=0; i < 20; ++i) {
        printf("Current Iteration: %d\n", i);
        sleep(1); 
    }
}

int main(int argc, char** argv, char** envp)
{
    char buf[2048] = {0};
    FILE* fh = NULL;
    FILE* outf = NULL;
    void* segs[NUM_THREADS] = {0};
    
    for(int i = 0; i < NUM_THREADS; ++i) {
        if(NULL == (segs[i] = mmap(NULL, STACK_SIZE, 
                               PROT_READ | PROT_WRITE, 
                               MAP_PRIVATE | MAP_ANON | MAP_GROWSDOWN, 
                               0, 0)))
         {
            printf("[x] Failed to allocate stack memory!");
            return -1;
         }
    }

    for(int i = 0; i < NUM_THREADS; ++i)
      create_thread((void*)print_stuff, segs[i], STACK_SIZE);

    if(NULL == (fh = fopen("/proc/self/status", "r"))) {
        printf("Failed to open proc!\n");
        goto Skip;
    }

    fread(buf, 2047, 2047, fh);
    if(NULL != (outf = fopen(LOGFILE, "w"))) {
        fprintf(outf, "Process Information:\n%s", buf);
        fclose(outf);
    } 
    fclose(fh); 
Skip:
    getchar();

    // Cleanup
    for(int i = 0; i < NUM_THREADS; ++i)
        munmap(segs[i], STACK_SIZE);

    return 0;
}
