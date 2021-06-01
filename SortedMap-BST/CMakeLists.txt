cmake_minimum_required(VERSION 3.19)
project(lab5)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(tests)

add_executable(lab5
        tests/ExtendedTest.cpp
        tests/ExtendedTest.h
        tests/ShortTest.cpp
        tests/ShortTest.h
        App.cpp
        SMIterator.cpp
        SMIterator.h
        SortedMap.cpp
        SortedMap.h)
