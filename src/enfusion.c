#include "enfusion.h"

#include <stdint.h>

#if defined(_WIN64)
#include <Windows.h>
#endif

#include "patterns.h"

#if defined(_WIN64)
const char* PATTERN_SCRIPT_TABLE_HEAD = "48 8B 1D ? ? ? ? 48 8B F2 4C 8B F1";
const char* PATTERN_REGISTER_CLASS = "48 83 EC 38 4C 8B C2 41 B1 02";
const char* PATTERN_REGISTER_CLASS_FUNCTION = "48 89 5C 24 ? 57 48 83 EC 30 0F B6 44 24 ? 48 8B D9";
#elif
const char* PATTERN_SCRIPT_TABLE_HEAD = "00";
const char* PATTERN_REGISTER_CLASS = "00";
const char* PATTERN_REGISTER_CLASS_FUNCTION = "00";
#endif


TEnfusionRegisterClass RegisterEnfusionClass = NULL;
TEnfusionRegisterClassFunction RegisterEnfusionClassFunction = NULL;


EEngineType GetEnfusionEngineType()
{
#if defined(_WIN64)
    if(GetModuleHandleA("Qt5Core.dll")) return ET_WORKBENCH;
    if(GetModuleHandleA("d3d11.dll") || GetModuleHandleA("d3d12.dll")) return ET_OTHER;
#endif
    // on linux only the server can run so we can just assume it's server!
    return ET_SERVER;
}


int InitEnfusion()
{
    // find patterns for 
    return 1;
}

