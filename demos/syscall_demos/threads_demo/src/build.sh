#!/bin/bash

nasm -f elf64 -g threads.nasm
gcc -g main.c threads.o -o threads_demo
