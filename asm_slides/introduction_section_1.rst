:title: Introduction to Assembly
:data-transition-duration: 1500
:css: asm.css

An introduction to x86 and x86_64

----

Introduction to Assembly Programming
====================================

.. code:: nasm

	instructor	db "Aaron Bray", 0x0a, 0x00
	email  db "aaron.m.bray@gmail.com", 0x0a, 0x00

----

Course Roadmap
==============

.. code:: nasm

	content:
		jmp .introduction

	.introduction:
		mov rax, HowToAsm
		jmp .basic_operations

	.basic_operations:
		call .arithmetic
		call .bit_operations
		mov rcx, DataTypes
		jmp .control_flow

	.control_flow:
		jmp .hardware_essentials

	.hardware_essentials:
		mov rax, Memory
		mov rcx, Interrupts
		call FloatingPoint
		call Simd
		call .systems_programming

	.systems_programming:
		ret

----

Assembly: An Introduction
=========================

----

Objectives
==========

* Understand the relationship between assembly language and opcodes
* Understand byte ordering, as it pertains to Assembly Programming
* Identify x86(_64) General Purpose Registers
* Perform basic memory access operations
* Begin debugging with the GNU Source-Level Debugger (GDB)
* Understand basic data sizes and types with regard to x86(_64)

----

Understanding Assembly
======================

* What is Assembly?

.. note::

	Collection of mnemonics that translate into instructions the CPU can execute. Assembly still has a variety of uses, from debugging and reverse engineering, to accessing instructions not exposed via C (such as hardware virtualization).

----

:data-rotate: 90

Assembly Instructions
=====================

This set of instructions:

:class: code-border

.. code:: nasm

	mov eax, 0x01
	ret

Becomes...

.. note::
	
	Thus, this set of instructions becomes the follow set of opcodes.

----

:data-x: r0
:data-y: r0
:data-rotate-y: 90

Opcodes
=======

\...This set of opcodes




.. code:: objdump-nasm

	0xb8 0x01 0x00 0x00 0x00
	0xc3

.. note::

	Perform opcodes demo

----

:data-x: r0
:data-y: r2000
:data-rotate-y: 0

Syntax Differences
==================

* Intel Syntax

.. code:: nasm

	mov eax, 0x01

* AT&T Syntax

.. code:: gas

	movl $0x01, %eax

.. note::

	This is one very blatant example, but many other assemblers (MASM, etc) will have small quirks to how you type in your assembly instructions. All equate to (about) the same thing, however.

----

:data-y: r2000


Byte Ordering
=============

* x86(_64) is little Endian
* Most significant byte (not bit) on the left

In memory, this address:

.. code::

	0xdeadbeef

----

:data-x: r0
:data-y: r0
:data-rotate-y: 90

Byte Ordering
=============

Becomes:

.. code::

	0xefbeadde

----

:data-y: r2000

:class: split-table

Byte Ordering
=============

+----------+-----+------+------+-----+
| Initial: | 0xde| 0xad | 0xbe | 0xef|
+----------+-----+------+------+-----+
| Memory:  | 0xef| 0xbe | 0xad | 0xde|
+----------+-----+------+------+-----+

----

General Purpose Registers
=========================

