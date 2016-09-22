:title: Introduction to Assembly
:data-transition-duration: 1500
:css: asm.css

An introduction to x86 and x86_64

----

Section 2
=========

Practical Application

----

Utility Methods
===============

----

Objectives
==========

* Implement a number of basic standard library functions in assembly
* Implement some essential data structures in assembly
* (OPTIONAL) Complete provided bonus labs

----

Assembly: A Practical Application

.. note::

	This section of the course will be mostly hands-on, with relatively short sections of lecture, followed
	by larger blocks of labs. The labs have (mostly) been staged so that there are a set of easier exercises,
	followed by a section of bonus material. If you complete any of the labs early, the bonus material is
	provided for you to work on. Most of the bonus sections have a C implementation provided for reference.

----

Utility Functions
=================

* Copy and search functions (Some methods from previous labs, such as the string instruction lab, may be helpful here)
	+ strlen
	+ memcpy
	+ memset
	+ memchr
	+ memcmp
	+ strchr
	+ strcmp
	+ strcpy
	+ strstr 

* Conversion
	+ atoi

----

atoi

.. code:: C

	int atoi(char* c)
	{
		long len = 0;
		int step = 1;
		int accum = 0;

		if(NULL == c)
			return 0;

		// We will start from the 1's place
		len = strlen(c);
		--len;
		while(len >= 0) {
			// subtract 0x30 (the difference 
			// between the number and its 
			// ordinal value as an ASCII character),
			// multiply by the step,
			// and add.
			accum += (c[len] - 0x30) * step;
			--len;
			// Move up by a factor of 10. 
			// First: 1's place, then 10's, etc.
			step *= 10;
		}

		return accum;
	}

----

Sorting (Bonus Labs)
====================

* Insertion Sort
* Quicksort

----

Lab 13 - Utility Functions
==========================

----

System Calls - an Introduction
==============================

----

Objectives
==========

* Understand the basic function and implementation of system calls (including legacy methods)
* Understand the basic functionality provided by a C Runtime
* Implement a system call wrapper in assembly
* Begin work on a C Runtime

----

System Calls
============

* What they are
* How they work

----

Legacy System Call Method
=========================

* int 0x80/0x2e

----

Modern Alternative
==================

* x86: sysenter / sysexit
* x64: syscall

----

My First Syscall
================

Wrapping system calls

* x86
* x64

----

Getting Information
===================

* Man pages often have a comprehensive list of required flags (even if definitions are buried in header files)
* May be more than 1 section to a man page (if the page overlaps with a utility page "2" generally has dev docs)

.. code:: bash

	~$ man mmap		
	~$ man 2 open

----

C Runtimes: A good _start
=========================

* What is a runtime?
* int main() vs your program's real entry point
* Building without a standard library
* stuff your crt usually does

----

Compiling with no CRT
=====================

* All functions will need to implemented/provided
* Initial effort: Wrap system functionality
	+ sys_exit
	+ write

----

:class: split-table

sys_exit
========


+------+-----------------+
| RAX  |  RDI            |
+------+-----------------+
| 60   | status (int)    |
+------+-----------------+

----

Implementing sys_exit
=====================

.. code:: nasm

	mov rax, 60  ; the syscall number (in this case exit)
	xor rdi, rdi ; argument 1, the exit code
    syscall 
	ret

----

:class: split-table

Some Setup
==========

* STDOUT - A special kind of file descriptor (1)
* sys_write

+------+-----------------+-------------------+-----------+
| RAX  |  RDI            |  RSI              | RDX       | 
+------+-----------------+-------------------+-----------+
| 1    | fd              | buffer ptr        | Count	 |
+------+-----------------+-------------------+-----------+

----

Lab 14
======

Finally, time for "Hello, World!"

----

Allocation
==========

----

Objectives
==========

* Understand the basic roles and responsibilities of a simple allocator 
* Understand the function of the mmap syscall
* Implement a simple allocator

----

Allocating Memory
=================

* The Heap - no longer just a call to malloc
* How do we add memory to our process?

----

About Allocators
================

