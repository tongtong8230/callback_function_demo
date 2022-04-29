#include <iostream>
#include "gtest/gtest.h"
#include "src/callback.h"

TEST(Callback, LogFile) {
  int count = 0;
  int* countPtr = &count;
  auto ret = QueryFile(L"C:\\Users\\kikihuang\\Desktop", countPtr, CountFile);
  std::cout << "File Count: " << count << std::endl;
  ASSERT_EQ(ret, true);
}

  ASSERT_EQ(ret, true);
}
