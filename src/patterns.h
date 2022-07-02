/* Author: Kegan 'Lystic' Hollern */

#ifndef PATTERNS_H
#define PATTERNS_H


typedef struct module_bounds {
    void* first;
    void* last;
} PatternBounds;


void* ReadRel(void* op_start, int op_prefix);// read a relative opcode
void* FindPattern(PatternBounds bounds, const char* pattern);

#endif //PATTERNS_H
