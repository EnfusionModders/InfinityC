/* date = June 29th 2022 5:35 pm */

#ifndef INFINITYPLUGIN_H
#define INFINITYPLUGIN_H

typedef void ScriptClass;
typedef void ScriptFunction;

typedef enum {LVL_INFO, LVL_WARN, LVL_ERROR, LVL_FATAL} LogLevel;

typedef void*(__fastcall* TUserScriptFunction)(void* pArgs, void* pResult);
typedef ScriptClass*(__fastcall* TRegisterClass)(const char* className);
typedef ScriptFunction*(__fastcall* TRegisterFunction)(ScriptClass* registeredClass, const char* functionName, TUserScriptFunction function);
typedef void(__fastcall* TPrintToLogf)(LogLevel level, const char* format, ...);

typedef struct infinity_core {
    TRegisterClass registerClass;
    TRegisterFunction registerFunction;
    TPrintToLogf printToLogf;
} InfinityCore;



#endif //INFINITYPLUGIN_H
