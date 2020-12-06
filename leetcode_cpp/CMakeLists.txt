cmake_minimum_required(VERSION 3.17)
project(leetcode_cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

add_executable(leetcode_cpp main.cpp util.h solutions/CommonSolution.h structures/List.cpp structures/List.h solutions/ArraySolution.h structures/SparseVector.h)