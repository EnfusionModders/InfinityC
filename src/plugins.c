#include "plugins.h"

#include <stdio.h>
#include <stdlib.h>

#include "system.h"
#include "enfusion.h"
#include "infinityplugin.h"
#include "logger.h"
#include "conventions.h"

// ------------------------------------------------------------
// plugin interface

void pluginPrint(LogLevel level, const char* format, ...);
ScriptClass* pluginRegisterClass(const char* className);
ScriptFunction* pluginRegisterClassFunction(ScriptClass* registeredClass, const char* functionName, TUserScriptFunction function) ;

InfinityCore g_Core = {
    .RegisterClass = pluginRegisterClass,
    .RegisterFunction = pluginRegisterClassFunction,
    .Print = pluginPrint,
};

// create registrator, insert it into global registrator table
// returns registrator pointer without type info
ScriptClass* pluginRegisterClass(const char* className)
{
    if(!className) return 0;
    
    EnfusionRegistrator* newEntry = CreateRegistrator(className);
    if(!newEntry) {
        Println(LT_ERROR, "Failed to insert new class. Failed to create registrator.");
        return 0;
    }
    
    EnfusionRegistrator* lastEntry = GetLastRegistratorEntry();
    if(!lastEntry) {
        Println(LT_ERROR, "Failed to insert new class. Could not find last registrator entry.");
        return 0;
    }
    
    if(!InsertChildRegistrator(lastEntry, newEntry)) {
        Println(LT_ERROR, "Failed to insert new registrator into table.");
        return 0;
    }
    return newEntry;
}
// insert function information into the registrator class
ScriptFunction* pluginRegisterClassFunction(ScriptClass* registeredClass, const char* functionName, TUserScriptFunction function) 
{
    EnfusionRegistrator* registrator = (EnfusionRegistrator*)registeredClass;
    if(!registrator) return 0;
    
    if(!function) return 0;
    if(!functionName) return 0;
    
    return InsertFunction(registrator, functionName, (TEnfusionScriptFunction)function);
}
ELogType pluginLvlToInfinityLvl(LogLevel level)
{
    switch(level) {
        case LVL_INFO: return LT_INFO;
        case LVL_WARN: return LT_WARN;
        case LVL_ERROR: return LT_ERROR;
        case LVL_FATAL: return LT_ERROR;
    }
}
// printf to enfusion internal console
void pluginPrint(LogLevel level, const char* format, ...)
{
    if(!format) return;
    
    va_list lst;
    va_start( lst, format );
    
    VEnfusionPrint(ELT_SCRIPT, GetEngineLogLevel(pluginLvlToInfinityLvl(level)), format, lst);
    
    va_end( lst );
    
}


// ------------------------------------------------------------
// plugin loading

typedef void(fastcall* TOnPluginLoad)(InfinityCore* pCore);

// enumerate all plugin libraries and call the function w/ library path
void enumPluginFiles(TFileFoundCallback enumCallback)
{
    char pluginDir[260] = { 0 }; // windows max path is 260 so we'll restrict linux to that
    if(!GetRelativeDirectory("plugins", pluginDir, 260)) {
        Println(LT_ERROR, "Failed to get relative plugin directory.");
        return;
    }
    
    
    Println(LT_INFO, "Looking for plugins in %s.", pluginDir);
    if(!EnumerateFilesInDirectory(pluginDir,  GetSystemLibraryExtension(), enumCallback))
    {
        Println(LT_ERROR, "Failed to enumerate plugins. Does the plugins directory exist?");
        return;
    }
}
void onPluginFound(const char* libraryPath)
{
    // load plugin and call onpluginload
    TOnPluginLoad func = (TOnPluginLoad)GetExport(libraryPath, "OnPluginLoad");
    if(!func) {
        Println(LT_ERROR, "Invalid plugin. Could not load: %s", libraryPath);
        return;
    }
    func(&g_Core);
}
void LoadPlugins()
{
    // enumerate all plugin files and call onPluginFound
    enumPluginFiles(onPluginFound);
}
