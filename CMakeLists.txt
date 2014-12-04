cmake_minimum_required(VERSION 2.8.4)
project(native_zxing)

#include_directories("${CMAKE_SOURCE_DIR}/cimg-lib")
include_directories("/opt/X11/include")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(native_zxing ${SOURCE_FILES})