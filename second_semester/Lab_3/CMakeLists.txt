cmake_minimum_required(VERSION 3.26)
project(Lab_3 C)

set(CMAKE_C_STANDARD 11)

add_executable(Lab_3 print.c
        lib/matrix.c
        lib/coord.c
        lib/display.c
        app.c)

add_executable(app app.c
        lib/matrix.c
        lib/coord.c
        lib/display.c)