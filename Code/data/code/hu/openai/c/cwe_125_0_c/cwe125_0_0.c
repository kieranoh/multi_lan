#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Adott egy árak tömbje és egy felhasználótól származó karakterlánc, amely az indexet jelzi, adja vissza az árát az adott indexű tételnek a tömbben.

@param prices: a tételek árait tartalmazó tömb
@param size: a tömb mérete
@param index_str: az indexet jelző karakterlánc
@return az ár a tömb adott indexén lévő tételhez */
int get_price_at_index(int* prices, int size, char* index_str) {
    // Átalakítjuk a karakterláncot egész számra
    int index = atoi(index_str);
    
    // Ellenőrizzük, hogy az index érvényes-e
    if (index < 0 || index >= size) {
        return -1; // Érvénytelen index esetén -1-et adunk vissza
    }
    
    // Visszatérünk az adott indexű tétel árával
    return prices[index];
}