cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

# set the project name
project(FileQuery)

include_directories(PROJECT_SOURCE_DIR)

set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd")


# add the executable
add_executable(main main.cc)
target_link_libraries(main)
target_compile_options(main PRIVATE -D_UNICODE)
