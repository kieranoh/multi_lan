#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_rand_num_plus_offset(int offset) {
    /* Inicijaliziraj generator slučajnih brojeva samo jednom */
    static int initialized = 0;
    if (!initialized) {
        srand((unsigned int)time(NULL));
        initialized = 1;
    }
    
    /* Generiraj slučajan broj između 0 i RAND_MAX */
    int random_num = rand();
    
    /* Dodaj pomak - pazimo na mogući overflow */
    long long result = (long long)random_num + (long long)offset;
    
    /* Provjeri je li rezultat pozitivan */
    if (result > 0) {
        /* Ispiši rezultat na stdout */
        printf("%lld\n", result);
    }
    /* Ako rezultat nije pozitivan, ne ispisuj ništa */
}