/* date = June 29th 2022 1:05 pm */

#ifndef ENFUSION_H
#define ENFUSION_H

typedef enum {ET_WORKBENCH, ET_SERVER, ET_OTHER} EEngineType;

// enfusion function definitions
typedef void(__fastcall* TEnfusionScriptFunction)(void* pArgs, void* pResult);
typedef void*(__fastcall* TEnfusionRegisterClass)(void* pScriptCtx, const char* className);
typedef void*(__fastcall* TEnfusionRegisterClassFunction)(void* pScriptCtx, void* pClassInst, const char* functionName, TEnfusionScriptFunction scriptFunction, unsigned int zero, char one);

// pointers to enfusion functions
// TODO: may want to store these functions in a struct instead of globally like such
extern TEnfusionRegisterClass RegisterEnfusionClass;
extern TEnfusionRegisterClassFunction RegisterEnfusionClassFunction;


EEngineType GetEnfusionEngineType();
int InitEnfusion();

#endif //ENFUSION_H
