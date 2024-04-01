cmake_minimum_required(VERSION 3.27)
project(property)

set(CMAKE_C_STANDARD 11)

add_executable(property main.c
        include/base_type.h
        src/base_type.c)
