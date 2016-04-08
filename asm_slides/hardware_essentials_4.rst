:title: Introduction to Assembly
:data-transition-duration: 1500
:css: asm.css

An introduction to x86 and x86_64

----

Memory and Tables
=================

An Introduction.


----

User and Kernel modes
=====================

* x86(_64) defines several modes of operation (or "rings") the processor can work in
* Each mode has various instructions (and portions of memory) it is allowed to perform
* User mode (which is least privileged) is Ring 3 (which is where most of your applications reside)
* Kernel mode (most privileged) is Ring 0, which is where the core (or kernel) of the OS resides
* Rings 1 and 2 are (largely) unused by most operatings systems

----

User Mode
=========

* Mode of least privilege (Ring 3)
* Cannot touch more privileged memory sections
* Cannot execute "privileged" instructions
* Typically must task some facility in the kernel in order to get resources

----

Kernel Mode
===========

* Mode of most privilege (Ring 0)
* Can access any portion of memory (and change protection)
* Can perform privileged instructions
* Device drivers often run here (in addition to the core portions of the OS)

----

Tables and Memory Segmentation
==============================

* Segment registers are a special type of register not covered yet, which come in a variety of flavors
	+ Each of them can be mapped to provide a special "view" of a section of memory
	+ Most modern operating systems use a "flat" memory model, forgoing segmentation (almost) entirely
	+ Still have some use cases, particularly in Windows (covered more later)
* Intel Specifies a number of tables, populated by the OS, which map functionality to the processor.
	+ The Interrupt Descriptor Table, or IDT
	+ The Global Descriptor Table, or GDT
	+ The Local Descriptor Table, or LDT

----

Interrupts
==========

The Interrupt Descriptor Table (IDT)

* What are interrupts?
	+ At their core, interrupts provide a special mechanism to alert the kernel of the operating system to some type of event
	+ Interrupts can be everything from hardware events (e.g., a keypress on a keyboard), to page or segmentation faults
	+ Software interrupts also exist, and were previously used as a mechanism to interact with the kernel (more on this later)
* So what does the IDT do?
	+ Initialized to inform the processor of where Interrupt Service Routines (ISRs) are located
	+ ISRs are special routines provided by the operating system, which get called when an interrupt occurs

.. note::

	We won't spend too much time on this particular topic (as it only loosely relates to segmentation), but it is important to understand how interrupts work (at a low level), and this will give you the foundational knowledge needed to understand what's happening under the hood later on.

----

