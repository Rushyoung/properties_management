cmake_minimum_required(VERSION 3.27)
project(Property)

set(CMAKE_C_STANDARD 11)

#set include directory
include_directories(include)

#set source directory
file(GLOB SOURCES "src/*.c")

#set(PKG_CONFIG_EXECUTABLE "D:/gtk/bin/pkg-config.exe")
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK2 REQUIRED gtk+-2.0)

include_directories(${GTK2_INCLUDE_DIRS})
link_directories(${GTK2_LIBRARY_DIRS})
add_definitions(${GTK2_CFLAGS_OTHER})

#add executable with sources and main.c file
add_executable(Property ${SOURCES} main.c)

target_link_libraries(Property ${GTK2_LIBRARIES})