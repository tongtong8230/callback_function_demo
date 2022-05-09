#ifndef QUERY_FILE_H_
#define QUERY_FILE_H_
#include <windows.h>
#include <functional>
#include <iostream>

bool QueryFile(
    const std::wstring& wstrDir, void* retValue,
    std::function<bool(const std::wstring&, WIN32_FIND_DATA, void*)>
        file_callback);
#endif  // QUERY_FILE_H_