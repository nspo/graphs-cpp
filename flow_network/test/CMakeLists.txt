set(BINARY flow_network_gtest)

add_executable(${BINARY} test_flow_edge.cpp test_flow_network_adj_list.cpp)

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC gtest gtest_main)
