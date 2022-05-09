#include "src/query_file.h"
#include <string>
#include "src/callback.h"

// 只要 queryfile 就好，其他事在 callback 裡面做
bool QueryFile(const std::wstring& wstrDir, std::vector<std::wstring>& files,
               void* retValue,  // 不要用 void*，用 struct
               std::function<bool(const std::wstring&, WIN32_FIND_DATA, void*)>
                   file_callback) {
  WIN32_FIND_DATA ffd;
  std::stack<std::wstring> directories;

  directories.push(wstrDir);
  files.clear();

  while (!directories.empty()) {
    std::wstring wstrPath = directories.top();
    std::wstring wstrTempDir = wstrPath + (L"\\*");
    directories.pop();

    HANDLE hFind = FindFirstFile(wstrTempDir.c_str(), &ffd);

    if (hFind == INVALID_HANDLE_VALUE) continue;

    do {
      if (wcscmp(ffd.cFileName, L".") == 0 || wcscmp(ffd.cFileName, L"..") == 0)
        continue;

      if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {  // 是否是目錄
        directories.push(wstrDir + L"\\" + ffd.cFileName);
      } else {
        files.push_back(wstrDir + L"\\" + ffd.cFileName);
      }
    } while (FindNextFile(hFind, &ffd) != 0);

    if (GetLastError() != ERROR_NO_MORE_FILES) { // function fails because no more matching files can be found
      FindClose(hFind);
      return false;
    }

    FindClose(hFind);
    hFind = INVALID_HANDLE_VALUE;
  }
  return true;
}