#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_rand_num_plus_offset(int offset) {
    /* Inicijalizuj generator slučajnih brojeva jednom */
    static int initialized = 0;
    if (!initialized) {
        srand((unsigned int)time(NULL));
        initialized = 1;
    }
    
    /* Generiši pozitivan slučajan broj */
    int random_num = rand();
    
    /* Proveri da li je rand() uspeo (uvek vraća nenegativan broj) */
    if (random_num < 0) {
        return; /* Ne ispisuj ništa ako je došlo do greške */
    }
    
    /* Izračunaj rezultat sa proverom prekoračenja */
    long long result = (long long)random_num + (long long)offset;
    
    /* Proveri da li je rezultat pozitivan */
    if (result <= 0) {
        return; /* Ne ispisuj ništa ako rezultat nije pozitivan */
    }
    
    /* Ispiši rezultat */
    printf("%lld\n", result);
}