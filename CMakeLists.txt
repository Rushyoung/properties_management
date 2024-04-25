cmake_minimum_required(VERSION 3.27)
project(property)

set(CMAKE_C_STANDARD 11)
find_package (PkgConfig REQUIRED)
pkg_check_modules (GTK2 REQUIRED gtk+-2.0)

include_directories (${GTK2_INCLUDE_DIRS})
link_directories (${GTK2_LIBRARY_DIRS})
add_executable(property #[[WIN32]] main.c
        include/base_type.h
        src/base_type.c
        src/database.c
        src/admin_ui.c
        src/login_ui.c
        src/ui_functions.c
        src/query.c
        src/auth.c
        include/auth.h
        src/residient_ui.c
        src/worker_ui.c
)
add_definitions (${GTK2_CFLAGS_OTHER})
target_link_libraries (property ${GTK2_LIBRARIES})
