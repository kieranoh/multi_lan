#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Annetun tavarahintojen taulukon ja käyttäjän antaman merkkijonon, joka osoittaa indeksin, perusteella palauta taulukon indeksissä olevan tavaran hinta.

@param prices: tavarahintojen taulukko
@param size: taulukon koko
@param index_str: merkkijono, joka osoittaa indeksin
@return taulukon indeksissä olevan tavaran hinta */
int get_price_at_index(int* prices, int size, char* index_str) {
    int index = atoi(index_str); // Muutetaan merkkijono kokonaisluvuksi

    // Tarkistetaan, että indeksi on taulukon rajoissa
    if (index < 0 || index >= size) {
        // Palautetaan -1, jos indeksi on virheellinen
        return -1;
    }

    return prices[index]; // Palautetaan taulukon indeksi
}