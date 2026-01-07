#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Dajući niz cijena stavki i niz od korisnika koji označava indeks, vrati cijenu stavke na indeksu u nizu.

@param prices: niz cijena stavki
@param size: veličina niza
@param index_str: niz koji označava indeks
@return cijena stavke na indeksu u nizu */
int get_price_at_index(int* prices, int size, char* index_str) {
    // Pretvaranje stringa u cijeli broj
    int index = atoi(index_str);
    
    // Provjera valjanosti indeksa
    if (index < 0 || index >= size) {
        return -1; // Vraćamo -1 ako je indeks izvan opsega
    }
    
    // Vraćanje cijene na zadanom indeksu
    return prices[index];
}