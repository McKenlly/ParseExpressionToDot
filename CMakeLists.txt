cmake_minimum_required(VERSION 3.8)
project(ParseExpressionToDot)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES parser.cpp TreeExpresssion.cpp TreeExpresssion.h)
add_executable(ParseExpressionToDot ${SOURCE_FILES})