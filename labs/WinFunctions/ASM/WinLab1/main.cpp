#include <Windows.h>
#include <stdio.h>

#define EQ(x, y)\
	do { x == y ? printf("[*] Success! Test passed.\n") : printf("[x] %s : %d - Test failed! %d is not equal to %d!", __FILE__, __LINE__, x, y); } while (0)

extern "C" void __stdcall first_func(int* firstVec, int* secondVec, int* thirdVec);
extern "C" int __stdcall second_func(int first, int second);

void first_test()
{
	int set1[] = { 10, 20, 30, 40 };
	int set2[] = { 20, 30, 40, 50 };
	int res[4] = { 0 };

	printf("Preparing to run first test... (Adding two vectors)\n");
	first_func(set1, set2, res);

	printf("Result: %d | %d | %d | %d\n", res[0], res[1], res[2], res[3]);
	
	for (int i = 0; i < 4; ++i) {
		EQ((set1[i] + set2[i]), res[i]);
	}
}

void second_test()
{
	int first = rand();
	int second = rand();
	int tmp = (first > second) ? first : second;

	printf("Preparing to run the second test... (Getting the max of two numbers-%d and %d)\n");
	EQ(tmp, second_func(first, second));
}

int main(int argc, char** argv)
{
	srand(GetTickCount());
	first_test();
	second_test();
	return 0;
}