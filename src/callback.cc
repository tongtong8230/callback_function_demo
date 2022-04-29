#include "src/callback.h"

bool LogFile(const std::wstring& wstrDir, int count) {
  std::wcout << wstrDir << std::endl;
  return true;
}
