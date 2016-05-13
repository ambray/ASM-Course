#!/bin/bash

nasm -f elf64 -g movin.nasm
gcc -g main.c movin.o -o run_me
