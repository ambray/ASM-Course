#include <stdio.h>
#include <stdlib.h>


extern "C" int first_func(void);

int main(int argc, char** argv)
{
	printf("Return: %d\n", first_func());
	return 0;
}
