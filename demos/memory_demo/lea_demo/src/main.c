#include <stdio.h>
#include <string.h>

struct example {
    unsigned long d1;
    unsigned long d2;
    char buf[25];
};

extern char* calc_address(struct example* tmp);

int main(int argc, char** argv)
{
    struct example x = {0};
    strncpy(x.buf, "Test string!", 24);
    
    char* tmp = calc_address(&x);
    printf("%s\n", tmp);

    return 0;
}   
