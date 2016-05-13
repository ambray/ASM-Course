#!/bin/bash

nasm -g -f elf64 run.nasm
gcc main.c run.o -g -o run_me
