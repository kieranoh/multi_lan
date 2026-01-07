#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_rand_num_plus_offset(int offset) {
    /* Initialize random number generator */
    if (srand((unsigned int)time(NULL)) != 0) {
        /* srand returns void, but we check if time returned 0 */
        if (time(NULL) == 0) {
            return;
        }
    }
    
    /* Generate random positive integer */
    int random_num = rand();
    
    /* Ensure random_num is positive (rand() returns non-negative) */
    if (random_num < 0) {
        return;
    }
    
    /* Add offset and print result */
    int result = random_num + offset;
    
    /* Check for integer overflow */
    if ((offset > 0 && result < random_num) || (offset < 0 && result > random_num)) {
        return;
    }
    
    printf("%d\n", result);
    fflush(stdout);
}