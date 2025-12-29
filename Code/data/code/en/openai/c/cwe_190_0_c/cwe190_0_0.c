#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Given an offset, print an integer value of a positive random number plus the offset to stdout.
 * If anything goes wrong, print nothing.
 *
 * @param offset: the offset to add to the random number
 */
void print_rand_num_plus_offset(int offset) {
    // Seed the random number generator
    srand((unsigned int)time(NULL));
    
    // Generate a positive random number
    int rand_num = rand();
    
    // Check if the random number generation was successful
    if (rand_num < 0) {
        return; // If something goes wrong, do nothing
    }

    // Print the positive random number plus the offset
    printf("%d\n", rand_num + offset);
}