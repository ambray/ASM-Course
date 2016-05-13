cmake_minimum_required(VERSION 3.2)
project(CRT C CXX ASM)

set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -nostdlib -g")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -g")

enable_language(ASM_NASM)
file(GLOB LAB_ASM_FILES "*.nasm")
file(GLOB LAB_CPP_FILES "*.c")

add_executable(crtproj ${LAB_ASM_FILES} ${LAB_CPP_FILES})
