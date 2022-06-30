/* date = June 30th 2022 0:57 pm */

#ifndef SYSTEM_H
#define SYSTEM_H

#include "patterns.h"

PatternBounds GetLibraryBounds(const char* libName);
void OSSleep(long int ms);
int LibraryExists(const char* libName);
int GetRelativeDirectory(const char* folderName, char* buffer, int size);


typedef void(__fastcall* TFileFoundCallback)(const char* fullPath);
int EnumerateFilesInDirectory(const char* directory, const char* filter, TFileFoundCallback enumCallback);
const char* GetSystemLibraryExtension();
void* GetExport(const char* library, const char* function);

#endif //SYSTEM_H
