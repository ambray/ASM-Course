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

	mov eax, 10
	mov ecx, 10
	mul ecx 	; rax now contains 100

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

Description
-----------

As with mul, div takes a single argument, and divides the value stored in the dividend register(s) by it. This is typically ax/eax/rax (and the \*dx equivalents), but may vary a bit depending on the size (chart provided on the next slide).

Basic Use
---------

.. code:: nasm

	; clearing the high bits, we're only using what's in rax!
	mov rdx, 0 ; there's a better way to do this, but we haven't learned it yet!
	mov rax, 2
	mov rcx, 10
	div rcx    ; rax now contains 5

----

div: operation results
======================

Where to retrieve the results of a div from depends on the size of the arguments. The table below illustrates this relationship:

.. image:: images/section_2_div_table.jpg


----


inc and dec
===========

Description
-----------

Adds or subtracts one from the provided register, storing the result in place.

Basic Use
---------

.. code:: nasm

	mov rax, 1 	; rax now contains 1
	inc rax		; rax now contains 2
	inc rax		; rax now contains 3
	dec rax		; rax now contains 2

----


Lab 3
=====

Arithmetic Operations

----

The Stack
=========

* Grows from high memory to low memory
* Current function typically exists within a stack "frame" (but not always!)

----

Stack Frames
============

* RSP (or ESP) points to the top of the stack
* RBP (or EBP) points to the "base" of the stack frame

----

Stack Frame Layout
==================

.. image:: images/section_2_stack_diagram_1.jpg

----

Expanding the Stack Frame
=========================

* Can modify the value of RSP directly to allocate more stack space:

.. code:: nasm

	sub rsp, 16

* But you must always ensure you clean up before the function returns:

.. code:: nasm

	add rsp, 16

----

Stack Alignment
===============

* x86_64 expects 16 byte stack alignment
* Allocating odd amounts of space can cause things to break
* ALWAYS make sure you clean up your stack before returning

----

New Instructions: push and pop
==============================

Description
-----------

Push will subtract a pointer-width amount of space from RSP, and place the argument in the newly-allocated location.
Pop performs the opposite action, storing the value just below RSP in the register provided, and adding a pointer-width amount to RSP.
For every push, you will need to pop!

Basic Use
---------

.. code:: nasm

	mov rax, 1		; 1 is now stored in rax.
	push rax		; 1 is now stored at the top of the stack
	pop rcx			; rcx now contains 1

----

Growing the Stack
=================

After a push operation:

.. image:: images/section_2_stack_diagram_2.jpg

----

Restoring the Stack
===================

After a pop operation:

.. image:: images/section_2_stack_diagram_3.jpg

----

Lab 4
=====

Stack Operations

----

Negative Numbers
================

* Negative numbers on the x86(_64) platform are represented via Two's Complement

----

Two's Complement
================
