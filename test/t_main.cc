#include <iostream>
#include "gtest/gtest.h"
#include "src/callback.h"
#include "src/query_file.h"

TEST(Callback, LogFile) {
  int count = 0;
  int* countPtr = &count;
  auto ret = QueryFile(L"C:\\Users\\kikihuang\\Desktop", countPtr, CountFile);
  std::cout << "File Count: " << count << std::endl;
  ASSERT_EQ(ret, true);
}

TEST(Callback, GetFileSize) {
  unsigned long long size = 0;
  unsigned long long* sizePtr = &size;
  auto lambda = [](const std::wstring& wstrDir,
                   WIN32_FIND_DATA findData, void* sizePtr) -> bool {
    unsigned long long* sizeULLPtr = (unsigned long long*)sizePtr;
    unsigned long long dwSize =
        (findData.nFileSizeHigh * (MAXDWORD + 1)) + findData.nFileSizeLow;
    *sizeULLPtr += dwSize;
    return true;
  };

  auto ret = QueryFile(L"C:\\Users\\kikihuang\\Documents", sizePtr, lambda);
  std::cout << "All Directory Size: " << *sizePtr << std::endl;
  ASSERT_EQ(ret, true);
}
