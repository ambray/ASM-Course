#include <Windows.h>
#include <sstream>
#include <string>
#include <iostream>

#define LIST_LENGTH		30

struct Node;
struct Node {
	Node* next;
	size_t data;
};

size_t gSum = 0;

extern "C" int __stdcall fibonacci(int n);
extern "C" void __stdcall walk_list_map(Node* n, void(*)(size_t));

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
	push eax
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

int calc_fib(int n)
{
	int* table = NULL;
	int tmp = 0;

	try {
		table = new int[n + 1];
		ZeroMemory(table, sizeof(int) * (n + 1));
		table[1] = 1;
		for (auto i = 2; i <= n; ++i)
			table[i] = table[i - 1] + table[i - 2];

		 tmp = table[n];
		 delete[] table;
	}
	catch (std::bad_alloc) {
		std::cout << "Failed to allocate memory for calculation!" << std::endl;
	}

	return tmp;
}

size_t validate(Node* start)
{
	size_t total = 0;
	for (; start != NULL; start = start->next)
		total += start->data;

	return total;
}

Node* populate_list(size_t* largest)
{
	Node* list_head = NULL;
	Node* tmp = NULL;
	Node* current = NULL;
	size_t lg = 0;

	if (NULL == largest)
		return NULL;

	try {
		list_head = new Node;
		ZeroMemory(list_head, sizeof(Node));
		lg = (size_t)rand();
		list_head->data = lg;
		tmp = list_head;
	}
	catch (std::bad_alloc) {
		std::cout << "Failed initial allocation!" << std::endl;
		return NULL;
	}

	for (auto i = 0; i < LIST_LENGTH; ++i) {
		try {
			current = new Node;
			ZeroMemory(current, sizeof(Node));
			current->data = (size_t)rand();
			lg = (current->data > lg) ? current->data : lg;
			tmp->next = current;
			tmp = current;
		}
		catch (std::bad_alloc) {
			std::cout << "Failed to allocate memory! Will try again..." << std::endl;
			continue;
		}
	}

	*largest = lg;
	return list_head;
}


void clean_list(Node* n)
{
	Node* current = NULL;
	Node* prev = NULL;

	current = n;
	if (NULL == current)
		return;
	do {
		prev = current;
		current = current->next;
		delete prev;
	} while (NULL != current);

}


void test_fibonacci()
{
	int expected = 0;
	int result = 0;

	PRINT_BEGIN("Fibonacci Test Case 1");
	result = fibonacci(10);
	expected = calc_fib(10);
	compare_vals(expected, result);
	PRINT_BEGIN("Fibonacci Test Case 2");

	result = fibonacci(20);
	expected = calc_fib(20);
	compare_vals(expected, result);


	PRINT_BEGIN("Fibonacci Test Case 3");
	result = fibonacci(5);
	expected = calc_fib(5);
	compare_vals(expected, result);


	PRINT_BEGIN("Fibonacci Test Case 4");
	result = fibonacci(15);
	expected = calc_fib(15);
	compare_vals(expected, result);
}

void test_walk_list_map()
{
	size_t lg = 0;
	size_t expected = 0;
	size_t result = 0;
	Node* list = populate_list(&lg);

	auto fp = [](size_t t) {
		gSum += t;
	};

	if (list == NULL)
		return;

	PRINT_BEGIN("Walk List Map test");
	walk_list_map(list, fp);
	expected = validate(list);
	compare_vals(expected, gSum);
	clean_list(list);
}

int main(int argc, char** argv, char** envp)
{
	srand(GetTickCount());
	test_fibonacci();
	//test_walk_list_map();
	return 0;
}