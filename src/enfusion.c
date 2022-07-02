#include "enfusion.h"

#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "system.h"
#include "logger.h"
#include "patterns.h"


const char* TARGET_MODULE_NAME = "ModuleGame";

#if defined(_WIN64)
const char* PATTERN_SCRIPT_TABLE_HEAD = "48 8B 1D ? ? ? ? 48 8B F2 4C 8B F1";
const char* PATTERN_REGISTER_CLASS = "48 83 EC 38 4C 8B C2 41 B1 02";
const char* PATTERN_REGISTER_CLASS_FUNCTION = "48 89 5C 24 ? 57 48 83 EC 30 0F B6 44 24 ? 48 8B D9";
const char* PATTERN_PRINTF_TO_LOG = "48 8B C4 4C 89 48 20 4C 89 40 18 41 54";
#else
const char* PATTERN_SCRIPT_TABLE_HEAD = "48 8B 1D ? ? ? ? 40 B5 01"; // rel accessor
const char* PATTERN_REGISTER_CLASS = "E8 ? ? ? ? 49 89 C4 4D 85 E4 74 74"; // rel call
const char* PATTERN_REGISTER_CLASS_FUNCTION = "E9 ? ? ? ? BF ? ? ? ? 5B"; // rel call
const char* PATTERN_PRINTF_TO_LOG = "E8 ? ? ? ? 48 81 C4 ? ? ? ? C3 0F 1F 44 00 00 53"; // rel call
#endif

// -----------------------------------------------------------------------------
// engine logging

TEnfusionLogPrintf PrintToEnfusionf = NULL; // pointer to engine function definition

EEngineLogLevel GetEngineLogLevel(ELogType type)
{
    // map our logger logtype structure to our engine log type values
    switch(type)
    {
        case LT_INFO: return ELL_INFO;
        case LT_WARN: return ELL_WARN;
        case LT_ERROR: return ELL_ERROR;
        case LT_FATAL: return ELL_FATAL;
    }
    return 0; // log values < 8 are never returned!
}
int VEnfusionPrint(EEngineLogType type, EEngineLogLevel level, const char* format, va_list args)
{
    if(!PrintToEnfusionf) return 0; // invalid engine pointer, return false
    PrintToEnfusionf(level, type, format, args);
    return 1;
}

// -----------------------------------------------------------------------------
// engine script registrator

// --- engine definition pointers
EnfusionRegistrator** EnfusionGlobalRegistratorTable = NULL;
TEnfusionRegisterClass RegisterEnfusionClass = NULL;
TEnfusionRegisterClassFunction RegisterEnfusionClassFunction = NULL;
const char* EnfusionStringModuleGame = NULL;

// --- registrator virtual table (and it's subsequent functions
void* rtnZero() { return 0; }
void* rtnOne() { return (void*)1; }
void* destroyRegistrator(EnfusionRegistrator* registrator) 
{
    // this function should never run. if the engine deconstructs our registrator
    // something is really wrong
    Println(LT_WARN, "Deconstructor for registrator called!?");
    free(registrator);
    return 0;
}
void* registerFunction(EnfusionRegistrator* registrator, void* a2)
{
    if(!registrator) return 0;
    
    const char* name = registrator->className;
    if(!name) return 0;
    
    FunctionTableEntry* functionEntry = registrator->classFunctions;
    if(!functionEntry) return (void*)1; 
    
    if ((*(uint32_t*)((uint64_t)a2 + 24) & 0x10) == 0)
		return (void*)1;
    // register class name
    void* pContext = *(void**)((uint64_t)a2 + 16);
    registrator->scriptClass = RegisterEnfusionClass(pContext, name);
    
    if(registrator->scriptClass)
    {
        // register all functions in linked list
        pContext = *(void**)((uint64_t)a2 + 16);
        do {
            RegisterEnfusionClassFunction(pContext, 
                                          registrator->scriptClass, 
                                          functionEntry->name, 
                                          functionEntry->function, 
                                          0, 1);
            
            functionEntry = functionEntry->next;
        } while(functionEntry);
        
    }
    return (void*)1;
}
const EnfusionRegistratorVTable g_RegistratorVtable = {
    .Deconstruct = destroyRegistrator,
    .Unk0 = rtnZero,
    .Register = registerFunction,
    .Unk1 = rtnOne,
    .Unk2 = rtnZero,
    .Unk3 = rtnOne,
    .Unk4 = rtnZero,
    .Unk5 = rtnZero,
    .Unk6 = rtnZero,
};
// --- functions / helpers / constructors
EnfusionRegistrator* GetLastRegistratorEntry()
{
    EnfusionRegistrator* head = *EnfusionGlobalRegistratorTable;
    if(!head) return 0;
    
    EnfusionRegistrator* last_valid = head;
    EnfusionRegistrator* next = head->next;
    while(next)
    {
        last_valid = next;
        next = next->next;
    }
    return last_valid;
}
int InsertChildRegistrator(EnfusionRegistrator* parent, EnfusionRegistrator* child)
{
    if(!parent) return 0;
    if(!child && parent->next) return 0;
    
    EnfusionRegistrator* prev_child = parent->next;
    parent->next = child;
    child->next = prev_child;
    
    return 1;
}

EnfusionRegistrator* CreateRegistrator(const char* className)
{
    if(!EnfusionStringModuleGame) return 0;
    
    EnfusionRegistrator* registrator = (EnfusionRegistrator*)malloc(sizeof(EnfusionRegistrator));
    if(!registrator) return 0;
    memset(registrator, 0, sizeof(EnfusionRegistrator)); // zero our buffer
    
    registrator->vtable = &g_RegistratorVtable;
    registrator->moduleName = EnfusionStringModuleGame;
    registrator->className = className;
    
    return registrator;
}

