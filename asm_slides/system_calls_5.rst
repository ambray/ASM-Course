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
* Implement a sorting algorithm in assembly
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
			// subtract 0x30 (the difference between the number and its 
			// ordinal value as an ASCII character), multiply by the step,
			// and add.
			accum += (c[len] - 0x30) * step;
			--len;
			// Move up by a factor of 10. First: 1's place, then 10's, etc.
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
	xor rdi, rdi ; the first argument in the syscall (in this case, the exit code)
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

Allocator Strategies
====================

// TODO: Talk about some allocator strategies to use

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

.. code:: c

	#define PROT_READ	0x1		/* Page can be read.  */
	#define PROT_WRITE	0x2		/* Page can be written.  */
	#define PROT_EXEC	0x4		/* Page can be executed.  */
	#define PROT_NONE	0x0		/* Page can not be accessed.  */

* Flags (need to be OR'd together)

.. code:: c

	#define MAP_ANONYMOUS	0x20		/* Don't use a file.  */
	/* ... */
	#define MAP_PRIVATE		0x02		/* Changes are private.  */

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

.. code:: c

	#define MAP_SHARED	0x01		/* Share changes.  */

----

File Information
================

* Using stat
* getdents
* Reading directory information

----

Process Information and Virtual Memory
======================================

* /proc - a special type of directory
* /proc/self
* Getting to process parameters

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

* Msync options

.. code:: c

	/* Flags to `msync'.  */
	#define MS_ASYNC	1		/* Sync memory asynchronously.  */
	#define MS_SYNC		4		/* Synchronous memory sync.  */

* Open options
	+ One of the following options must be chosen:

.. code:: c

	#define O_RDONLY	     00
	#define O_WRONLY	     01
	#define O_RDWR		     02


	+ Zero or more of the following may be chosen:

.. code:: c

	#define O_CREAT	   0100	/* Create the file */
	#define O_TRUNC	  01000	/* Truncate (if exists) */
	#define O_APPEND  02000 /* Append */


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

// TODO: Talk about using the syscall; similarities to fork(), etc.
// Show some basic uses of clone... talk about setting up new stack,
// illustrate sharing, setting up register values, etc

+--------+------+------------------+-------------------+-----------+------------+
|Syscall | RAX  |  RDI             |  RSI              | RDX       | R10        | 
+--------+------+------------------+-------------------+-----------+------------+
| Clone  | 56   | Clone flags      | Stack Pointer     | parent tid| child tid  | 
+--------+------+------------------+-------------------+-----------+------------+

----

Flags
=====

Some flags we'll want for our thread library:

.. code:: c

	#define CLONE_VM      0x00000100 /* Set if VM shared between processes.  */
	#define CLONE_FS      0x00000200 /* Set if fs info shared between processes.  */
	#define CLONE_FILES   0x00000400 /* Set if open files shared between processes.  */
	#define CLONE_SIGHAND 0x00000800 /* Set if signal handlers shared.  */
	#define CLONE_THREAD  0x00010000 /* Set to add to same thread group.  */

----

Basic Steps to Success
======================

1.) Allocate Stack Space
2.) Call Clone
3.) Transfer Control to Intended function

---- 

Allocating Stack Space
======================

* The stack grows down, and thus we need to give the high part of the new stack segment to clone
* mmap is the best choice to do this, as it has flags that let us specify that we wish to use the allocated memory as a thread stack:

.. code:: c

	#define MAP_GROWSDOWN	0x0100

----

Calling Clone
=============

* As seen above, clone has several arguments
* For our purposes, only two are really useful: the flags argument (RDI), and a pointer to our new stack
* We'll need to get to the end of the new stack:

.. code:: nasm

	lea rcx, [rcx + STACK_SIZE]  ; assuming rcx contains a pointer to our newly allocated stack segment

----

Running the Thread Function
===========================

----

Join
====

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
		lock bts
		; ...
	
	unlock_func:
		; ...
		lock btr
		; ...

----

Lab and Demo - Threading and Synchronization
============================================

----

Review
======
