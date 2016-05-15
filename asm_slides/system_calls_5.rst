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
	+ strstr (BONUS)

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

----

I/O
===

----

Objectives
==========

* Understand and Identify basic facts about Linux files and file descriptors
* Implement wrappers for several file I/O system calls
* Understand and utilize file-based process bookkeeping mechanisms (via /proc)

----

Files and Operations
====================

* UNIX Model - Everything is a file!
* File Descriptors
	+ A bookkeeping mechanism to represent your access to a resource
	+ Some typically reserved numbers: 1/2/3 (for std in/out/err)

----

File Operations
===============

* Read and Write
* Open and Close (for existing files)
* Unlink (for deleting)
* Syncing changes - msync and fsync

----

Process Information and Virtual Memory
======================================

----

mmap - A different use
======================

* Can be used to map a file into memory
* Essentially (part of) how executables are loaded
* Can be more efficient for I/O 

----

mmap - Some new flags
=====================

* Required to be set to Shared for changes to appear in base file
* Changes may not show up until either munmap or a call to msync

.. code:: nasm

	%define MAP_SHARED	0x01  ; Share changes.  


----

Process Information and Virtual Memory
======================================

* /proc - a special type of directory
* /proc/self
* Getting to process parameters - /proc/self/cmdline

----

:class: split-table shrink-table

Syscall Info - pt1
==================

+--------+------+------------------+-------------------+-----------+------------+------------+--------+
|Syscall | RAX  |  RDI             |  RSI              | RDX       | R10        | R8         | R9     |
+--------+------+------------------+-------------------+-----------+------------+------------+--------+
| mmap   | 9    | address          | length            | Protection| Flags      | Descriptor | offset |
+--------+------+------------------+-------------------+-----------+------------+------------+--------+
| munmap | 11   | address          | length            |           |            |            |        | 
+--------+------+------------------+-------------------+-----------+------------+------------+--------+ 
| read   | 0    | Descriptor       | buffer ptr        | Count     |            |            |        |
+--------+------+------------------+-------------------+-----------+------------+------------+--------+
| write  | 1    | Descriptor       | buffer ptr        | Count     |            |            |        | 
+--------+------+------------------+-------------------+-----------+------------+------------+--------+
| open   | 2    | filename (char*) | flags             |   mode    |            |            |        |
+--------+------+------------------+-------------------+-----------+------------+------------+--------+ 
| close  | 3    | Descriptor       |                   |           |            |            |        | 
+--------+------+------------------+-------------------+-----------+------------+------------+--------+ 

----

:class: split-table shrink-table

Syscall Info - pt2
==================

+--------+------+--------------+-------------------+-----------+------------+------------+--------+
|Syscall | RAX  |  RDI         |  RSI              | RDX       | R10        | R8         | R9     |
+--------+------+--------------+-------------------+-----------+------------+------------+--------+
| unlink | 87   | Path (char*) |                   |           |            |            |        | 
+--------+------+--------------+-------------------+-----------+------------+------------+--------+ 
| msync  | 26   | address start| length            | flags     |            |            |        | 
+--------+------+--------------+-------------------+-----------+------------+------------+--------+ 
| fsync  | 74   | Descriptor   |                   |           |            |            |        | 
+--------+------+--------------+-------------------+-----------+------------+------------+--------+ 

----

Flags and Modes
===============

Msync options

