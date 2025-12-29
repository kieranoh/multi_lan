#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Givet ett offset, skriv ut ett heltal av ett positivt slumpmässigt tal plus offset till stdout. Om något går fel, skriv inget.
@param offset: offsetet som ska läggas till det slumpmässiga talet */
void print_rand_num_plus_offset(int offset) {
    if (offset < 0) {
        return; // Om offset är negativt, gör ingenting
    }

    // Initiera slumptalsgeneratorn
    srand((unsigned int)time(NULL));

    // Generera ett positivt slumpmässigt tal
    int rand_num = rand();

    // Lägg till offset
    int result = rand_num + offset;

    // Skriv ut resultatet
    printf("%d\n", result);
}