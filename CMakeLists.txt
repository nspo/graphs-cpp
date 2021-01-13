cmake_minimum_required(VERSION 3.10)
project(graphs_cpp)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
add_compile_options(/W4)
else()
add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_subdirectory(submodules/googletest)

add_subdirectory(general)
include_directories(general/include)

add_subdirectory(unweighted_graph)
add_subdirectory(unweighted_digraph)
add_subdirectory(weighted_graph)
add_subdirectory(weighted_digraph)