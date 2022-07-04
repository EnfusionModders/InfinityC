/* date = June 30th 2022 2:13 pm */

#ifndef ENSCRIPT_H
#define ENSCRIPT_H

typedef struct script_native_holder {
    void* pValue;
} NativeValueHolder;
typedef struct script_argument_values {
    NativeValueHolder* pListStart[1];
} ProtoArguments;
typedef struct script_argument_types {
    
} ProtoArgumentTypes;
typedef struct script_function_context {
    ProtoArguments* pArgs;
    ProtoArgumentTypes* pArgTypes;
} FunctionContext;
typedef struct script_result_handler {
    NativeValueHolder* pReturn;
} FunctionResult;



// ---------------------------------------------------------
// helper functions
static inline void WriteNativeValue(NativeValueHolder* native, void* pData, unsigned int size)
{
    unsigned char* value_ptr = (unsigned char*)native;
    unsigned char* data_ptr = (unsigned char*)pData;
    
    if(!value_ptr) return;
    if(!data_ptr) return;
    
    for(int i = 0; i < size; i++)
    {
        value_ptr[i] = data_ptr[i]; 
    }
}

// idk we may need this when writing uninitialized values
//   int type;
//   Test.ExampleUninitSet(type);
static inline NativeValueHolder* CreateNativeValue(void* pData, unsigned int size)
{
    NativeValueHolder* newBuffer = malloc(size);
    WriteNativeValue(newBuffer, pData, size);
    return newBuffer;
}
static inline NativeValueHolder* GetArgumentHolder(FunctionContext* pCtx, unsigned int index) {
    if(!pCtx) return 0;
    ProtoArguments* args = pCtx->pArgs;
    if(!args) return 0;
    NativeValueHolder** start = args->pListStart;
    if(!start) return 0;
    return start[index];
}
static inline void* GetArgument(FunctionContext* pCtx, unsigned int index) {
    NativeValueHolder* native = GetArgumentHolder(pCtx, index);
    if(!native) return 0;
    return native->pValue;// this may not work without size information, may need to follow the WriteNativeValue style...
}
// this function is not working :(
static inline void SetArgument(FunctionContext* pCtx, unsigned int index, void* pData, unsigned int size)
{
    NativeValueHolder* native = GetArgumentHolder(pCtx, index);
    if(!native) return;
    WriteNativeValue(native, pData, size);
}
static inline void SetResult(FunctionResult* pResult, void* pData, unsigned int size) {
    if(!pResult) return;
    NativeValueHolder* native = pResult->pReturn;
    if(!native) return;
    // write the value to the preallocated return buffer
    WriteNativeValue(native, pData, size);
}


#endif //ENSCRIPT_H
