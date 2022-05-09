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
  HANDLE hFind = FindFirstFile(wstrTempDir.c_str(), &ffd);
  if (hFind == INVALID_HANDLE_VALUE) return false;
  do {
      if (wcscmp(ffd.cFileName, L".") == 0 || wcscmp(ffd.cFileName, L"..") == 0)

    std::wstring wstrFileName = wstrDir + (L"\\") + findData.cFileName;

    if (file_count > FILE_MAX_LIMIT) break;
    if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {  // 是否是目錄
      wstrFileName.append(L"\\");
      QueryFile(wstrFileName, retValue, file_callback);
    } else {
      file_count++;
      auto ret = file_callback(wstrFileName, hFind, findData, retValue);
      if (ret == false) break;
    }
    } while (FindNextFile(hFind, &ffd) != 0);
  
  FindClose(hFind);
  return true;
}