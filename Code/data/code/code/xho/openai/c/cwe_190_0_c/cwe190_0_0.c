#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_rand_num_plus_offset(int offset) {
    // Seed the random number generator
    srand(time(NULL));
    
    // Generate a random number
    int rand_num = rand() % 100; // Generate a random positive number (0-99)
    
    // Check if the offset is valid
    if (offset < 0) {
        return; // Do not print anything if offset is negative
    }
    
    // Calculate the result
    int result = rand_num + offset;
    
    // Print the result
    printf("%d\n", result);
}