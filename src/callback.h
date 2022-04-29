#ifndef _CALLBACK_H_
#define _CALLBACK_H_
#include <windows.h>
#include <iostream>
#include <string>

bool CountFile(const std::wstring& wstrDir, HANDLE hFind,
             WIN32_FIND_DATA findData, void* fileCountPtr);
#endif  // _CALLBACK_H_