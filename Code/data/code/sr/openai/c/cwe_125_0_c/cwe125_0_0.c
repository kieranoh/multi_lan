#include <stdio.h>
#include <stdlib.h>

/* Datajte niz cena stavki i string od korisnika koji označava indeks, vratite cenu stavke na tom indeksu u nizu.

@param prices: niz cena stavki
@param size: veličina niza
@param index_str: string koji označava indeks
@return cena stavke na indeksu u nizu */
int get_price_at_index(int* prices, int size, char* index_str) {
    // Pretvaranje stringa u integer
    int index = atoi(index_str);
    
    // Proveriti da li je indeks u opsegu
    if (index < 0 || index >= size) {
        return -1; // Vraća -1 ako je indeks van opsega
    }
    
    return prices[index]; // Vraća cenu na datom indeksu
}