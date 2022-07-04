#include "tests.h"

#inlcude "minunit.h"

// link to Infinity headers
#include "system.h"

#include <stdio.h>
#include <time.h>
#include <string.h>


int test_OSSleep() {
    clock_t t;
    t = clock();
    
    OSSleep(5000);
    
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    
    _assert(time_taken <= 5.1 && time_taken >= 4.9, "Time out of bounds");
    
    return 0;
    
}

// returns the # of failed tests
int test_system() {
    int failed = 0;
    _verify(test_OSSleep, failed);
    
    
    return failed;
}