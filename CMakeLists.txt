cmake_minimum_required(VERSION 3.25)
project(Calculator)

set(CMAKE_CXX_STANDARD 17)

add_executable(Calculator main.cpp
        stack/stack.cpp
        stack/stack.h ExpressionCalculator.cpp ExpressionCalculator.h)
