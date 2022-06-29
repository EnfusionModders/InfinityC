#include "enfusion.h"

#include <stdint.h>

#if defined(_WIN64)
#include <Windows.h>
#include <Psapi.h>
#elif
#include <unistd.h> // sleep()
#endif

#include "logger.h"
#include "patterns.h"

const char* TARGET_MODULE_NAME = "ModuleGame";

#if defined(_WIN64)
const char* PATTERN_SCRIPT_TABLE_HEAD = "48 8B 1D ? ? ? ? 48 8B F2 4C 8B F1";
const char* PATTERN_REGISTER_CLASS = "48 83 EC 38 4C 8B C2 41 B1 02";
const char* PATTERN_REGISTER_CLASS_FUNCTION = "48 89 5C 24 ? 57 48 83 EC 30 0F B6 44 24 ? 48 8B D9";
#elif
const char* PATTERN_SCRIPT_TABLE_HEAD = "00";
const char* PATTERN_REGISTER_CLASS = "00";
const char* PATTERN_REGISTER_CLASS_FUNCTION = "00";
#endif

EnfusionRegistrator** EnfusionGlobalRegistratorTable;
const char* EnfusionStringModuleGame = NULL;
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

PatternBounds getEngineBounds()
{
    PatternBounds bounds;
    bounds.first = 0;
    bounds.last = 0;
    
#if defined(_WIN64)
    MODULEINFO info;
    HMODULE base = GetModuleHandle(NULL);
    if(!GetModuleInformation(GetCurrentProcess(), 
                             base,
                             &info,
                             sizeof(MODULEINFO)))
    {
        Println(LT_ERROR, "Failed to get module information during engine bounds calculation.");
        return bounds;
    }
    bounds.first = info.lpBaseOfDll;
    bounds.last = (void*)((uint64_t)base + info.SizeOfImage - 1);
#elif 
    //TODO: linux calculate module bounds
#endif
    
    
    return bounds;
}

int InitEnfusion()
{
    Println(LT_DEBUG, "Enfusion init started...");
    // find patterns for 
    PatternBounds searchRange = getEngineBounds();
    if(!searchRange.first || !searchRange.last)
    {
        Println(LT_ERROR, "Failed to calculate search range for enfusion engine.");
        return 0;
    }
    
    void* addr = FindPattern(searchRange, PATTERN_SCRIPT_TABLE_HEAD);
    if(!addr)
    {
        Println(LT_ERROR, "Failed to find global registrator table.");
        return 0;
    }
    uint32_t rel = *(uint32_t*)((uint64_t)addr+3); // pattern start is offset from 3 to the rel access
    EnfusionGlobalRegistratorTable = (void*)((uint64_t)addr + 7 + rel); // 3 offset + 4 size of int32
    Println(LT_DEBUG, "Found Table Head @ %p from %p / %d",EnfusionGlobalRegistratorTable, addr, rel);
    
    
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
    
    Println(LT_DEBUG, "Enfusion init success.");
    return 1;
}

// ------------------------------------------------------------------------------
// global registrator table stuff

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

int WaitForGlobalRegistratorTable()
{
    if(!EnfusionGlobalRegistratorTable) return 0; // ???? table was never set?
    int total_count = 0;
    // wait for table to be created
    const EnfusionRegistrator* head = 0;
    while(!head)
    {
        head = *EnfusionGlobalRegistratorTable;
        Sleep(100);
        total_count += 100;
        if(total_count >= 5000) return 0; // timeout!
    }
    // wait for ModuleGame entries to be added to the table
    while(!findModuleGameInTable(head))
    {
        Sleep(100);
        total_count += 100;
        if(total_count >= 5000) return 0; // timeout!
    }
    return 1;
}


// --------------------------------------------------------------------------------
// enfusion script registrator implementation

void* rtnZero() { return 0; }
void* rtnOne() { return (void*)1; }
void* destroyRegistrator(EnfusionRegistrator* registrator)
{
    Println(LT_WARN, "Deconstructor for registrator called!?");
    free(registrator);
    return 0;
}
void* registerFunction(EnfusionRegistrator* registrator, void* a2)
{
    // return 1 on success
    if(!registrator) return 0;
    const char* name = registrator->className;
    if(!name) return 0;
    FunctionTableEntry* functionEntry = registrator->classFunctions;
    if(!functionEntry) return (void*)1; // no functions registered... no point registering this class
    
    
    if ((*(uint32_t*)((uint64_t)a2 + 24) & 0x10) == 0)
		return (void*)1;
    
    Println(LT_DEBUG, "Base registrator called for %s.", name);
    
    void* pContext = *(void**)((uint64_t)a2 + 16);
    registrator->scriptClass = RegisterEnfusionClass(pContext, name);
    if(registrator->scriptClass)
    {
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


EnfusionRegistrator* CreateRegistrator(const char* className)
{
    if(!EnfusionStringModuleGame) return 0;
    
    EnfusionRegistrator* registrator = (EnfusionRegistrator*)malloc(sizeof(EnfusionRegistrator));
    if(!registrator) return 0;
    memset(registrator, 0, sizeof(EnfusionRegistrator)); // zero our buffer
    registrator->vtable = &g_RegistratorVtable;
    registrator->moduleName = EnfusionStringModuleGame;
    registrator->className = className;
    
    // maybe we want to populate the registration struct here?
    
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

// ---------------------------------------------------------------------------------