#include <Windows.h>
#include <sstream>
#include <string>
#include <iostream>

extern "C" size_t __cdecl copy_string(char* dest, char* src);
extern "C" void __stdcall get_cpu_string(char* buf);

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

void get_compare(char* buf)
{
	int vals[4] = { 0 };
	__cpuid(vals, 0);

	memcpy(buf, &vals[1], 4);
	memcpy((buf + 4), &vals[3], 4);
	memcpy((buf + 8), &vals[2], 4);
}


void test_copy_string()
{
	
	char base[] = "Lorem ipsum, this is a test string, and all that stuff.";
	DWORD canary = 0xc0ffee;
	char dest[sizeof(base)] = { 0 };
	

	PRINT_BEGIN("Copy String Test");
	copy_string(dest, base);
	if (0xc0ffee != canary) {
		std::cout << "Unbounded copy in test!" << std::endl;
		return;
	}
	compare_vals(base, dest, sizeof(base));
}

void test_get_cpu_string()
{
	char buf[13] = { 0 };
	char out[13] = { 0 };

	PRINT_BEGIN("CPU String Test");
	get_cpu_string(buf);
	std::cout << "First: " << buf << std::endl;
	get_compare(out);
	std::cout << "Second: " << out << std::endl;
	compare_vals(out, buf, sizeof(out));
}



int main(int argc, char** argv, char** envp)
{
	srand(GetTickCount());
	test_copy_string();
	//test_get_cpu_string();
	return 0;
}
