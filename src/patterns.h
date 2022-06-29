/* date = June 29th 2022 2:07 pm */

#ifndef PATTERNS_H
#define PATTERNS_H


typedef struct module_bounds {
    void* first;
    void* last;
} PatternBounds;


void* FindPattern(PatternBounds bounds, const char* pattern);

#endif //PATTERNS_H
