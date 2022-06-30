#include "system.h"

#include <stdint.h>
#include <stdio.h>

#include "logger.h"
#include "patterns.h"

// include system headers
#if defined(_WIN64)
#include <Windows.h>
#include <Psapi.h>
#else
#include <dlfcn.h>
#include <unistd.h>
#endif



void OSSleep(long int ms)
{
#if defined(_WIN64)
    Sleep(ms);
#else
    sleep(ms / 1000);
#endif
}
// get bounds of a loaded library
// pass NULL to get bounds of main assembly
PatternBounds GetLibraryBounds(const char* libName)
{
    PatternBounds result;
    result.first = 0;
    result.last = 0;
    
#if defined(_WIN64)
    MODULEINFO info;
    HMODULE base = GetModuleHandle(libName);
    if(!GetModuleInformation(GetCurrentProcess(), 
                             base,
                             &info,
                             sizeof(MODULEINFO)))
    {
        Println(LT_ERROR, "Failed to get module information during engine bounds calculation.");
        return result;
    }
    result.first = info.lpBaseOfDll;
    result.last = (void*)((uint64_t)base + info.SizeOfImage - 1);
#else
    //TODO: linux implementation
#endif
    return result;
}

int LibraryExists(const char* libName)
{
#if defined(_WIN64)
    return (GetModuleHandleA(libName) != NULL);
#else
    return dlopen(libName, RTLD_LAZY | RTLD_NOLOAD);
#endif
}

// set `buffer` to a relative directory to main app
// if main app in `/bin` and folder is `plugins` then return /bin/plugins
// return TRUE if successfully written to buffer
int GetRelativeDirectory(const char* folderName, char* buffer, int size)
{
    int folderNamelen = strlen(folderName);
#if defined(_WIN64)
    char sDir[MAX_PATH] = { 0 };
    if(!GetCurrentDirectoryA(MAX_PATH, sDir)) {
        Println(LT_ERROR, "Failed to get current working directory.");
        return 0;
    }
    if(strlen(sDir) + folderNamelen + 2 > MAX_PATH) return 0; // strcat would overflow!
    
    strcat(sDir,"\\"); // windows uses backslash
    strcat(sDir, folderName); // C:\ReforgerServer\Plugins
    
    if(size < strlen(sDir)+1) return 0; // not large enough buffer
    
    strcpy(buffer,sDir);
    return 1;
#else
    char sDir[size] = { 0 };
    if(!getcwd(sDir, size)) return 0; // not large enough buffer
    
    if(strlen(sDir) + folderNamelen + 2 > size) return 0; // strcat would overflow!
    
    strcat(sDir, "//");
    strcat(sDir, folderName);
    
    strcpy(buffer, sDir);
    return 1;
#endif
}

// enumerate files in directory matching the given extension filter of format '*.*'
// filter can be NULL to default to '*.*'
// on match, callback is run on the same thread
// returns true on success
int EnumerateFilesInDirectory(const char* directory, const char* filter, TFileFoundCallback enumCallback)
{
    if(filter == 0)
        filter = "*.*";
    
#if defined(_WIN64)
    WIN32_FIND_DATA fdFile;
    HANDLE hFind = NULL;
    
    char sPath[MAX_PATH] = { 0 };
    sprintf(sPath, "%s\\%s", directory, filter);
    // ensure directory exists before we start trying to iterate it!
    if((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
    {
        return 0;
    }
    
    do
    {
        //Find first file will always return "."
        //    and ".." as the first two directories.
        if(strcmp(fdFile.cFileName, ".") != 0 && strcmp(fdFile.cFileName, "..") != 0)
        {
            // set spath to this target file path
            sprintf(sPath, "%s\\%s", directory, fdFile.cFileName);
            
            // run callback if target is actually a file
            if(!(fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                enumCallback(sPath);
            }
        }
    }
    while(FindNextFile(hFind, &fdFile));
    
    FindClose(hFind);
    
    return 1;
#else
    
    return 0;
#endif
}

const char* GetSystemLibraryExtension()
{
#if defined(_WIN64)
    return "*.dll";
#else
    return "*.so";
#endif
}

// get the address of an exported C function
void* GetExport(const char* library, const char* function)
{
#if defined(_WIN64)
    HMODULE hLib = LoadLibraryA(library);
    if(!hLib) return 0;
    return GetProcAddress(hLib, function);
#elif
    void* hLib = dlopen(library, RTLD_NOW | RTLD_NODELETE);
    if(!hLib) return 0;
    return dlsym(hLib, function);
#endif
}