Interrupts (Cont'd)
===================

* Interrupt Gates
	+ Essentially the entry number (in the IDT) of the ISR you want to call
	+ The 'int' assembly instruction will call the corresponding ISR
	+ The 'iret' instruction is provided (on the kernel side) to return back to user mode (more on this later)

* Example: Using a software interrupt in Linux to perform a system call
	+ This is an (old) way of talking to the kernel (x86)
	+ int 0x80 will look up the 0x80-th entry in the IDT, and call it

The following code will perform an exit(0) on Linux (x86):

.. code:: nasm
	
	mov eax, 0x01	; the system call number
	mov ebx, 0x00	; first parameter
	int 0x80 		; interrupt

---- 

Segment Registers
=================

* The Basics:
	+ CS - Code Segment
	+ DS - Data Segment
	+ SS - Stack Segment
	+ FS - Far Segment
	+ GS - Global Segment

* Example: Getting a value from some offset into a segment

.. code:: nasm

	; Retrieves the value stored at offset
	; 0x33 into the Global Segment
	mov rax, [gs:0x33]

----

Segmentation - Segments
=======================

* What is a segment?
	+ Describes a logical section of memory
	+ Specifies who can access it (e.g., what privilege level you need)
	+ Indicates the range (start address and length)
* Why are they important?
	+ Part of the segmentation model, used to map a flat section of memory to the segment registers

----

Segmentation
============

The Global Descriptor Table (GDT)

* Initialized by the operating system
* Contains various segment descriptors in its entries
* The GDT Register (GDTR) indicates where it is located
* Contains information about how the memory in your system gets mapped
* Also (partially) defines how the transition from user to kernel mode occurs
* Intended to be a global structure

----

Segmentation
============

The Local Descriptor Table (LDT)

* Similar to the GDT
* Intended to have smaller scope: e.g., a per-process construct

----

Segmentation - Real World examples
==================================

* Microsoft uses segmentation to provide fast access to key data structures
* The Thread Environment Block (TEB) in user mode
	+ Hangs off of the FS register in x86/GS in x64
	+ Provides lots of important per-thread information
* The Processor Control Block (or KPRCB) in kernel mode
	+ Hangs off of the FS register in x86/GS in x64
	+ Provides lots of important per-processor information


----

Segmentation
============

Further Reading (if interested): 

* The OSDev Wiki describes GDT initialization - http://wiki.osdev.org/GDT_Tutorial
* The Segment Descriptor Cache - Mr. Robert Collins (from a Dr. Dobbs article) - http://www.rcollins.org/ddj/Aug98/Aug98.html

----

Model Specific Registers (MSRs)
===============================

* Many of these exist for x86(_64)
* Most only accessible in privileged mode
* used (sometimes) via RDMSR and WRMSR
* Others have special instructions
* Mainly documented by vendor (e.g., Intel manual)

----

Time Stamp Counter
==================

* Can read from user mode (via rdtsc)
* Can only modify from kernel mode
* Low bits of result are stored into EAX/high bits in EDX
	+ This is the same on both x86 and x86_x64
	+ x64 - rdtsc will clear the high bits of storage registers
	+ Results can be combined on x64 to full width with a left-shift and a bitwise or

----

Feature Support
===============

* The CPUID instruction can provide information about the current CPU
	+ Vender string
	+ Model number
	+ Size of internal cache
	+ Various features supported

* The instruction behaves similarly on BOTH x86 and x86_64

* The value in EAX at the time of the CPUID call determines what information comes back
	+ 0 -> Vender ID String - stored in EBX/EDX/ECX
	+ 1 -> Returns a bitfield containing supported features
	+ ...

----

Lab 10
======

MSRs and CPUID

----

x87 - The Floating Point Architecture
=====================================

.. image:: ./images/fpu_outline.jpg

----

==============
Data Registers
==============

* Can contain any 32 or 64 bit data
* Can't transfer directly from standard registers (e.g., EAX/RAX)

.. image:: ./images/fpu_data_regs.jpg

----

Floating Point Exceptions
=========================

* Floating point exceptions are separate from typical interrupts
* They are the only interrupts you can disable from an unprivileged operating context
* The previous instruction pointer (and other contextual information) are stored via special registers

----

Floating Point - Additional Information
=======================================

* Floating point hardware also includes its own FLAGS register
* As mentioned in the previous slide, contextual information is stored in special registers under certain circumstances

.. image:: ./images/fpu_outline.jpg

----

Floating Point Encoding
=======================

* Data encoding is a great deal more complicated for floating point than other types
* Floating point numbers are represented via scientific notation (sort of)
* We can store floats in one of three ways:
	+ Single Precision -> which is 32 bits
	+ Double Precision -> which is 64 bits
	+ Quad Precision -> which is 128 bits


----

Floating Point Encoding (cont'd)
================================

Four parts to the equation:

	+ Significand (also called the mantissa) - This is the decimal representation of our number. A non-zero value will always be in the left-most position
	+ Radix - The base to multiply by (e.g., 10)
	+ Exponent - The power to raise the radix to


----

Floating Point Data Encoding
============================

* x87 Registers Show the split between different parts (under the hood)

So if we have a number like 1378.5, and our hardware looks like this:

.. image:: ./images/fpu_data_regs.jpg

We have:

.. image:: ./images/fpu_equation.png

----

Binary Representation
=====================

1. We take the base 2 representation of the number
2. We transform the number, such that it can be represented via scientific notation
3. The exponent is encoded using a "biased" value, which expedites compare operations
4. Since we know that the left-most position of the significand will always be 1, it is dropped for single precision numbers (though it is preserved in doubles).

----

Exponent Values
===============

Bias value added to exponent

.. image:: ./images/fpu_biased_table.jpg

e.g., an exponent of 3 (111 in binary) would get added with 127 (in the case of a single precision float), or 1111111, to get 10000110.

----

Special Exponent Values
=======================

* Some values are preserved for special cases in exponent representation
	+ 00000000 (all 0s) - This value is used to encode +/- infinity
	+ 11111111 (all 1s) - This value is used to indicate NaN (Not a Number)

* NaN simply indicates that the floating point encoded value is not valid.

----

Working with Floating Point 
===========================

* The floating point registers are treated like a stack
* Values get pushed on (via "load" instructions) and popped off/copied (via "store" instructions)

----

FPU Instruction Set
===================

Basic Operations

* Loads (push)
	+ fld - Loads a floating point value from the indicated location, onto the stack
	+ flid - Loads an integer value, encoding it as a double, onto the stack

* Stores
	+ fst - Stores the value on the top of the stack at the specified location (either memory or elsewhere in the floating point stack)
	+ fstp - Performs the same operation as above, but also pops the value off the stack.
	+ fist - Converts the value at the top of the stack to an integer, and stores it at the destination.


*  Exchange: fxch - Swaps the contents of the given floating point registers

----

FPU Conditional Move
====================

fcmovcc - Move if: Copies the contents from the requested register in the stack to the top if the condition is satisfied 

* b (e.g., fcmovb) - Move if below (if CF is set to 1)
* nb - Move if not below (e.g., CF is 0)
* e - Move if equal (e.g., ZF is 1)
* ne - Move if not equal (ZF is 0)
* be - Move if below or equal (CF is 1 or ZF is 1)
* nbe - Move if not below or equal (CF is 0 and ZF is 0)

----

FPU Arithmetic Operations
=========================

* fadd/fsub/fmul - Performs the requested operation on the source and destination operands, storing the results in the destination
* fiadd/fisub/fimul - Similar to above, but performs the requested operation on a floating point and integer value

----

Lab 11
======

Floating Point Operations 

----

Single Instruction, Multiple Data (SIMD)
========================================


