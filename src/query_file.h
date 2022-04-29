#ifndef QUERY_FILE_H_
#define QUERY_FILE_H_
#include <iostream>
#include <functional>

bool QueryFile(const std::wstring& wstrDir,
               bool (*file_callback)(const std::wstring&, int));
#endif  // QUERY_FILE_H_