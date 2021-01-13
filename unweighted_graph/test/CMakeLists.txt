set(BINARY unweighted_graph_gtest)

add_executable(${BINARY} test_unweighted_graph_basic.cpp)

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC gtest gtest_main)
