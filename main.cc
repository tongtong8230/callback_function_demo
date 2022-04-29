#include <windows.h>
#include <functional>
#include <iostream>

bool QueryFile(std::wstring wstrDir,
               std::function<bool(std::wstring, int)> file_callback) {
  int count = 0;
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

    auto ret = file_callback(wstrFileName.c_str(), 15);
    if (ret == false) continue;

    if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {  // 是否是目錄
      QueryFile(wstrFileName.c_str(), file_callback);
    }
  } while (FindNextFile(hFind, &findData) != 0);

  FindClose(hFind);
  return true;
}

// bool queryfile(function<bool(std::string, std::string, int)> log_func) {
//   //模擬 file query.
//   for (auto i = 0; i < 20; i++) {
//     std::string path = "C:\\123123123.exe";
//     std::string path2 = "D:\\aaaaa.exe";
//     int ret = log_func(path, path2, i);
//     if (ret == false)  //可能有些地方需要跳開
//       break;
//   }

//   return true;
// }

// //callback + lambda()
//   queryfile([](std::string path , std::string path2 , int count){

//     //一些處理
//     std::cout << "path:" << path << std::endl;
//     std::cout << "path2:" << path2 << std::endl;
//     std::cout << "count:" << count << std::endl;
//     if (count > 8) // 跳掉判斷...
//     {
//       return false;
//     }

//     return true;
//   });

int main() { return 0; }