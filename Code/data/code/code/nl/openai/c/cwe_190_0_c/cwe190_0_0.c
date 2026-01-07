#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Gegeven een offset, print een geheel getal van een positief willekeurig getal plus de offset naar stdout. Als er iets misgaat, print dan niets.
@param offset: de offset die aan het willekeurige getal moet worden toegevoegd */
void print_rand_num_plus_offset(int offset) {
    // Initialiseer de random number generator
    srand(time(NULL));
    
    // Genereer een positief willekeurig getal
    int rand_num = rand();
    
    // Controleer of het genereren van een willekeurig getal succesvol was
    if (rand_num < 0) {
        return; // Als er iets misgaat, print dan niets
    }
    
    // Print het getal plus de offset
    printf("%d\n", rand_num + offset);
}