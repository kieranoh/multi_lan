#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
Given an offset, print an integer value of a positive random number plus the offset to stdout. If anything goes wrong, print nothing.

@param offset: the offset to add to the random number
*/
void print_rand_num_plus_offset(int offset) {
    // Initialize random number generator
    static int initialized = 0;
    if (!initialized) {
        srand((unsigned int)time(NULL));
        initialized = 1;
    }
    
    // Generate a positive random number
    // rand() returns a value between 0 and RAND_MAX (inclusive)
    // We use modulo to get a reasonable positive number
    int random_num = rand() % 10000;  // Get a number between 0 and 9999
    
    // Calculate the result
    int result = random_num + offset;
    
    // Print the result to stdout
    printf("%d", result);
}