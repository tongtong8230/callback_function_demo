#ifndef _CALLBACK_H_
#define _CALLBACK_H_
#include <windows.h>
#include <iostream>
#include <string>
#include "src/query_file.h"

bool CountFile(const std::wstring& wstrDir, const WIN32_FIND_DATA& ffd,
               DirectoryData* dir_ptr);

#endif  // _CALLBACK_H_