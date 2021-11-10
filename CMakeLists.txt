cmake_minimum_required(VERSION 3.20)
project(Elements)

set(CMAKE_CXX_STANDARD 23)
set(HWY_EXAMPLES_TESTS_INSTALL false)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/3rdparty)

# 3rdparty
add_subdirectory(3rdparty/highway)

# Main
add_subdirectory(src)

# Test
add_subdirectory(3rdparty/googletest)
add_subdirectory(tests)
# add_subdirectory(3rdparty/googletest)