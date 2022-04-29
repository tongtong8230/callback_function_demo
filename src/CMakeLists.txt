include_directories("${PROJECT_SOURCE_DIR}/src")

# add the executable
add_executable(main main.cc callback.cc)
# target_link_libraries(main )
target_compile_options(main PRIVATE -D_UNICODE)