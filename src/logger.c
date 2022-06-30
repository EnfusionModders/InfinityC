#include "logger.h"

#include <stdio.h>
#include <stdarg.h>


#include "enfusion.h"

void Println(ELogType type, const char* format, ...)
{
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
}