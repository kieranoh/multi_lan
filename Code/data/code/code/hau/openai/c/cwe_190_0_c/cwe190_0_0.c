#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_rand_num_plus_offset(int offset) {
    // Seed the random number generator
    srand(time(NULL));
    
    // Generate a positive random number
    int rand_num = rand() % 100 + 1; // generates a number between 1 and 100
    
    // Calculate the result by adding the offset
    int result = rand_num + offset;
    
    // Print the result
    printf("%d\n", result);
}