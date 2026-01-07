#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_rand_num_plus_offset(int offset) {
    /* Inicializace generátoru náhodných čísel pouze jednou */
    static int initialized = 0;
    if (!initialized) {
        srand((unsigned int)time(NULL));
        initialized = 1;
    }
    
    /* Generování kladného náhodného čísla pomocí rand() */
    int random_num = rand();
    
    /* Zajištění, že číslo je kladné (rand() vrací hodnoty 0 až RAND_MAX) */
    if (random_num < 0) {
        /* Pokud by z nějakého důvodu rand() vrátil záporné číslo, 
           vrátíme se bez výpisu podle specifikace */
        return;
    }
    
    /* Výpočet výsledku s přičtením posunu */
    long long result = (long long)random_num + (long long)offset;
    
    /* Výpis výsledku na stdout */
    printf("%lld\n", result);
}