cmake_minimum_required(VERSION 3.5.1)
project(hello_test)


set (CMAKE_CXX_STANDARD 11)
#set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

set (SRC ./src/ArithmaticExpression.cpp ./src/Evaluation.cpp ./src/main.cpp)
include_directories (./include)

add_executable (hello ${SRC})
