#include "src/query_file.h"
#include <stack>
#include <string>
#include "src/callback.h"

bool QueryFile(const std::wstring& wstrDir, directory_options options,
               DirectoryData* dirdata,
               std::function<bool(const std::wstring&, const WIN32_FIND_DATA&,
                                  DirectoryData*)>
                   FileCallback) {
  WIN32_FIND_DATA ffd;
  std::stack<std::wstring> directories;

  directories.push(wstrDir);

  while (!directories.empty()) {
    std::wstring path = directories.top();
    std::wstring temp_path = path + (L"\\*");
    directories.pop();

    HANDLE hFind = FindFirstFile(temp_path.c_str(), &ffd);

    if (hFind == INVALID_HANDLE_VALUE) return false;
    if (ffd.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)
      continue;  // 是否是 symbolic link

    do {
      if (wcscmp(ffd.cFileName, L".") == 0 || wcscmp(ffd.cFileName, L"..") == 0)
        continue;
      if (ffd.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) continue;

      if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY &&
          options == directory_options::recursive_directory) {  // 是否是目錄
        directories.push(path + L"\\" + ffd.cFileName);
      } else {
        std::wstring filename = path + L"\\" + ffd.cFileName;
        if (!FileCallback(filename, ffd, dirdata))
          return true;  // 超過 file count  // return true or false?
      }
    } while (FindNextFile(hFind, &ffd) != 0);

    if (GetLastError() != NO_ERROR &&
        GetLastError() !=
            ERROR_NO_MORE_FILES) {  // function fails because no more
                                    // matching files can be found
      FindClose(hFind);
      return false;
    }

    FindClose(hFind);
    hFind = INVALID_HANDLE_VALUE;
  }
  return true;
}

