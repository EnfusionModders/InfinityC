/* date = June 29th 2022 5:35 pm */

#ifndef INFINITYPLUGIN_H
#define INFINITYPLUGIN_H

#include "enscript.h"

typedef void ScriptClass;
typedef void ScriptFunction;

typedef enum {LVL_INFO, LVL_WARN, LVL_ERROR, LVL_FATAL} LogLevel;

typedef FunctionResult*(__fastcall* TUserScriptFunction)(FunctionContext* pCtx, FunctionResult* pResult);

typedef ScriptClass*(__fastcall* TRegisterClass)(const char* className);
typedef ScriptFunction*(__fastcall* TRegisterFunction)(ScriptClass* registeredClass, const char* functionName, TUserScriptFunction function);

typedef void(__fastcall* TPrintToLogf)(LogLevel level, const char* format, ...);

typedef struct infinity_core {
    TRegisterClass RegisterClass;
    TRegisterFunction RegisterFunction;
    TPrintToLogf Print;
} InfinityCore;



#endif //INFINITYPLUGIN_H
