cmake_minimum_required(VERSION 3.10)
project(LLMpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_library(llmpp
    src/cpuinfo.cpp
    src/memoryarena.cpp
    src/tensor.cpp
)

# Tests
enable_testing()
add_subdirectory(tests)

# Examples
add_subdirectory(examples)