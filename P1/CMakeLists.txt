cmake_minimum_required(VERSION 3.26)
project(P1 C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Werror -pedantic)
set(CMAKE_VERBOSE_MAKEFILE ON)


add_executable(P1 main.c
        IntSet.c
        IntSet.h
        LinkedList.c
        LinkedList.h
        dfa.c
        dfa.h
        nfa.c
        nfa.h
        nfa_to_dfa.c
        nfa_to_dfa.h)
