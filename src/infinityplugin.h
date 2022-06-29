/* date = June 29th 2022 5:35 pm */

#ifndef INFINITYPLUGIN_H
#define INFINITYPLUGIN_H


typedef void ScriptClass;
typedef void ScriptFunction;

typedef void(__fastcall* TUserScriptFunction)(void* pArgs, void* pResult);
typedef ScriptClass*(__fastcall* TRegisterClass)(const char* className);
typedef ScriptFunction*(__fastcall* TRegisterFunction)(ScriptClass* registeredClass, const char* functionName, TUserScriptFunction function);

typedef struct infinity_core {
    TRegisterClass registerClass;
    TRegisterFunction registerFunction;
} InfinityCore;



/*
Example plugin:

void TestFunction(void* pArgs, void* pResult)
{

printf("wow!");

}

extern "C" OnPluginLoad(InfinityCore* pCore)
{
  
ScriptClass* pClass = pCore->registerClass("ExampleClass");
pCore->registerFunction(pClass, "ExampleFunction", &TestFunction);

}


*/


#endif //INFINITYPLUGIN_H
