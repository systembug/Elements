cmake_minimum_required(VERSION 3.20)
project(Elements_tests)

set(CMAKE_CXX_STANDARD 23)
set(SIMD_FLAGS "-mavx2")

include_directories(${PROJECT_SOURCE_DIR}/../Elements)
include_directories(${PROJECT_SOURCE_DIR}/3rdparty/googletest/googletest/include)

# set(Highway ${PROJECT_SOURCE_DIR}/../3rdparty/hwy/libs/libhwy.a)

add_executable(Elements_tests main.cpp test.cpp)
target_link_libraries(Elements_tests Elements_lib ${Highway} gtest hwy)
target_compile_options(Elements_tests PRIVATE ${SIMD_FLAGS})