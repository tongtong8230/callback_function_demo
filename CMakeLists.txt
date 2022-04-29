cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

# set the project name
project(FileQuery)

include_directories(${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd")

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(TEST_DIR "${PROJECT_SOURCE_DIR}/test")

add_subdirectory(src)
add_subdirectory(test)