* Shared registers have addressable subregisters
* 64 bit/32 bit/16 bit/8 bit
* x86_64 contains many more general purpose registers than x86
  (though they don't all have subregisters)

----

:data-rotate-x: 90

:class: register-table

x86 and x64 Registers
=====================

.. image:: images/section_1_register_table.jpg

* rbp/ebp - Base Pointer
* rsp/esp - Stack Pointer
* rip/eip - Instruction Pointer (Program Counter)

.. note::

	Being general purpose, most of the registers may be
	used to store arbitrary values, though some may have defined
	uses with certain instructions (which we'll discuss later on).
	The registers listed at the bottom generally have some special uses
	however, where RIP/EIP points at the current place in memory we are executing, and RSP/ESP typically points to the top of the stack (which will also be discussed in greater detail later on).

----

x64 Registers
=============

* r8 - r15

----

:data-x: r2000

Register Data and Pointers
==========================

* Registers can contain up to pointer-sized amounts of data (4 bytes on 32 bit, 8 on 64)
* Registers can also contain memory addresses (pointers) to blocks of data residing elsewhere in the process.

----

Register Data and Pointers - Example
====================================

First, we'll store a pointer (memory address) in rax, and then store some stuff there:
--------------------------------------------------------------------------------------

.. code:: nasm

	mov rax, 0xc0ffee ; a memory address (hopefully valid!)
	mov [rax], 100 ; now we store some data there!

.. image:: images/section_1_pointers.jpg

----

Register Data and Pointers - Example (Part 2!)
==============================================

Now, we'll copy that address into rcx:
--------------------------------------

.. code:: nasm

	mov rcx, rax ; now we copy the pointer!

.. image:: images/section_1_pointers_second_stage.jpg

* Now both point to the same place!

----

Register Data and Pointers - Example (Part 3)
=============================================

Now, we'll access the data stored at the address, and copy it into rcx 
----------------------------------------------------------------------

.. code:: nasm
	
	mov rcx, [rcx] ; copy the data from location 0xc0ffee into rcx

.. image:: images/section_1_pointers_third_stage.jpg	

Please note that this replaces the old value in rcx, which was just the address we're accessing.

----

Now, for our first instruction...

----

NOP
===

* Does nothing!
* Used for padding/alignment/timing reasons
* Idempotent instruction (doesn't affect anything else in the system)

----

Memory Access - mov
===================

Description
-----------

Moves a small block of memory from a source (the right-hand operand) to destination (the left operand). An amount of data may be specified (more on this later).

Basic Use
---------

.. code:: nasm

	mov rax, 0x01      ; immediate - rax is now 1
	mov rax, rcx       ; register - rax now has a copy of ecx
	mov rax, [rbx]     ; memory - rbx is treated as a pointer
    mov rax, qword [rbx + 8] ; copying a quad word (8 bytes)

.. note::

	The mov instruction simply copies data from source (the operand on the right), to destination (the operand on the left).

----

Memory Access - lea
===================

Description
-----------

Calculates an address, but does not actually attempt to access it.

Basic Use
---------

.. code:: nasm

    ; calculate an address by taking the address
    ; of what RDX points at,
    ; and adding 8 bytes to it (perhaps indexing
    ; into an array). Note that we are just calc-
    ; ulating the address, NOT accessing memory.
	lea rax, [rdx + 8]
	mov rax, [rax]     ; actually accessing the memory


----

:data-y: r2000

Memory Access - xchg
====================

Description
-----------

Exchanges the values provided atomically (more on this later).

Basic Use
---------

.. code:: nasm

	xchg rax, rcx   ; exchange two register values
	xchg rax, [rcx] ; exchange a register value with a value stored in memory


----


Debugging
=========

* Debugger Cheat Sheet

.. code:: nasm

  int3 ; breakpoint

.. note::

  Tips for debugging assembly: keep an eye on registers, use breakpoints liberally!

----

GDB
===

* Text User Interface

* Basic Use
  + info
  + help

* ~/.gdbinit

----

GDB
===

* Single Stepping (stepi/si)
* Stepping Over (nexti/ni)

----

GDB
===

* Breakpoints (break)
* info break - shows us information about all currently set breakpoints
* Removing breakpoints (clear and delete)

Example:

.. code:: bash

	(gdb) break myfunc
	Breakpoint 1 at 0x4004a4
	(gdb) info break
	Num 	Type 		 Disp Enb Address
	1		breakpoint   keep y   0x00000000004004a4
	(gdb) delete 1
	(gdb) info break
	No breakpoints or watchpoints

.. note:: 

	Demo stepping and using GDB with a sample init file and our opcodes demo

----

:data-rotate-y: 180

Lab 1
=====

Using mov, lea, and xchg

----

x86(_64) data sizes
===================

* byte - "smallest" addressable unit
* word - two bytes
* dword - double word (4 bytes - pointer width on x86)
* qword - quad word (8 bytes - pointer width on x64)

----


GDB
===

* We can use GDB to examing various places in memory with "x" (for "eXamine")
* x has several options:
	+ x/nfu - where n is the Number of things to examine, f is the Format, and u is the Unit size 
	+ x addr
	+ x $<register> - examines the memory address pointed to by the register

* Format options include:
	+ s - For a NULL-terminated string
	+ i - For a machine instruction
	+ x - For hexidecimal (the default, which changes when x is used)

* Unit size options are a bit confusing in the context of x86(_64) assembly, and include:
	+ b - bytes
	+ h - Halfwords (equivalent to "word" in x86(_64) asm; e.g., 2 bytes)
	+ w - Words (4 bytes, equivalent to dwords)
	+ g - Giant words (8 bytes, equivalent to qwords)

.. note::

	Demo - Dumping memory via GDB

----

Sub Registers
=============

.. image:: images/section_1_register_table.jpg

* Subregisters are still part of the bigger "parent" register
* Unless special instructions (not yet mentioned) are used, will NOT modify data in the other portions of the register.

----

Memory/Register Access - mov
============================

* When accessing memory, amount of data to copy can be specified

.. code:: nasm

	mov al, byte [rsi] ; copy a single byte
	mov eax, dword [rcx] ; copy a dword (4 bytes)
	mov rax, qword [rsi] ; copy a qword (8 bytes)

* Also, data can be copied from subregister to subregister

.. code:: nasm

	mov al, cl  ; copy from cl to al
	xchg al, ah ; exchange the low and high bytes in ax

----

Register Access - movzx
=======================

Description
-----------

Move with zero extend. When moving data that is smaller than the destination size,
zero out the remaining bits.

Basic Use
---------

.. code:: nasm

	movzx rax, cl ; everything above al is now set to 0
	movzx rax, byte [rsi + 5]

----

Lab 2
=====

Using subregisters, accessing smaller values, and zero extending.

----

Structures
==========

* NASM provides a concept of a "struct" for convenience
* More of a macro than a traditional data structure
* Very useful for keeping track of local variables or parameters (among other things)

----

Structures
==========

.. code:: nasm

	struc MyStruct
		.field1		resd 1	; field1's size is 1 dword
		.field2		resd 1  ; field2's size is 1 dword
		.field3		resq 1	; field3's size is 1 qword
	endstruc

	; ...
	mov rax, [rdi + MyStruct.field3] ; This will be equivalent to: mov rax, [rdi+8]
