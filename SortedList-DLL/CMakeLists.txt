cmake_minimum_required(VERSION 3.17)
project(lab2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab2
        App.cpp
        tests/ExtendedTest.cpp
        tests/ExtendedTest.h
        ListIterator.cpp
        ListIterator.h
        tests/ShortTest.cpp
        tests/ShortTest.h
        SortedIndexedList.h
        SortedIndexeList.cpp)
