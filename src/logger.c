#include "logger.h"

#include <stdio.h>
#include <stdarg.h>

#include "enfusion.h"

void printToStdout(ELogType type, const char* format, va_list args);


void Println(ELogType type, const char* format, ...)
{
    // get engine definition for this log level
    EEngineLogLevel lvl = GetEngineLogLevel(type);
    
    va_list args;
    va_start(args, format);
    if(!VEnfusionPrint(ELT_DEFAULT, lvl, format, args))
    {
        // failed to print to enfusion so we'll need to print to stdout
        printToStdout(type, format, args);
    }
    va_end(args);
    
    /*
    EEngineLogLevel elevel = ELL_INFO;
    const char* typedetails = "(?)";
    switch(type)
    {
        case LT_INFO:
        elevel = ELL_INFO;
        typedetails = ("   ");
        break;
        case LT_WARN:
        elevel = ELL_WARN;
        typedetails = ("(W)");
        break;
        case LT_ERROR:
        elevel = ELL_ERROR;
        typedetails = ("(E)");
        break;
        case LT_FATAL:
        elevel = ELL_FATAL;
        typedetails = ("(F)");
        break;
    }
    
    va_list lst;
    va_start( lst, format );
    if(!VEnfusionPrint(ELT_DEFAULT, elevel, format, lst))
    {
        printf("INFINITY   ");
        printf(typedetails);
        printf(": ");
        vprintf( format, lst );
        printf("\n");
    }
    va_end( lst );
*/
}


// fallback in case enfusion print fails for whatever reason
void printToStdout(ELogType type, const char* format, va_list args)
{
    
    printf("INFINITY   ");
    switch(type)
    {
        case LT_INFO: printf("   "); break;
        case LT_WARN: printf("(W)"); break;
        case LT_ERROR: printf("(E)"); break;
        case LT_FATAL: printf("(F)"); break;
    }
    printf(": ");
    vprintf( format, args );
    printf("\n");
}