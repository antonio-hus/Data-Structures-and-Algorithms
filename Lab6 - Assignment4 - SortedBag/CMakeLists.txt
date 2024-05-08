cmake_minimum_required(VERSION 3.27)
project(Lab6___Assignment4___SortedBag)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        Lab6___Assignment4___SortedBag
        main.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h
        SortedBag.cpp
        SortedBag.h
        SortedBagIterator.cpp
        SortedBagIterator.h
)
