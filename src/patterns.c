/* Author: Kegan 'Lystic' Hollern */
#include "patterns.h"

#include <stdlib.h>
#include <stdint.h>

#include "logger.h"

void* searchByMask(PatternBounds bounds, const unsigned char* search, const char* mask);
int patternToSearchMask(const char* pattern, unsigned char* searchOut, char* maskOut);


void* ReadRel(void* op_start, int op_prefix) 
{
    if(!op_start) return 0;
    
    void* read_at = (void*)((uint64_t)op_start + op_prefix); // jump past our prefix (mov/call opcode)
    int32_t rel = *(int32_t*)read_at; // read 4 byte rel value (rel can be negative!)
    void* dest = (void*)((uint64_t)op_start + 4 + op_prefix + rel); // rel is based on the next instruction
    return dest;
}

// find a pattern of format "01 A2 48 F3 ? A2"
void* FindPattern(PatternBounds bounds, const char* pattern)
{
    // convert friendly pattern format to search/mask format
    char mask[255] = { 0 };
    unsigned char search[255] = { 0 };
    if(!patternToSearchMask(pattern, search, mask)) return 0;
    
    // find by mask
    return searchByMask(bounds, search, mask);
}

// convert "AA 00 ? 2F" to a "\xAA\x00\x00\x2F" and "xx?x"
int patternToSearchMask(const char* pattern, unsigned char* searchOut, char* maskOut)
{
    int idx = 0;
    
    const char* c;
    for(c = pattern; *c != '\0'; c++)
    {
        if(*c == '?')
        {
            maskOut[idx] = '?';
            searchOut[idx] = 0x0;
            idx++;
            continue;
        }
        if(*c == ' ') continue;
        
        long int value = strtol(c,NULL, 16);
        if(value > 0xFF) { // expect 0x0 to 0xFF
            Println(LT_ERROR,"Invalid hex value found in pattern: '%s' %d.", pattern, value);
            return 0;
        }
        maskOut[idx]='x';
        searchOut[idx] = (unsigned char)value;
        idx++;
        c++; // we need to step twice to get to the next space
        if(*c == '\0') {
            Println(LT_WARN,"Unexpected end of pattern '%s'.", pattern);
            break; // unexpected end of pattern? ex: "AA A"
        }
    }
    
    return 1;
}

// find a pattern by mask
void* searchByMask(PatternBounds bounds, const unsigned char* search, const char* mask)
{
    if(!bounds.first || !bounds.last) return 0;
    
    for(void* addr = bounds.first; addr < bounds.last;addr++)
    {
        // store pointers to our search string and real data
        const unsigned char* s = search;
        const unsigned char* r = addr;
        
        // iterate our mask, search, and real address all at once
        for(const char* m = mask; *m != '\0';m++,s++,r++)
        {
            if(*m == '?') continue; // if mask is '?' skip this byte check
            if(*s != *r) break; // if real does not match our search then this is not a pattern match
        }
        if(*s == '\0') // if we made it to the end of our search above, we have a valid pattern hit
        {
            return addr; // return address of first byte of our pattern hit
        }
    }
    return 0; // no hit in bounds
}