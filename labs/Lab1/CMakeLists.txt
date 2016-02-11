cmake_minimum_required(VERSION 3.3)
project(Lab1 C CXX)

enable_language(ASM_NASM)

file(GLOB LAB_ASM_FILES "*.nasm")
file(GLOB LAB_CPP_FILES "*.cpp")

add_executable(Lab1 ${LAB_ASM_FILES} ${LAB_CPP_FILES})
