cmake_minimum_required(VERSION 3.10)
project(graphs_cpp)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
add_compile_options(/W4)
else()
add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(include)

add_executable(graphs_demo graphs_main.cpp)
add_executable(digraphs_demo digraphs_main.cpp)

add_subdirectory(submodules/googletest)
add_subdirectory(test)