cmake_minimum_required(VERSION 3.17)
project(leetcode_cpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(leetcode_cpp main.cpp util.h util.cpp solutions/CommonSolution.h structures/List.cpp structures/List.h solutions/ArraySolution.h)