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
	+ itoa

* Other
	+ Simple Hash Function

----

itoa / atoi

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

Data Structures
===============

* Must implement at least linked list
* Each structure has 4 functions that must be completed:
	+ Add node (which should take a pointer to a pre-built node)
	+ Add value (or key)
	+ Remove node
	+ Find node (by key)


----

Data Structure Labs
===================

* Linked List

* Bonus:
	+ Double linked list
	+ Hash table

----

Sorting
=======

* Insertion Sort

* Bonus:
	+ Quicksort

.. note::

	Instructor demo of insertion sort should be done here.

----

Lab - Utility Functions
=======================

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

* x86: syscall
* x64: sysenter / sysexit

----

My First Syscall
================

Wrapping system calls

* x86
* x64

----

C Runtimes: A good _start
=========================

* What is a runtime?
* int main() vs your program's real entry point
* Building without a standard library
* stuff your crt usually does

----

Lab XX
======

Implementing a stub CRT

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

mmap
====

* Lets us create a memory mapping
* May be backed by a file, or anonymous
* This will be the base for our allocator

----

Creating a Heap
===============

* Beginning the Process: malloc and free

* Steps to success
	+ Initialization: Handled in _start
	+ Making Requests: Define a "block" size
	+ Keeping a list: Maintain a list of "free" chunks

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
	+ A bookkeeping mechanism to represent your access to a resource
	+ Some typically reserved numbers: 1/2/3 (for std in/out/err)

----

Reading and Writing
===================

Finally, time for "Hello, World!"

----

File Operations
===============

* Open and Close (for existing files)
* Creat and Unlink (for creating and deleting)
* Random access via lseek
* Syncing changes

----

mmap - A different use
======================

* Can be used to map a file into memory
* Essentially (part of) how executables are loaded
* Can be more efficient for I/O 

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
* Implement a simple threading model

----

What is a Thread?
=================

* Each thread contains its own process
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
* Some special properties of xchg
* Introduction cmpxchg

----

The clone Syscall
=================

* This syscall creates a new process, but allows you to specify some amount of sharing with the parent process
* Threads and processes in Linux are synonymous, but the amount of resources they share may differ

----

Creating a Simple Spinlock
==========================

----

Lab and Demo - Threading and Synchronization
============================================

----

Review
======

