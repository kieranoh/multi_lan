#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_rand_num_plus_offset(int offset) {
    /* Alusta satunnaislukugeneraattori */
    srand((unsigned int)time(NULL));
    
    /* Generoi satunnaisluku väliltä 1-100 (positiivinen) */
    int random_num = rand() % 100 + 1;
    
    /* Laske tulos */
    int result = random_num + offset;
    
    /* Tulosta vain jos tulos on positiivinen */
    if (result > 0) {
        printf("%d\n", result);
    }
    /* Jos tulos ei ole positiivinen, älä tulosta mitään */
}