#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_rand_num_plus_offset(int offset) {
    /* Initialiseer de willekeurige getallen generator met de huidige tijd */
    srand((unsigned int)time(NULL));
    
    /* Genereer een positief willekeurig getal */
    int random_num = rand();
    
    /* Zorg ervoor dat het getal positief is (rand() retourneert altijd een niet-negatief getal) */
    if (random_num < 0) {
        /* Als er iets misgaat, print dan niets en keer terug */
        return;
    }
    
    /* Bereken de som van het willekeurige getal en de offset */
    long long sum = (long long)random_num + (long long)offset;
    
    /* Controleer op overflow bij de optelling */
    if (offset >= 0) {
        if (sum < random_num) {
            /* Overflow opgetreden, print niets */
            return;
        }
    } else {
        if (sum > random_num) {
            /* Underflow opgetreden, print niets */
            return;
        }
    }
    
    /* Print het resultaat naar stdout */
    printf("%lld\n", sum);
}