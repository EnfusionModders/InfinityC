#include "system.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "logger.h"
#include "patterns.h"

// include system headers
#if defined(_WIN64)
#include <Windows.h>
#include <Psapi.h>
#else
#include <unistd.h>
#include <dlfcn.h>
#include <link.h>
#include <sys/types.h>
#include <dirent.h>
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


#if !defined(_WIN64)
static int
on_module_enum(struct dl_phdr_info *info, size_t size, void *data)
{
    PatternBounds* pResults = (PatternBounds*)data;
    if(!pResults) return 1;
    
    void* base = (void*)info->dlpi_addr;
    
    //Println(LT_INFO, "Base module relocation: %p", base);
    
    // find Loadable program segment (we only pattern scan this region)
    for(int i = 0; i < info->dlpi_phnum;i++)
    {
        const ElfW(Phdr)* phdr = &info->dlpi_phdr[i];
        if (phdr->p_type == PT_LOAD) { /* Loadable program segment */
            pResults->first = (void*)((uint64_t)base + (uint64_t)phdr->p_vaddr);
            pResults->last = (void*)((uint64_t)pResults->first + (uint64_t)phdr->p_memsz - 1); 
            return 1;
        }
    }
    
    Println(LT_ERROR, "Failed to find loadable program segment for reforger.");
    return 1;
}

#endif


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
    dl_iterate_phdr(on_module_enum, (void*)&result);
#endif
    Println(LT_INFO, "Main Library Bounds: %p-%p",result.first, result.last);
    return result;
}

int LibraryExists(const char* libName)
{
#if defined(_WIN64)
    return (GetModuleHandleA(libName) != NULL);
#else
    return (dlopen(libName, RTLD_LAZY | RTLD_NOLOAD) != NULL);
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
    char sDir[size];
    memset(sDir, 0, size);
    
    if(!getcwd(sDir, size)) return 0; // not large enough buffer
    
    if(strlen(sDir) + folderNamelen + 2 > size) return 0; // strcat would overflow!
    
    strcat(sDir, "/"); 
    strcat(sDir, folderName);
    
    strcpy(buffer, sDir);
    return 1;
#endif
}

#if !defined(_WIN64)
#include <stdbool.h>

bool match(const char *pattern, const char *candidate, int p, int c) {
    if (pattern[p] == '\0') {
        return candidate[c] == '\0';
    } else if (pattern[p] == '*') {
        for (; candidate[c] != '\0'; c++) {
            if (match(pattern, candidate, p+1, c))
                return true;
        }
        return match(pattern, candidate, p+1, c);
    } else if (pattern[p] != '?' && pattern[p] != candidate[c]) {
        return false;
    }  else {
        return match(pattern, candidate, p+1, c+1);
    }
}
#endif


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
    DIR* dp = opendir(directory);
    struct dirent *ep;
    
    while (ep = readdir (dp))
    {
        if(strcmp(ep->d_name, ".") == 0 || strcmp(ep->d_name, "..") == 0) continue; // skip .. and . files
        
        char sPath[260];
        memset(sPath, 0, 260);
        sprintf(sPath,"%s/%s",directory, ep->d_name);
        if(!match(filter, ep->d_name, 0, 0)) // check if pattern matches (check only filename not directory)
            continue;
        
        Println(LT_INFO, "found %s/%s in plugin dir",directory, ep->d_name);
        enumCallback(sPath);
    }
    closedir(dp);
    return 1;
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
#else
    void* hLib = dlopen(library, RTLD_NOW | RTLD_NODELETE);
    if(!hLib) return 0;
    return dlsym(hLib, function);
#endif
}