FunctionTableEntry* getLastFunctionEntry(EnfusionRegistrator* registrator)
{
    if(!registrator) return 0;
    FunctionTableEntry* head = registrator->classFunctions;
    if(!head) return 0;
    
    FunctionTableEntry* last_valid = head;
    FunctionTableEntry* next = head->next;
    while(next)
    {
        last_valid = next;
        next = next->next;
    }
    return last_valid;
}

FunctionTableEntry* InsertFunction(EnfusionRegistrator* registrator, const char* functionName, TEnfusionScriptFunction function)
{
    FunctionTableEntry* newEntry = (FunctionTableEntry*)malloc(sizeof(FunctionTableEntry));
    if(!newEntry) return 0;
    
    memset(newEntry,0,sizeof(FunctionTableEntry));
    newEntry->name = functionName;
    newEntry->function = function;
    
    FunctionTableEntry* lastEntry = getLastFunctionEntry(registrator);
    if(!lastEntry) {
        registrator->classFunctions = newEntry;
        return newEntry;
    }
    lastEntry->next = newEntry;
    return newEntry;
}

// ------------------------------------------------------------------------------
// infinity / engine / settup functions


EEngineType GetEnfusionEngineType()
{
    if(LibraryExists("Qt5Core.dll")) return ET_WORKBENCH;
    if(LibraryExists("d3d11.dll") || LibraryExists("d3d12.dll")) return ET_OTHER;
    return ET_SERVER;
}
int findModuleGameInTable(const EnfusionRegistrator* head)
{
    const EnfusionRegistrator* next = head;
    int target_len = strlen(TARGET_MODULE_NAME);
    
    while(next)
    {
        const char* name = next->moduleName; // access violation?!
        if(name && strlen(name) == target_len && strstr(name, TARGET_MODULE_NAME))
        {
            EnfusionStringModuleGame = next->moduleName;
            return 1;
        }
        next = next->next;
    }
    return 0;
}
int WaitForGlobalRegistratorTable()
{
    if(!EnfusionGlobalRegistratorTable) return 0; // ???? table was never set?
    int total_count = 0;
    // wait for table to be created
    const EnfusionRegistrator* head = 0;
    while(!head)
    {
        head = *EnfusionGlobalRegistratorTable;
        OSSleep(100); // OS safe sleep from system.h
        total_count += 100;
        if(total_count >= 5000) return 0; // timeout!
    }
    // wait for ModuleGame entries to be added to the table
    while(!findModuleGameInTable(head))
    {
        OSSleep(100);
        total_count += 100;
        if(total_count >= 5000) return 0; // timeout!
    }
    return 1;
}
PatternBounds getEngineBounds()
{
    return GetLibraryBounds(NULL);
}

int InitEnfusion()
{
    // find patterns for 
    PatternBounds searchRange = getEngineBounds();
    if(!searchRange.first || !searchRange.last)
    {
        Println(LT_ERROR, "Failed to calculate search range for enfusion engine.");
        return 0;
    }
    
#if defined(_WIN64)
    // find windows patterns
    void* addr = FindPattern(searchRange, PATTERN_SCRIPT_TABLE_HEAD);
    if(!addr)
    {
        Println(LT_ERROR, "Failed to find global registrator table.");
        return 0;
    }
    EnfusionGlobalRegistratorTable = ReadRel(addr, 3);
    
    RegisterEnfusionClass = FindPattern(searchRange, PATTERN_REGISTER_CLASS);
    if(!RegisterEnfusionClass)
    {
        Println(LT_ERROR, "Failed to find register enfusion class function.");
        return 0;
    }
    
    RegisterEnfusionClassFunction = FindPattern(searchRange, PATTERN_REGISTER_CLASS_FUNCTION);
    if(!RegisterEnfusionClassFunction)
    {
        Println(LT_ERROR, "Failed to find register enfusion class function function.");
        return 0;
    }
    
    PrintToEnfusionf = FindPattern(searchRange, PATTERN_PRINTF_TO_LOG);
    if(!PrintToEnfusionf)
    {
        Println(LT_ERROR, "Failed to find log print routine.");
        return 0;
    }
    
#else
    // find linux patterns
    void* relcall = FindPattern(searchRange,PATTERN_SCRIPT_TABLE_HEAD);
    if(!relcall)
    {
        Println(LT_ERROR, "Failed to find global registrator table.");
        return 0;
    }
    EnfusionGlobalRegistratorTable = ReadRel(relcall, 3);
    
    relcall = FindPattern(searchRange, PATTERN_REGISTER_CLASS);
    if(!relcall)
    {
        Println(LT_ERROR, "Failed to find register enfusion class function.");
        return 0;
    }
    RegisterEnfusionClass = ReadRel(relcall, 1);
    
    relcall = FindPattern(searchRange, PATTERN_REGISTER_CLASS_FUNCTION);
    if(!relcall)
    {
        Println(LT_ERROR, "Failed to find register enfusion class function function.");
        return 0;
    }
    RegisterEnfusionClassFunction = ReadRel(relcall, 1);
    
    relcall = FindPattern(searchRange, PATTERN_PRINTF_TO_LOG);
    if(!relcall)
    {
        Println(LT_ERROR, "Failed to find log print routine.");
        return 0;
    }
    PrintToEnfusionf = ReadRel(relcall, 1);
#endif
    
    Println(LT_INFO, "Enfusion initialized");
    
    return 1;
}
