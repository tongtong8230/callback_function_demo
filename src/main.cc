#include <windows.h>
#include <functional>
#include <iostream>
#include <string>
#include "callback.h"

bool QueryFile(const std::wstring& wstrDir,
               bool (*file_callback)(const std::wstring&, int)) {
  if (wstrDir.empty()) {
    return false;
  }
  HANDLE hFind;
  WIN32_FIND_DATA findData;
  std::wstring wstrTempDir = wstrDir + (L"\\*");
  hFind = FindFirstFile(wstrTempDir.c_str(), &findData);
  if (hFind == INVALID_HANDLE_VALUE) {
    return false;
  }
  do {
    if (wcscmp(findData.cFileName, L".") == 0 ||
        wcscmp(findData.cFileName, L"..") == 0) {
      continue;
    }

    std::wstring wstrFileName;
    wstrFileName.assign(wstrDir);
    wstrFileName.append(L"\\");
    wstrFileName.append(findData.cFileName);

    int file_count = 0;
    const int FILE_MAX_LIMIT = 500000;

    if (file_count > FILE_MAX_LIMIT) break;
    if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {  // 是否是目錄
      wstrFileName.append(L"\\");
      QueryFile(wstrFileName, file_callback);
    } else {
      file_count++;
      auto ret = file_callback(wstrFileName, file_count);
      if (ret == false) break;
    }
  } while (FindNextFile(hFind, &findData) != 0);

  FindClose(hFind);
  return true;
}

int main() {
  setlocale(LC_ALL, setlocale(LC_CTYPE, ""));

  QueryFile(L"C:\\Users\\kikihuang\\Documents", LogFile);

  return 0;
}