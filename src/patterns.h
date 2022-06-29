/* date = June 29th 2022 2:07 pm */

#ifndef PATTERNS_H
#define PATTERNS_H


struct PatternBounds {
    void* first;
    void* last;
}


void* FindPattern(PatternBounds bounds, const char* pattern);

#endif //PATTERNS_H
