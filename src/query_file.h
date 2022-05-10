#ifndef QUERY_FILE_H_
#define QUERY_FILE_H_
#include <windows.h>
#include <functional>
#include <iostream>

typedef struct _DirectoryData {
  unsigned long long file_count = 0;
  unsigned long long file_total_size = 0;
} DirectoryData;

enum class directory_options {
  none = 0,
  recursive_directory = 1,
  // skip_permission_denied = 2
};

/**
 * @brief
 *
 * @param wstrDir the path to query files
 * @param dirdata a return value
 * @param FileCallback a callback which will implement on these files
 * @return true
 */
bool QueryFile(const std::wstring& wstrDir, directory_options options,
               DirectoryData* dirdata,
               std::function<bool(const std::wstring&, const WIN32_FIND_DATA&,
                                  DirectoryData*)>
                   FileCallback);

#endif  // QUERY_FILE_H_