cmake_minimum_required(VERSION 3.26)
project(Calculator)

set(CMAKE_CXX_STANDARD 17)

add_executable(Calculator main.cpp
        stack/stack.cpp
        determine/checking.cpp
        determine/checking.h
        determine/result_generate.cpp
        determine/result_generate.h
        determine/writing_to_stack.cpp
        determine/writing_to_stack.h
        stack/stack.cpp
        stack/stack.h)
