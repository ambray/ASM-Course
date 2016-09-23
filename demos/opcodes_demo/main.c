#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

unsigned char bytes[] = { 0xcc, 0xb8, 0x01, 0x00, 0x00, 0x00, 0xc3 };

int main(int argc, char** argv)
{
	void* buffer = NULL;
	int(*rettrue)() = NULL;

	if (NULL == (buffer = mmap(NULL, sizeof(bytes), PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, 0, 0))) {
		printf("Failed to allocate our buffer!\n");
		return -1;
	}

	memcpy(buffer, bytes, sizeof(bytes));

	rettrue = (int(*)())buffer;

	(rettrue()) ? printf("It returned true!\n") : printf("It didnt' return true :(\n");

	munmap(buffer, sizeof(buffer));
    return 0;
}
