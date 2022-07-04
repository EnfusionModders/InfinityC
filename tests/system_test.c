#include "tests.h"

#include "minunit.h"

// link to Infinity headers
#include "system.h"

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>


int test_OSSleep() {
    clock_t t;
    t = clock();
    
    OSSleep(5000);
    
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    
    _assert(time_taken <= 5.1 && time_taken >= 4.9, "Time out of bounds");
    
    return 0;
}
int test_GetLibraryBounds() {
    PatternBounds bounds = GetLibraryBounds(NULL);
    _assert(bounds.first && bounds.last && bounds.first != bounds.last, "Invalid library bounds.");
    return 0;
}
int test_LibraryExists() {
    _assert(LibraryExists(0), "Main Module not found");
    return 0;
}
int test_GetRelativeDirectory() {
    char FULL_PATH[260];
    memset(FULL_PATH, 0, 260);
    int result = GetRelativeDirectory("missing_folder", FULL_PATH, 260);
    
    _assert(result, "Error while getting relative directory");
    _assert(strstr(FULL_PATH, "/missing_folder") || strstr(FULL_PATH, "\\missing_folder"), "missing_folder not in path");
    _assert(strcmp(FULL_PATH, "missing_folder") != 0, "Missing full path to main application");
    
    return 0;
}


// returns the # of failed tests
int test_system() {
    int failed = 0;
    _verify(test_OSSleep, failed);
    _verify(test_GetLibraryBounds, failed);
    _verify(test_LibraryExists, failed);
    _verify(test_GetRelativeDirectory, failed);
    
    return failed;
}