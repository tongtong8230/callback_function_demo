include_directories(${PROJECT_SOURCE_DIR})
include_directories(${SRC_DIR})

# add the executable
add_executable(main main.cc callback.cc query_file.cc)
# target_link_libraries(main )
target_compile_options(main PRIVATE -D_UNICODE)