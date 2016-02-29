:title: Introduction to Assembly
:data-transition-duration: 1500
:css: asm.css

An introduction to x86

----

:class: split-table

FLAGS
=====

* A register that contains a variety of bits representing state and status information
* Varies in size, but many portions (in newer processors) aren't used

+--------+-----------+
| FLAGS  |  16 bits  |
+--------+-----------+
| EFLAGS |  32 bits  |
+--------+-----------+
| RFLAGS |  64 bits  |
+--------+-----------+

----

Flag Layout
===========