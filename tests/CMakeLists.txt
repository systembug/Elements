cmake_minimum_required(VERSION 3.20)
project(Elements_tests)

set(CMAKE_CXX_STANDARD 23)

include_directories(${PROJECT_SOURCE_DIR}/../Elements)
include_directories(${PROJECT_SOURCE_DIR}/3rdparty/googletest/googletest/include)

message(STATUS ${PROJECT_SOURCE_DIR})
message(STATUS ${CMAKE_PROJECT_INCLUDE})

add_executable(Elements_tests main.cpp test.cpp)
target_link_libraries(Elements_tests Elements_lib gtest)