#!/bin/bash

nasm -f elf64 -g write.nasm
gcc -g main.c write.o -o write_stuff
