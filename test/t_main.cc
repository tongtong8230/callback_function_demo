#include <iostream>
#include "gtest/gtest.h"
#include "src/callback.h"

TEST(Callback, LogFile) {
  auto ret = QueryFile(L"C:\\Users\\kikihuang\\Documents", LogFile);
  ASSERT_EQ(ret, true);
}
