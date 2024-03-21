cmake_minimum_required(VERSION 3.27)
project(Lab3___Assignment1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab3___Assignment1
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h
        Stack.cpp
        Stack.h
        Stack.cpp)
