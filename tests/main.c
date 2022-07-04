#include "tests.h"
#include "minunit.h"

#include <stdio.h>

int main(int argc, char* argv[]) {
    printf("Testing InfinityC...\n");
    fflush(stdout);
    
    int failures = 0;
    _verify(test_system, failures);
    
    if(failures) {
        printf("%d tests failed!\n", failures);
    } else {
        printf("Tests passed!\n");
    }
    return failures;
}