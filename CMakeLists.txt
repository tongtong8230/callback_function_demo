cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

# set the project name
project(FileQuery)

include_directories(${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd")

add_subdirectory(src)
add_subdirectory(test)