#include "src/callback.h"

bool CountFile(const std::wstring& wstrDir,
               WIN32_FIND_DATA findData, void* fileCountPtr) {
  int* fileCountIntPtr = (int*)fileCountPtr;
  (*fileCountIntPtr)++;
  return true;
}
