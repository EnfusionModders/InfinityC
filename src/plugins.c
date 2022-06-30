#include "plugins.h"

#include <stdio.h>

#if defined(_WIN64)
#include <Windows.h>
#endif

#include "enfusion.h"
#include "infinityplugin.h"
#include "logger.h"

typedef void(__fastcall* TPluginEnumCallback)(const char* fullPath);
typedef void(__fastcall* TOnPluginLoad)(InfinityCore* pCore);

void printToLogf(LogLevel level, const char* format, ...);
void* getExport(const char* library, const char* function);
void enumPluginFiles(TPluginEnumCallback onPluginFound);
void onPluginFound(const char* libraryPath);
void initCore();
ScriptClass* pluginRegisterClass(const char* className);
ScriptFunction* pluginRegisterClassFunction(ScriptClass* registeredClass, const char* functionName, TUserScriptFunction function);

InfinityCore g_Core;

void LoadPlugins()
{
    // setup global infinity core
    initCore();
    
    
    // load all modules from "plugins" directory
    // find "OnPluginLoad" C export from plugin
    enumPluginFiles(onPluginFound);
    
#if defined(DEBUG)
    
#endif
}

// ---------------------------------------------------------------------
// plugin functionality

void initCore()
{
    g_Core.registerClass = pluginRegisterClass;
    g_Core.registerFunction = pluginRegisterClassFunction;
    g_Core.printToLogf = printToLogf;
}

void printToLogf(LogLevel level, const char* format, ...)
{
    EEngineLogLevel lvl = ELL_INFO;
    switch(level)
    {
        case LVL_WARN:
        lvl = ELL_WARN;
        break;
        case LVL_ERROR:
        lvl = ELL_ERROR;
        break;
        case LVL_FATAL:
        lvl = ELL_FATAL;
        break;
    }
    va_list lst;
    va_start( lst, format );
    VEnfusionPrint(ELT_SCRIPT, lvl, format, lst);
    va_end( lst );
}

ScriptClass* pluginRegisterClass(const char* className)
{
    // here we would insert a new registrator that registers a class with this name and any functions we later specify
    
    EnfusionRegistrator* newEntry = CreateRegistrator(className);
    EnfusionRegistrator* lastEntry = GetLastRegistratorEntry();
    if(!lastEntry) {
        Println(LT_ERROR, "Failed to insert new class. Could not find last registrator entry.");
        return 0;
    }
    if(!newEntry) {
        Println(LT_ERROR, "Failed to insert new class. Failed to create registrator.");
        return 0;
    }
    if(!InsertChildRegistrator(lastEntry, newEntry)) {
        Println(LT_ERROR, "Failed to insert new registrator into table.");
        return 0;
    }
    return newEntry; // we return the registrator pointer here but don't actually tell plugins what it is
}
ScriptFunction* pluginRegisterClassFunction(ScriptClass* registeredClass, const char* functionName, TUserScriptFunction function) 
{
    // registeredClass is actually our EnfusionRegistrator
    EnfusionRegistrator* registrator = (EnfusionRegistrator*)registeredClass;
    if(!registrator) return 0;
    
    return InsertFunction(registrator, functionName, function);
}




// ---------------------------------------------------------------------
// plugin loading and enumeration

void onPluginFound(const char* libraryPath)
{
    // load plugin and call onpluginload
    TOnPluginLoad func = (TOnPluginLoad)getExport(libraryPath, "OnPluginLoad");
    if(!func) {
        Println(LT_ERROR, "Invalid plugin. Could not load: %s", libraryPath);
        return;
    }
    func(&g_Core);
}

void enumPluginFiles(TPluginEnumCallback onPluginFound)
{
#if defined(_WIN64)
    char sDir[MAX_PATH] = { 0 };
    if(!GetCurrentDirectoryA(MAX_PATH, sDir)) {
        Println(LT_ERROR, "Failed to get current working directory.");
        return;
    }
    strcat(sDir, "\\Plugins"); // C:\ReforgerServer\Plugins
    
    WIN32_FIND_DATA fdFile;
    HANDLE hFind = NULL;
    
    char sPath[MAX_PATH] = { 0 };
    
    sprintf(sPath, "%s\\*.*", sDir);
    
    Println(LT_INFO, "Looking for plugins in %s.", sPath);
    
    if((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
    {
        Println(LT_WARN, "Plugin path not found: [%s]", sDir);
        return;
    }
    
    do
    {
        //Find first file will always return "."
        //    and ".." as the first two directories.
        if(strcmp(fdFile.cFileName, ".") != 0 && strcmp(fdFile.cFileName, "..") != 0)
        {
            //Build up our file path using the passed in
            //  [sDir] and the file/foldername we just found:
            sprintf(sPath, "%s\\%s", sDir, fdFile.cFileName);
            
            //Is the entity a File or Folder?
            if(!(fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                Println(LT_INFO, "Found plugin: %s\n", sPath);
                onPluginFound(sPath);
            }
        }
    }
    while(FindNextFile(hFind, &fdFile)); //Find the next file.
    
    FindClose(hFind); //Always, Always, clean things up!
    
#elif
    Printf(LT_WARN, "Linux plugin enum not implemented.");
    // TODO: linux file enumeration
#endif
}

void* getExport(const char* library, const char* function)
{
#if defined(_WIN64)
    HMODULE hLib = LoadLibraryA(library);
    if(!hLib) return 0;
    return GetProcAddress(hLib, "OnPluginLoad");
#elif
    // TODO: dlopen / dlsym
    Printf(LT_WARN, "Linux getExport not implemented.");
    return 0;
#endif
}
