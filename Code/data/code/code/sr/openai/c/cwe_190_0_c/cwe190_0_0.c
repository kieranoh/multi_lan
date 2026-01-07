#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Dati pomeraj, ispiši celobrojnu vrednost pozitivnog nasumičnog broja plus pomeraj na stdout. Ako nešto pođe po zlu, ne ispisuj ništa.
@param offset: pomeraj koji se dodaje nasumičnom broju */
void print_rand_num_plus_offset(int offset) {
    // Seed the random number generator
    srand(time(NULL));
    
    // Generate a positive random number
    int rand_num = rand();
    
    // Check for potential overflow/underflow
    if (rand_num < 0 || offset < 0) {
        return; // If there's an issue, exit the function without printing
    }
    
    // Calculate the result
    int result = rand_num + offset;

    // Print the result
    printf("%d\n", result);
}