#include "logger.h"

#include <stdio.h>
#include <stdarg.h>

void Println(ELogType type, const char* format, ...)
{
#if !defined(DEBUG)
    if(type == LT_DEBUG) return; // no debug logs when compiled without debug
#endif
    printf("INFINITY   ");
    switch(type)
    {
        case LT_INFO:
        printf("   ");
        break;
        case LT_WARN:
        printf("(W)");
        break;
        case LT_ERROR:
        printf("(E)");
        break;
        case LT_DEBUG:
        printf("(D)");
        break;
        default:
        printf("(?)");
        break;
    }
    printf(": ");
    // temporary until we've figured out how to print to the standard logger in enfusion
    va_list lst;
    va_start( lst, format );
    vprintf( format, lst );
    va_end( lst );
    printf("\n");
}