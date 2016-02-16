:title: Introduction to Assembly
:data-transition-duration: 1500
:css: asm.css

An introduction to x86

----

Arithmetic Operations
=====================

Basic Math Operations

----

The add and sub instructions
============================

Description
-----------

Adds and subtracts arbitrary values. The destination (where the result is stored) is the first value provided.

Basic Use
---------

Using an immediate, we can just add a number to a value in a register:

.. code:: nasm

	mov rax, 1
	add rax, 2 ; rax now contains 3
	sub rax, 1 ; rax now contains 2

We can also add the values stored in two registers together:

.. code:: nasm

	mov rax, 1
	mov rcx, 2
	add rax, rcx ; as above, rax now contains 3
	sub rax, rcx ; rax is now back to 1

----

The mul instruction
============================

Description
-----------

Allow multiplication of arbitrary values. Takes a single argument, multiplies by rax/eax/ax (depending on operand size).

Basic Use
---------

.. code:: nasm

	mov rax, 10
	mul 10 		; rax now contains 100

	mov rax, 5
	mov rcx, 7
	mul rcx     ; rax now contains 35

.. note::

	Results are mostly stored in the source operand (ax/eax/rax), but may be stored in dx/edx/rdx as well if overflow occurs. The table on the next slide illustrates this.

----

The mul instruction: storing results
====================================

Results are stored in the source (possible), or in a combination of registers in the configuration below:

.. image:: images/section_2_mul_table.jpg

----

The div instruction
===================
