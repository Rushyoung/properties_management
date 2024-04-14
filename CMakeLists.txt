cmake_minimum_required(VERSION 3.27)
project(test)

set(CMAKE_C_STANDARD 11)

find_package (PkgConfig REQUIRED)
pkg_check_modules (GTK2 REQUIRED gtk+-2.0)

include_directories (${GTK2_INCLUDE_DIRS})
link_directories (${GTK2_LIBRARY_DIRS})
add_executable(test test.c)
add_definitions (${GTK2_CFLAGS_OTHER})
target_link_libraries (test ${GTK2_LIBRARIES})
