:title: Introduction to Assembly
:data-transition-duration: 1500
:css: asm.css

An introduction to x86

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

========  ========  ========  ======
64 bit,   32 bit,   16 bit,   8 bit
========  ========  ========  ======
rax       eax       ax        ah/al
rcx       ecx       cx        ch/cl
rbx       ebx       bx        bh/bl
rdx       edx       dx        dh/dl
rdi       edi       N/A       N/A
rsi       esi       N/A       N/A
========  ========  ========  ======

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

:data-rotate-y: 180

Lab 1
=====

Using mov, lea, and xchg

----

Debugging
=========
