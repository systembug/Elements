cmake_minimum_required(VERSION 3.20)
project(Elements)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(3rdparty/googletest)
