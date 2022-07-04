#include "tests.h"
#include "minunit.h"

#include <stdio.h>

int main(intc argc, char* argv[]) {
    printf("Testing InfinityC...\n");
    int failures = 0;
    _verify(test_system, failures);
    
    if(failures) {
        printf("%d tests failed!\n", failures);
    } else {
        printf("Tests passed!\n");
    }
    return failures;
}