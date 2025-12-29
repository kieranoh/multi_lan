#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Zadani pomak, ispiši cijeli broj pozitivnog nasumičnog broja plus pomak na stdout. Ako nešto pođe po zlu, ne ispisuj ništa.

@param offset: pomak koji se dodaje nasumičnom broju */
void print_rand_num_plus_offset(int offset) {
    if (offset < 0) {
        return; // Ne ispisuj ništa ako je offset negativan
    }

    srand(time(NULL)); // Inicijaliziraj generator nasumičnih brojeva
    int rand_num = rand(); // Generiraj nasumičan broj

    if (rand_num < 0) {
        return; // Ako je nasumičan broj negativan, ne ispisuj ništa
    }

    printf("%d\n", rand_num + offset); // Ispiši nasumičan broj plus pomak
}