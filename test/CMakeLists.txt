include_directories(${PROJECT_SOURCE_DIR})
include_directories(${TEST_DIR})
include_directories(${SRC_DIR})


# find_package(Threads)
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Setup testing
enable_testing()

# add the executable
add_executable(t_main t_main.cc ${SRC_DIR}/query_file.cc ${SRC_DIR}/callback.cc)
target_link_libraries(t_main gtest gtest_main) #CMAKE_THREAD_LIBS_INIT)
target_compile_options(t_main PRIVATE -D_UNICODE)