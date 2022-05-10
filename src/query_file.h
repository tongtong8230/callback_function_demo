#ifndef QUERY_FILE_H_
#define QUERY_FILE_H_
#include <windows.h>
#include <functional>
#include <iostream>
// #include <stack>

bool QueryFile(const std::wstring& wstrDir, std::vector<std::wstring>& files,
               DIRECTORYDATA* dirdata,
               std::function<bool(const std::wstring&, const WIN32_FIND_DATA&,
                                  DIRECTORYDATA*)>
                   FileCallback);

struct DIRECTORYDATA {
  unsigned long long file_count;
  unsigned long long file_total_size;
};

#endif  // QUERY_FILE_H_