set(BINARY general_gtest)

add_executable(${BINARY} test_disjoint_sets.cpp test_priority_queue.cpp)

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC gtest gtest_main)
