cmake_minimum_required(VERSION 3.10)

# Tests
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_tensor test_tensor.cpp)
target_link_libraries(test_tensor llmpp ${GTEST_LIBRARIES} pthread)

add_test(NAME TensorTest COMMAND test_tensor)