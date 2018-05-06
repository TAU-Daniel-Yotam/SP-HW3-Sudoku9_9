cmake_minimum_required(VERSION 3.10)
project(HW3 C)

set(CMAKE_C_STANDARD 90)
set(GCC_COVERAGE_COMPILE_FLAGS "-c -fmessage-length=0 –ansi -Wall -Wextra -Werror -pedantic-errors")

add_executable(HW3 main.c main.c Game.c Solver.c Solver.h Game.h Parser.c Parser.h MainAux.c MainAux.h)