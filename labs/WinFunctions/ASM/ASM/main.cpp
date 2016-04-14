#include <Windows.h>
#include <stdio.h>

extern "C" int __stdcall first_func(int, int);
extern "C" int __stdcall second_func(int, int);
extern "C" size_t __cdecl  third_func(char*, size_t);
extern "C" void __stdcall fourth_func(unsigned char*, char*, size_t size);

char* strings[] = {
	"the first string.",
	"second string, find the length!",
	"third string. We're testing lots of them now.",
	NULL,
};

void convert(unsigned char* in, char* out, int sz)
{
	if (NULL == in || NULL == out)
		return;

	for (int i = 0; i < sz; ++i)
		out[i] = in[i] ^ 0x5f;
}

unsigned char src[] = { 0x12, 0x51, 0x62, 0x61, 0x127, 0x23, 0x62, 0x45, 0x59, 0x60, 0x55, 0x58, 0x58, 0x44, 0x58 };


#define EQ(x, y)\
	do { x == y ? printf("[*] Success! Test passed.\n") : printf("[x] %s : %d - Test failed! %d is not equal to %d!", __FILE__, __LINE__, x, y); } while (0)

void first_test()
{
	int result = 0;

	printf("Preparing to run first function: stdcall add\n");
	result = first_func(4, 5);
	EQ(9, result);
}

void second_test()
{
	int result = 0;


	printf("Preparing to run second function: stdcall subtract\n");
	result = second_func(20, 10);
	EQ(10, result);

}

void third_test()
{
	int result = 0;
	size_t szres = 0;

	printf("Preparing to run third function: cdecl strnlen\n");
	for (int i = 0; strings[i] != NULL; ++i) {
		szres = third_func(strings[i], strlen(strings[i]));
		EQ((int)strlen(strings[i]), (int)szres);
	}
}

void fourth_test()
{
	char buf1[sizeof(src) + 1] = { 0 };
	DWORD canary = 0xc0ffee;
	char buf2[sizeof(src) + 2] = { 0 };
	printf("Preparing to run the fourth function: XOR'd array\n");
	convert(src, buf2, sizeof(src));
	fourth_func(src, buf1, sizeof(src));
	if (0xc0ffee != canary) {
		printf("[x] Unbounded copy detected!\n");
		return;
	}

	EQ(0, (int)strcmp(buf1, buf2));
}

int main(int argc, char** argv)
{
	first_test();
	//second_test();
	//third_test();
	//fourth_test();

	return 0;
}