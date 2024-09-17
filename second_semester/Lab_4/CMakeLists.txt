cmake_minimum_required(VERSION 3.26)
project(Lab_4 C)

set(CMAKE_C_STANDARD 11)

add_executable(Lab_4 print.c
        lib/matrix.c
        lib/coord.c
        lib/display.c
        app.c
        lib/characteristic.c)

add_executable(app app.c
        lib/matrix.c
        lib/coord.c
        lib/display.c
        lib/characteristic.c)