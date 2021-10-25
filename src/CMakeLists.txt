cmake_minimum_required(VERSION 3.20)
project(Elements_src)

set(CMAKE_CXX_STANDARD 23)

include_directories(${CMAKE_PROJECT_INCLUDE})

add_library(Elements_lib SHARED basics/Vec.hpp basics/StaticMem.hpp basics/DynamicMem.hpp)
set_target_properties(Elements_lib PROPERTIES LINKER_LANGUAGE CXX)
add_executable(Elements_src main.cpp)
target_link_libraries(Elements_src Elements_lib)