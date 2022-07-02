/* date = June 29th 2022 1:05 pm */

#ifndef ENFUSION_H
#define ENFUSION_H

#include <stdarg.h>

#include "logger.h"
#include "conventions.h"

typedef enum {ET_WORKBENCH, ET_SERVER, ET_OTHER} EEngineType;

// ---------------------------------------------------------------------------
// engine logging
typedef void(fastcall* TEnfusionLogPrintf)(unsigned int message_level, long long sender_type, const char *format, va_list args);

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

EEngineLogLevel GetEngineLogLevel(ELogType type);
int VEnfusionPrint(EEngineLogType type, EEngineLogLevel level, const char* format, va_list args);

// --------------------------------------------------------------------------
// proto script function definition

typedef void*(fastcall* TEnfusionScriptFunction)(void* pArgs, void* pResult);

// ---------------------------------------------------------------------------
// engine script registrator


typedef void*(fastcall* TEnfusionRegisterClass)(void* pScriptCtx, const char* className);
typedef void*(fastcall* TEnfusionRegisterClassFunction)(void* pScriptCtx, void* pClassInst, const char* functionName, TEnfusionScriptFunction* scriptFunction, unsigned int zero, char one);

typedef struct enfusion_plugin_registrator_function_table_entry FunctionTableEntry;
typedef struct enfusion_registrator EnfusionRegistrator;
typedef struct enfusion_registrator_vtable EnfusionRegistratorVTable;
typedef void*(fastcall* TEnfusionRegistratorFunction)(EnfusionRegistrator* registrator);
typedef void*(fastcall* TEnfusionRegistratorRegisterFunction)(EnfusionRegistrator* registrator, void* a2);


struct enfusion_registrator_vtable {
#if !defined(_WIN64)
    TEnfusionRegistratorFunction LinuxHeader;
#endif
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

EnfusionRegistrator* CreateRegistrator(const char* className);
int InsertChildRegistrator(EnfusionRegistrator* parent, EnfusionRegistrator* child);
FunctionTableEntry* InsertFunction(EnfusionRegistrator* registrator, const char* functionName, TEnfusionScriptFunction function);
EnfusionRegistrator* GetLastRegistratorEntry();


EEngineType GetEnfusionEngineType();
int InitEnfusion();
int WaitForGlobalRegistratorTable();





#endif //ENFUSION_H
