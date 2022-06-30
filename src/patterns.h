/* Author: Kegan 'Lystic' Hollern */

#ifndef PATTERNS_H
#define PATTERNS_H


typedef struct module_bounds {
    void* first;
    void* last;
} PatternBounds;


void* FindPattern(PatternBounds bounds, const char* pattern);

#endif //PATTERNS_H