* Many different strategies for heap management
	+ Lots of special cases to consider
	+ Multithreading adds more concerns (we'll talk more about this later)
* Our strategy here will try to remain simple

----

Our Allocator Strategy
======================

* Getting new memory from the kernel every time we need to allocate is very inefficient
* We'll want to build a list of unused (or "free") chunks to hand out when allocations are requested
* When a chunk is requested, we can check the free list first (if initialized), to see if we have something that will work
* If not, we'll need to allocate memory

----

Asking for More
===============

* We can actually ask for memory from the kernel in two ways:
	+ mmap - This is the more "modern" approach; we can ask the kernel for more memory by requesting an anonymous page mapping (we'll be discussing mmap in much greater detail over the next few sections)
	+ brk - We won't really touch this too much; it lets you extend or shrink the end of the memory mappings in your program
* Some additional initialization logic can also be added to _start, if needed

----

:class: split-table

mmap
====

* Lets us create a memory mapping
* May be backed by a file, or anonymous
* This will be the base for our allocator

+------+-----------------+-------------------+-----------+------------+----------------------+--------+
| RAX  |  RDI            |  RSI              | RDX       | R10        | R8                   | R9     |
+------+-----------------+-------------------+-----------+------------+----------------------+--------+
| 9    | addr (or NULL)  | length            | Protection| Flags      | Descriptor (or NULL) | offset |
+------+-----------------+-------------------+-----------+------------+----------------------+--------+

----

Arguments
=========

* Protection (from mman-linux.h)

.. code:: nasm

	%define PROT_READ	0x1	 ; Page can be read.  
	%define PROT_WRITE	0x2	 ; Page can be written.  
	%define PROT_EXEC	0x4	 ; Page can be executed.  
	%define PROT_NONE	0x0	 ; Page can not be accessed.  

* Flags (need to be OR'd together)

.. code:: nasm

	%define MAP_ANONYMOUS	0x20  ; Don't use a file.  
	; ... 
	%define MAP_PRIVATE		0x02  ; Changes are private.  

----

Creating a Heap
===============

* Beginning the Process: malloc and free

* Steps to success
	+ Initialization: Handled in _start
	+ Making Requests: Define a "block" size
	+ Keeping a list: Maintain a list of "free" chunks

----

:class: split-table

munmap
======

+------+-----------------+-------------------+
| RAX  |  RDI            |  RSI              | 
+------+-----------------+-------------------+
| 11   | addr            | length            |
+------+-----------------+-------------------+

----

Problem Description
===================

Some pseudo-C to describe our malloc strategy:

Some initial structure information:

.. code:: c

	/** 
	* Our free list node structure definition.
	* In this case, just a simple linked list.
	*/
	struct heap_node;
	typedef struct heap_node {
		struct heap_node* next;
		unsigned long size;
		unsigned char data[1];
	} heap_node;

	typedef struct free_list {
		heap_node* head;
	} free_list;

	/* Add structure overhead to our alloc size */
	#define HEAP_ALLOC_SIZE(x)	(sizeof(heap_node) + x)
	/* The beginning of our free list; head starts out NULL */
	free_list free_start;

----


Problem Description
===================

.. code:: c
	
	/* NOTE: n is the allocation size requested */
	heap_node* check_free_list(unsigned long n)
	{
		heap_node* prev = NULL;
		heap_node* current = NULL;

		/* 
		* If our list is empty, we need to
		* allocate. 
		*/
		if(NULL == free_start->head)
			return NULL;

		current = free_start->head;
		prev = current;
		if (current->size >= n) {
			/* Remove from the list */
			free_start->head = (current->next != NULL) ? 
					&current->next : NULL;
			return current;
		} else if (current->next == NULL) {
			return NULL;
		}

		do {
		/* Walk the list, find and remove a
		* chunk of at least size n 
		*/
		} while(current->next);
		return NULL;
	}

----

Problem Description
===================

.. code:: c

	void* allocate(unsigned long n)
	{
		heap_node* tmp = NULL;
		unsigned long alloc_size = 0;

		/* 
		* We'll check the free list first,
		* and see if there is a suitable chunk
		*/ 
		if(NULL != (tmp = check_free_list(n))) {
			/* We found a match! */
			return (void*)tmp->data;
		}

		/* 
		* Since we need to allocate, we have
		* to add enough to our header to
		* account for our heap_node struct!
		*/
		alloc_size = HEAP_ALLOC_SIZE(n);
		/* We'll allocate some space */
		if(NULL == (tmp = mmap_anon_page(alloc_size))) {
			return NULL;
		}

		tmp->size = n;
		tmp->next = NULL;
		/* Return the beginning of the data buffer */
		return (void*)tmp->data;
	}

----


Problem Description
===================

.. code:: c

	void deallocate(void* p)
	{
		heap_node* node = NULL;

		if(NULL == p)
			return;
		/* 
		* Subtract the size of the bookkeeping struct to get 
		* back to the top of the heap_node structure in 
		* memory
		*/
		node = (heap_node*)(((char*)p) - sizeof(heap_node));
		/* Zero the user provided data */
		memset(node->data, 0, node->size);
		/* Add the node to the free list */
		node->next = &free_start->head;
		free_start->head = node;
	}

----

Additional Steps to Consider
============================

* Keep track of the number of items on the free list; release some if it becomes too large
* Keep multiple free lists based on chunk size

----

Lab - Creating an Allocator
===========================

