#include <windows.h>
#include <functional>
#include <iostream>
#include <string>

bool LogFile(const std::wstring& wstrDir, int count) {
  std::wcout << wstrDir << std::endl;
  return true;
}

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
    int count = 0;
    if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {  // 是否是目錄
      wstrFileName.append(L"\\");
      QueryFile(wstrFileName, file_callback);
    } else {
      count++;
      auto ret = file_callback(wstrFileName, count);
      if (ret == false) break;
    }
  } while (FindNextFile(hFind, &findData) != 0);

  FindClose(hFind);
  return true;
}

int main() {
  setlocale(LC_ALL, setlocale(LC_CTYPE, ""));
  try {
    QueryFile(L"C:\\Users\\kikihuang\\Documents", LogFile);
  } catch (const std::exception& e) {
    std::cerr << e.what();
  }
  return 0;
}