.. code:: nasm

	; Flags to `msync'.  
	%define MS_ASYNC	1  ; Sync memory asynchronously.  
	%define MS_SYNC		4  ; Synchronous memory sync.  

Open options:

* One of the following options must be chosen:

.. code:: nasm

	%define O_RDONLY	   00
	%define O_WRONLY	   01
	%define O_RDWR		   02


* Zero or more of the following may be chosen:

.. code:: nasm

	%define O_CREAT	   0100	; Create the file 
	%define O_TRUNC	  01000	; Truncate (if exists) 
	%define O_APPEND  02000 ; Append 


----

Mode
====

* If file is being created, specifies permissions to set on it
* Can be one of the following values (follow UNIX-style permission rules) specified on the next slide

----

:class: split-table shrink-table

+---------+-------+--------------------------------------------------+
| S_IRWXU | 00700 | user  (file  owner)  has read, write and execute |
|         |       | permission                                       |
+---------+-------+--------------------------------------------------+
| S_IRUSR | 00400 | user has read permission                         |
+---------+-------+--------------------------------------------------+
| S_IWUSR | 00200 | user has write permission                        |
+---------+-------+--------------------------------------------------+
| S_IXUSR | 00100 | user has execute permission                      |
+---------+-------+--------------------------------------------------+
| S_IRWXG | 00070 | group has read, write and execute permission     |
+---------+-------+--------------------------------------------------+
| S_IRGRP | 00040 | group has read permission                        |
+---------+-------+--------------------------------------------------+
| S_IWGRP | 00020 | group has write permission                       |
+---------+-------+--------------------------------------------------+
| S_IXGRP | 00010 | group has execute permission                     |
+---------+-------+--------------------------------------------------+
| S_IRWXO | 00007 | others have read, write and execute permission   |
+---------+-------+--------------------------------------------------+

----

Lab - File I/O and Expanding _start
===================================

----

Threading
=========

----

Objectives
==========

* Understand at a basic level the Linux threading model
* Understand some of the pitfalls of working with multithreaded applications
* Understand and implement some of the basic synchronization tools provided by the x86(_64) instruction set
* Implement a simple threading library

----

What is a Thread?
=================

* Each thread is essentially a separate stream of execution
	+ The register values for each thread are different
	+ This is referred to as "context"
	+ Transitions from one thread to another is referred to as "switching context"
* Multiple threads may be running at the same time
* It is difficult (if not impossible!) to predict how scheduling will occur

----

Synchronization
===============

* Access to data needs to be synchronized (meaning: we need to make sure only one thread at a time can modify it)
* Race conditions happen if multiple threads are trying to update the same data at once

----

Safe memory access
==================

* Think in terms of "transactions"
* The lock prefix
* Some instructions, such as xchg, implicitly lock

----

The clone Syscall
=================

* This syscall creates a new process, but allows you to specify some amount of sharing with the parent process
* Threads and processes in Linux are synonymous, but the amount of resources they share may differ

----

:class: split-table

Clone
=====

+--------+------+------------------+-------------------+-----------+------------+
|Syscall | RAX  |  RDI             |  RSI              | RDX       | R10        | 
+--------+------+------------------+-------------------+-----------+------------+
| Clone  | 56   | Clone flags      | Stack Pointer     | parent tid| child tid  | 
+--------+------+------------------+-------------------+-----------+------------+

----

Flags
=====

Some flags we'll want for our thread library:

.. code:: nasm

	%define CLONE_VM      0x00000100 ; VM shared between procs.  
	%define CLONE_FS      0x00000200 ; fs info shared  
	%define CLONE_FILES   0x00000400 ; open files shared 
	%define CLONE_SIGHAND 0x00000800 ; signal handlers shared.  
	%define CLONE_THREAD  0x00010000 ; add to same thread group.  

----

Basic Steps to Success
======================

1. Allocate Stack Space
2. Call Clone
3. Transfer Control to Intended function

---- 

Allocating Stack Space
======================

* The stack grows down, and thus we need to give the high part of the new stack segment to clone
* mmap is the best choice to do this, as it has flags that let us specify that we wish to use the allocated memory as a thread stack:

.. code:: nasm

	%define MAP_GROWSDOWN	0x0100

----

Calling Clone
=============

* As seen above, clone has several arguments
* For our purposes, only two are really useful: the flags argument (RDI), and a pointer to our new stack
* We'll need to get to the end of the new stack:

.. code:: nasm

	; assuming rsi contains a pointer to 
	; our newly allocated stack segment
	lea rsi, [rsi + STACK_SIZE]  

----

Calling Clone (cont'd)
======================

* After clone, both the parent and child continue executing in the same place (right after the syscall)
* The child (our newly created thread) will have the same initial register values as the parent, with two exceptions:
	+ RAX - this will be set to 0
	+ RSP - this will now point to our new stack
* The parent will now have (in RAX) the PID of the thread

----

Running the Thread Function
===========================

* A number of options exist to transfer control to the new function
	+ Pass via non-volatile register
	+ Pass via stack
* If any thread-specific setup is to be done, just need to:

.. code:: nasm

	test rax, rax
	jz .child
	jmp .parent

* easiest method of control transfer is probably passing via the new stack

----

Running the Thread Function (cont'd)
====================================

* Recall from our section on control flow that the ret instruction essentially performs "pop rip" (or pop X + jmp X)
* Thus, we can now set our stack up so that the new thread function will be our return point (we'll just change the way our stack looks before the call to clone):

Now, instead of: 

.. code:: nasm

	lea rsi, [rsi + STACK_SIZE]
	; ...
	syscall

we will:

.. code:: nasm

	lea rsi, [rsi + STACK_SIZE - 8]
	mov [rsi], rdi 	; our function pointer
	; ...
	syscall
	; ...
	ret

----

Running the Thread Function (cont'd)
====================================

* With our function set to be at the top of the new stack, we can now simply return
* On return, our new thread will begin executing inside of the thread function
* This works wonderfully, BUT
	+ What happens when the thread function returns?

----

Exit
====

* We need to ensure that we call exit after execution completes
* Since we are at the top of the stack to begin with, there is no place to go
* The easy solution:

.. code:: nasm

		lea rsi, [rsi + STACK_SIZE - 8]
		mov [rsi], rdi 	; our function pointer
		; ...
		syscall
		test rax, rax ; check to see if we are parent/child
		jnz .parent	; jump to end if we are the parent
		pop rax ; pop the function pointer (top of stack)
		call rax 	; call our thread function!
		; ...
		call exit 	; call exit (no place to return)
	.parent:
		; ... 		; parent: cleanup/return
		ret
	

----

A Better Exit Strategy
======================

* We can take the previous code a step further, and add another return address to the stack
* If we put exit first, we will still be able to transfer control in the same fashion, but don't need to wrap out child function with additional calls

.. code:: nasm 

	lea rsi, [rsi + STACK_SIZE - 8]
	mov [rsi], exit 	; our exit function
	sub rsi, 8			; go back just a bit
	mov [rsi], rdi 		; now our function pointer
	; ...
	syscall
	; ...
	ret

----

Race Conditions
===============

* Can occur when multiple threads access data at once, where the data is being modified
* Can be rather difficult to spot at first
* Multiple strategies exist to mitigate
	+ Locks
	+ Atomic Instructions
* Can be difficult to get absolutely correct

.. note::

	Think in terms of a busy intersection with no stop sign.

----

What do Race Conditions look like?
==================================

.. code:: nasm

	mov rax, [rdi] ; we load our data
	; but by the time we reach here,
	; any number of things could have
	; happened to the value in the pointer
	test rax, rax

----

More Problems
=============

* Deadlocks
* Starvation
* Recursive locking
* And much, much, more!

---- 

Making Atomic adds and Comparisons
==================================

.. code:: nasm

	lock xadd		; add in place
	lock bts		; bit test and set
	lock btr		; bit test and clear
	lock cmpxchg	; compare and swap
	xchg			; implicitly locks

----

Creating a Simple Spinlock
==========================

.. code:: nasm

	lock_func:
		; ...
		lock bts [rdi], 0
		jc .done
		jmp lock_func
		; ...
	.done:
		ret
	
	unlock_func:
		; ...
		lock btr [rdi], 0
		; ...

----

Lab and Demo - Threading and Synchronization
============================================

----

Review
======
