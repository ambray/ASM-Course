#include <Windows.h>
#include <sstream>
#include <string>
#include <iostream>

extern "C" int __stdcall sum_array(int* buffer, int size);
extern "C" int __cdecl find_largest(unsigned long* buffer, int size);

#define PRINT_BEGIN(test)\
	do {\
		std::cout << __COUNTER__ << " - Running the " << test << " Test, in " << __FUNCTION__\
				  << " : " << __LINE__ << std::endl;\
	} while(0)

template<typename T>
void compare_vals(T first, T second)
{
	std::stringstream result;
	if (first == second)
		result << "[*] Success! Values are equal!";
	else
		result << "[x] Test Failed! Results are not equal!";
	result << " Expected: " << first << " | Received: " << second << ", In test: " << std::endl;
	std::cout << result.str();
}

template<typename T>
void compare_vals(T* first, T* second, size_t size)
{
	std::stringstream result;
	std::stringstream contents;
	bool isEqual = true;

	for (int i = 0; i < size; ++i, ++first, ++second) {
		if (*first == *second) {
			contents << " Expected: " << *first << " | Received: " << *second << "\t";
			isEqual &= true;
		}
		else {
			contents << " Expected: " << *first << " | Received: " << *second << "\t";
			isEqual = false;
		}
	}
	if (isEqual)
		result << "[*] Success! Values are equal! " << contents.str();
	else
		result << "[x] Test Failed! Results are not equal! " << contents.str();

	result << std::endl;
	std::cout << result.str();
}

template <typename T>
void populate_buffer(T* buffer, size_t size)
{
	if (NULL == buffer)
		return;
	for (auto i = 0; i < size; ++i)
		buffer[i] = (T)rand();
}

void test_sum_array()
{
	int base[] = { 10, 20, 30, 60, 80 };
	int expected = 0;
	int result = 0;
	int buf[8] = { 0 };

	PRINT_BEGIN("Sum Array - Base Case");
	result = sum_array(base, sizeof(base) / sizeof(int));
	for (auto i = 0; i < sizeof(base) / sizeof(int); ++i)
		expected += base[i];
	compare_vals(expected, result);
	result = 0;
	expected = 0;

	PRINT_BEGIN("Sum Array - Random Values");
	populate_buffer(buf, sizeof(buf) / sizeof(int));
	result = sum_array(buf, sizeof(buf) / sizeof(int));
	for (auto i = 0; i < sizeof(buf) / sizeof(int); ++i)
		expected += buf[i];
	compare_vals(expected, result);

}


void test_find_largest()
{
	DWORD base[] = { 4, 20, 3, 5, 50, 10 };
	DWORD base2[] = { 4, 20, 3, 5, 50, 10, 70 };
	size_t working_size = 0;
	DWORD expected = 0;
	DWORD result = 0;
	DWORD buf[20] = { 0 };

	PRINT_BEGIN("Find Largest - Base Case 1");
	working_size = sizeof(base) / sizeof(DWORD);
	result = find_largest(base, working_size);
	expected = 50;
	compare_vals(expected, result);

	expected = 0;
	result = 0;

	PRINT_BEGIN("Find Largest - Base Case 2");
	working_size = sizeof(base2) / sizeof(DWORD);
	result = find_largest(base2, working_size);
	expected = 70;
	compare_vals(expected, result);
	
	expected = 0;
	result = 0;

	PRINT_BEGIN("Find Largest - Random Values");
	working_size = sizeof(buf) / sizeof(DWORD);
	populate_buffer(buf, working_size);
	result = find_largest(buf, working_size);
	expected = buf[0];
	for (auto i = 0; i < working_size; ++i)
		expected = (buf[i] > expected) ? buf[i] : expected;

	compare_vals(expected, result);

}

int main(int argc, char** argv, char** envp)
{
	srand(GetTickCount());
	test_sum_array();
	//test_find_largest();
	return 0;
}