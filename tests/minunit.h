#ifndef MINUNIT_H
#define MINUNIT_H

// Prints failure message and info. Returns 1.
#define FAIL(msg) do { printf("Test %s() failed at line %d.\n\tInfo: %s", __func__, __LINE__, msg); return 1; } while(0)
// asserts TEST is true. Prints message and failure on fail.
#define _assert(test, message) do { if(!(test)) FAIL(message); } while(0)
// increments fail_counter if the test function fails by the return code
#define _verify(test, fail_counter) do { int minunit_test_result=test(); if(minunit_test_result) fail_counter+=minunit_test_result; } while(0)


#endif