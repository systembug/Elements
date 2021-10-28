cmake_minimum_required(VERSION 3.20)
project(Elements_src)

set(CMAKE_CXX_STANDARD 23)
set(SIMD_FLAGS "-mavx2")

include_directories(${PROJECT_SOURCE_DIR})

# set(Highway ${PROJECT_SOURCE_DIR}/../3rdparty/hwy/libs/libhwy.a)
set(SRC_FILES basics/Vec.hpp basics/StaticMem.hpp basics/DynamicMem.hpp basics/DynamicMemAlloc.hpp basics/VecImpl.hpp)

add_library(Elements_lib SHARED ${SRC_FILES})
set_target_properties(Elements_lib PROPERTIES LINKER_LANGUAGE CXX)
target_compile_options(Elements_lib PRIVATE ${SIMD_FLAGS})
target_link_libraries(Elements_lib hwy)

add_executable(Elements_src main.cpp)
target_link_libraries(Elements_src Elements_lib)
# target_compile_options(Elements_src PRIVATE ${HWY_FLAGS})
# target_link_libraries(Elements_src hwy)