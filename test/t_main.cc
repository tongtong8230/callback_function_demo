#include <iostream>
#include "gtest/gtest.h"
#include "src/callback.h"
#include "src/query_file.h"

TEST(Callback, CountFile) {
  DirectoryData dir_data;
  DirectoryData* dir_ptr = &dir_data;
  auto ret =
      QueryFile(L"C:\\Users\\kikihuang", directory_options::none,
                dir_ptr, CountFile);
  std::cout << "File Count: " << dir_ptr->file_count << std::endl;
  ASSERT_EQ(ret, true);
}

TEST(Callback, GetFileSize) {
  DirectoryData dir_data;
  DirectoryData* dir_ptr = &dir_data;
  auto lambda = [](const std::wstring& wstrDir, const WIN32_FIND_DATA& ffd,
                   DirectoryData* dir_ptr) -> bool {
    const unsigned long long FILE_MAX_LIMIT = 500000;
    if (dir_ptr->file_count > FILE_MAX_LIMIT) return false;

    unsigned long long dwSize =
        (ffd.nFileSizeHigh * (MAXDWORD + 1)) + ffd.nFileSizeLow;
    dir_ptr->file_total_size += dwSize;
    return true;
  };

  auto ret = QueryFile(L"C:\\Users\\kikihuang\\Documents",
                       directory_options::recursive_directory, dir_ptr, lambda);
  std::cout << "All Directory Size: " << dir_ptr->file_total_size << std::endl;
  ASSERT_EQ(ret, true);
}
