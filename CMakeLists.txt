cmake_minimum_required(VERSION 3.10)
project(LLMpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.)

add_library(llmpp
    cpuinfo.cpp
    memoryarena.cpp
    tensor.cpp
)

add_executable(test_llmpp test.cpp)
target_link_libraries(test_llmpp llmpp)