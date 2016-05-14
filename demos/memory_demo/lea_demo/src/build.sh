#!/bin/bash

nasm -f elf64 -g leadm.nasm
gcc -g main.c leadm.o -o run_demo
