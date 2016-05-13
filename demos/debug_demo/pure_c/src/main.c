#include <stdio.h>
#include <string.h>
#include <errno.h>

/**
* open_file: Opens a file.
* @param fname: the file name to open.
* @param fptr: The output parameter for
* out file pointer.
*/
int open_file(char* fname, FILE** fptr)
{
    FILE* ftmp = NULL;

    if(NULL == fname || NULL == fptr)
        return -1;

    if(NULL == (ftmp = fopen(fname, "w"))) {
        fprintf(stdout, "File open failed! %s\n", strerror(errno));
        return errno;
    }
        
    *fptr = ftmp;
    return 0;
}

/**
* print_env: Prints a list of strings to a file handle.
* @param fh: The file handle to write output into.
* @param envp: A pointer to a NULL-terminated list of pointers.
* @returns int: A value indicating success.
*/
int print_env(FILE* fh, char** envp)
{
    if (NULL == envp || NULL == *envp || NULL == fh)
        return -1;

    for(int i = 0; NULL != envp[i]; ++i) {
        fprintf(fh, "Printing ENV val %d: %s\n", i, envp[i]);
    }

    return 0;
}

int main(int argc, char** argv, char** envp)
{
    int value = 0;
    FILE* fh = NULL;

    if((value = print_env(stdout, envp))) {
        printf("Failed to print env!\n");
        return value;
    }
    
    if((value = open_file("test.txt", &fh))) {
        printf("Failed to open file!\n");
        return value;
    }   

    if((value = print_env(fh, envp))) {
        printf("Failed to write env to file!\n");
        goto cleanup;
    }
    
cleanup:   
    fclose(fh);
    return value;
}
