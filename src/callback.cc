#include "src/callback.h"

bool CountFile(const std::wstring& wstrDir, WIN32_FIND_DATA ffd,
               DIRECTORYDATA* dir_ptr) {
  const unsigned long long FILE_MAX_LIMIT = 500000;
  if (dir_ptr->file_count > FILE_MAX_LIMIT) return true; // 要 return true or false?
  dir_ptr->file_count++;
  return true;
}
