#define O_RDONLY           0
#define O_WRONLY           1
#define O_RDWR             2
#define S_IRWXU            700    // user (file owner) has read, write and execute permission
#define O_CREAT    	   100    // Create the file
#define O_TRUNC           1000    // Truncate (if exists)
#define O_APPEND          2000    // Append

struct dirent {
    unsigned long   d_ino;
    unsigned long   d_off;
    unsigned short  d_reclen;
    char            d_name[];
};


extern void prints (void);
extern void lexit(void);
extern void* lmalloc(unsigned int n);
extern void free(void*);
extern long int write(int fd, const void *buf, long int count); 
extern int open(const char *pathname, int flags, int mode);
extern int getdents(unsigned int fd, struct dirent*, unsigned int count);
extern int execve(const char *filename, char *const argv[],  char *const envp[]);
extern int close(int fd); 
extern int strlen(char* buf);

char* newPointer = 0;

int main()
{
   int retValue = 0;
   int fd = 0;
   char buffer[1024] = {0};

// call open
   char * inputFile = {"/proc/self/cmdline"};
	asm("int3");
   fd = open(inputFile, O_RDONLY, S_IRWXU);

// call read
    retValue = read(fd, buffer, 200);    
    close(fd);

// call write
    char * outputFile = {"outputFile.txt"};
    fd = open(outputFile, O_RDWR, S_IRWXU);             
    write(fd, buffer, retValue);

// call close 
    close(fd);


   return 0;
}

