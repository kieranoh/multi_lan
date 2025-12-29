#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Annetun siirron perusteella tulosta positiivisen satunnaisen luvun kokonaisarvo plus siirto stdout:iin. Jos jokin menee pieleen, älä tulosta mitään.

@param offset: siirto, joka lisätään satunnaiseen lukuun */
void print_rand_num_plus_offset(int offset) {
    // Alustetaan satunnaislukugeneraattori
    srand(time(NULL));

    // Generoidaan satunnainen positiivinen luku
    int rand_num = rand() % 100; // Generoi luku 0-99
    int result = rand_num + offset;

    // Tarkistetaan, että tulos on positiivinen
    if (result > 0) {
        printf("%d\n", result);
    }
}