/* date = June 29th 2022 5:35 pm */

#ifndef INFINITYPLUGIN_H
#define INFINITYPLUGIN_H

#include "enscript.h"
#include "conventions.h"

typedef void ScriptClass;
typedef void ScriptFunction;

typedef enum {LVL_INFO, LVL_WARN, LVL_ERROR, LVL_FATAL} LogLevel;

typedef FunctionResult*(fastcall* TUserScriptFunction)(FunctionContext* pCtx, FunctionResult* pResult);

typedef ScriptClass*(fastcall* TRegisterClass)(const char* className);
typedef ScriptFunction*(fastcall* TRegisterFunction)(ScriptClass* registeredClass, const char* functionName, TUserScriptFunction function);

typedef void(fastcall* TPrintToLogf)(LogLevel level, const char* format, ...);

typedef struct infinity_core {
    TRegisterClass RegisterClass;
    TRegisterFunction RegisterFunction;
    TPrintToLogf Print;
} InfinityCore;



#endif //INFINITYPLUGIN_H
