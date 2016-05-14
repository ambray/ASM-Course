#include <stdio.h>

extern void write_stuff(char*);
extern void exit_prog(int);

int main(int argc, char** argv, char** envp)
{
    write_stuff("We get to this point.\n");
    write_stuff("And to this point.\n");
    exit_prog(-1);
    write_stuff("But not to here!\n");
    
    return 0;
}
