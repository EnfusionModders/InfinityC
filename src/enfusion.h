/* date = June 29th 2022 1:05 pm */

#ifndef ENFUSION_H
#define ENFUSION_H

#include <stdarg.h>

typedef enum {ET_WORKBENCH, ET_SERVER, ET_OTHER} EEngineType;
typedef enum {
    // I only added the ones I care about xd
    ELT_DEFAULT = 1,
    ELT_ENGINE = 2,
    ELT_SCRIPT = 9,
    ELT_INIT = 13,
} EEngineLogType;
typedef enum {
    ELL_INFO = 8,
    ELL_WARN = 0x10,
    ELL_ERROR = 0x20,
    ELL_FATAL = 0x40,
} EEngineLogLevel;


// enfusion function definitions
typedef void*(__fastcall* TEnfusionScriptFunction)(void* pArgs, void* pResult);
typedef void*(__fastcall* TEnfusionRegisterClass)(void* pScriptCtx, const char* className);
typedef void*(__fastcall* TEnfusionRegisterClassFunction)(void* pScriptCtx, void* pClassInst, const char* functionName, TEnfusionScriptFunction* scriptFunction, unsigned int zero, char one);
typedef void(__fastcall* TEnfusionLogPrintf)(unsigned int message_level, long long sender_type, const char *format, va_list args);

// registrator "class" structures and types
typedef struct enfusion_plugin_registrator_function_table_entry FunctionTableEntry;
typedef struct enfusion_registrator EnfusionRegistrator;
typedef struct enfusion_registrator_vtable EnfusionRegistratorVTable;
typedef void*(__fastcall* TEnfusionRegistratorFunction)(EnfusionRegistrator* registrator);
typedef void*(__fastcall* TEnfusionRegistratorRegisterFunction)(EnfusionRegistrator* registrator, void* a2);
struct enfusion_registrator_vtable {
    TEnfusionRegistratorFunction Deconstruct;
    TEnfusionRegistratorFunction Unk0;
    TEnfusionRegistratorRegisterFunction Register;
    TEnfusionRegistratorFunction Unk1;
    TEnfusionRegistratorFunction Unk2;
    TEnfusionRegistratorFunction Unk3;
    TEnfusionRegistratorFunction Unk4;
    TEnfusionRegistratorFunction Unk5;
    TEnfusionRegistratorFunction Unk6;
};
struct enfusion_plugin_registrator_function_table_entry {
    const char* name;
    void* function;
    FunctionTableEntry* next;
};
struct enfusion_registrator {
    const EnfusionRegistratorVTable* vtable;
    const char* moduleName;
    EnfusionRegistrator* next;
    void* scriptClass;
    // these are added to support our plugin registration system --- NOT NATIVE TO ENFUSION
    const char* className;
    FunctionTableEntry* classFunctions;
};



// pointers to enfusion functions and objects
// TODO: may want to store these functions in a struct instead of globally like such
//extern TEnfusionRegisterClass RegisterEnfusionClass;
//extern TEnfusionRegisterClassFunction RegisterEnfusionClassFunction;
//extern const char* EnfusionStringModuleGame;
//extern EnfusionRegistrator** EnfusionGlobalRegistratorTable;



EEngineType GetEnfusionEngineType();
int InitEnfusion();
EnfusionRegistrator* CreateRegistrator(const char* className);
int WaitForGlobalRegistratorTable();
EnfusionRegistrator* GetLastRegistratorEntry();
int InsertChildRegistrator(EnfusionRegistrator* parent, EnfusionRegistrator* child);
FunctionTableEntry* InsertFunction(EnfusionRegistrator* registrator, const char* functionName, TEnfusionScriptFunction function);
int VEnfusionPrint(EEngineLogType type, EEngineLogLevel level, const char* format, va_list args);
int EnfusionPrint(EEngineLogType type, EEngineLogLevel level, const char* format, ...);

#endif //ENFUSION_H
