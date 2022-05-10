#include "src/query_file.h"
#include <stack>
#include <string>
#include "src/callback.h"

// 只要 queryfile 就好，其他事在 callback 裡面做
bool QueryFile(const std::wstring& wstrDir, std::vector<std::wstring>& files,
               DIRECTORYDATA* dirdata,
               std::function<bool(const std::wstring&, const WIN32_FIND_DATA&,
                                  DIRECTORYDATA*)>
                   FileCallback) {
  WIN32_FIND_DATA ffd;
  std::stack<std::wstring> directories;

  directories.push(wstrDir);
  files.clear();

  while (!directories.empty()) {
    std::wstring path = directories.top();
    std::wstring temp_path = path + (L"\\*");
    directories.pop();

    HANDLE hFind = FindFirstFile(temp_path.c_str(), &ffd);

    if (hFind == INVALID_HANDLE_VALUE) continue;

    do {
      if (wcscmp(ffd.cFileName, L".") == 0 || wcscmp(ffd.cFileName, L"..") == 0)
        continue;

      if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {  // 是否是目錄
        directories.push(path + L"\\" + ffd.cFileName);
      } else {
        std::wstring filename = path + L"\\" + ffd.cFileName;
        // files.push_back(filename);
        FileCallback(filename, ffd, dirdata);
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