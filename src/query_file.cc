#include "src/query_file.h"
#include <string>
#include "src/callback.h"

               std::function<bool(const std::wstring&, WIN32_FIND_DATA,
                                  void*)>  // 不要用 void*，用 struct
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
      QueryFile(wstrFileName, retValue, file_callback);
    } else {
      file_count++;
      auto ret = file_callback(wstrFileName, hFind, findData, retValue);
      if (ret == false) break;
    }
  } while (FindNextFile(hFind, &findData) != 0);
  
  
  FindClose(hFind);
  return true;
}