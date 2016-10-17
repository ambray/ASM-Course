#include <Windows.h>
#include <sstream>
#include <string>
#include <iostream>

#define LIST_LENGTH		100

int glbl = 0;
int v = 0;

struct Node;
struct Node {
	Node* next;
	size_t data;
};

extern "C" void __stdcall unpack_string(unsigned char* input, char* output, size_t length);
extern "C" Node* __fastcall walk_list(Node* start, size_t needle);
extern "C" int __cdecl call_function();

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

extern "C" int __stdcall first_func()
{
	glbl = (int)GetTickCount();
	return glbl;
}

extern "C" int __cdecl test_func(int value)
{

	if (value == glbl) {
		v = (int)GetTickCount();
		return v;
	}
	else {
		v = 0;
		return 0;
	}


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

	for	(auto i = 0; i < LIST_LENGTH; ++i) {
		try {
			current = new Node;
			ZeroMemory(current, sizeof(Node));
			current->data = (size_t)rand();
			lg = (current->data > lg) ? current->data : lg;
			tmp->next = current;
			tmp = current;
		} catch (std::bad_alloc) {
			std::cout << "Failed to allocate memory! Will try again..." << std::endl;
			continue;
		}
	}

	*largest = lg;
	return list_head;
}

size_t bad_needle(Node* list)
{
	size_t tmp = 0;
	Node* current = NULL;
	bool inList = false;

	do {
		tmp = (size_t)rand();
		
		for (current = list; current != NULL; current = current->next) {
			if (tmp == current->data) {
				inList = true;
				break;
			} else {
				inList = false;
			}
		}
	} while (inList);

	return tmp;
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

void test_unpack_string()
{
	char base[] = "lorem ipsum and all that stuff.";
	unsigned char input[sizeof(base)] = { 0 };
	char out[sizeof(base) + 1] = { 0 };

	for (auto i = 0; i < sizeof(base); ++i)
		input[i] = base[i] << 1;

	PRINT_BEGIN("Unpack String");
	unpack_string(input, out, sizeof(base));

	compare_vals(base, out, sizeof(base));
}

void test_walk_list()
{
	size_t needle = 0;
	Node* list = populate_list(&needle);
	if (NULL == list)
		return;
	PRINT_BEGIN("Walk List - Test Case 1");
	Node* found = walk_list(list, needle);
	if (NULL == found) {
		std::cout << "Value returned from walk_list function was NULL! Test failed!" << std::endl;
		return;
	}
		
	compare_vals(found->data, needle);
	clean_list(list);

	if (NULL == (list = populate_list(&needle))) {
		std::cout << "Failed initial allocation for second test!" << std::endl;
		return;
	}

	needle = bad_needle(list);

	PRINT_BEGIN("Walk List - Test Case 2");
	compare_vals((void*)NULL, (void*)walk_list(list, needle));

	clean_list(list);
}

void test_call_function()
{
	int output = 0;
	glbl = (rand() % 3) + 1;
	PRINT_BEGIN("Call Function Test");
	if (0 == (output = call_function())) {
		std::cout << "Bad output provided! Wrong flags give to test function!" << 
			      "Expected: " << (glbl | (1 << 4)) << std::endl;
		return;
	}
	compare_vals(glbl, output);
}

int main(int argc, char** argv, char** envp)
{
	srand(GetTickCount());

	test_unpack_string();
	//test_walk_list();
	//test_call_function();

	return 0;
}
