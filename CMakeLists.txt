cmake_minimum_required(VERSION 3.17)
project(graphs_cpp)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
add_compile_options(/W4)
else()
add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_executable(graphs_test main.cpp)