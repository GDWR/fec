cmake_minimum_required(VERSION 3.24)
project(fec)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SRC_FILES src/*.cpp src/*.hpp)
add_executable(fec ${SRC_FILES})
