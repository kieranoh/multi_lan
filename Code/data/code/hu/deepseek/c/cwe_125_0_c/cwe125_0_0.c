#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Adott egy árak tömbje és egy felhasználótól származó karakterlánc, amely az indexet jelzi, adja vissza az árát az adott indexű tételnek a tömbben.

@param prices: a tételek árait tartalmazó tömb
@param size: a tömb mérete
@param index_str: az indexet jelző karakterlánc
@return az ár a tömb adott indexén lévő tételhez */
int get_price_at_index(int* prices, int size, char* index_str) {
    // Ellenőrizzük, hogy a tömb érvényes-e
    if (prices == NULL || size <= 0) {
        return -1;
    }
    
    // Ellenőrizzük, hogy az index string érvényes-e
    if (index_str == NULL || strlen(index_str) == 0) {
        return -1;
    }
    
    // Ellenőrizzük, hogy a string csak számjegyeket tartalmaz-e (és opcionálisan előjel)
    char* p = index_str;
    
    // Kezeljük az opcionális előjelet
    if (*p == '-' || *p == '+') {
        p++;
    }
    
    // Ellenőrizzük, hogy minden karakter számjegy-e
    while (*p != '\0') {
        if (!isdigit((unsigned char)*p)) {
            return -1;
        }
        p++;
    }
    
    // Konvertáljuk a stringet integerré
    long index = strtol(index_str, NULL, 10);
    
    // Ellenőrizzük, hogy az index a tömb határain belül van-e
    if (index < 0 || index >= size) {
        return -1;
    }
    
    // Visszaadjuk az árat a megadott indexen
    return prices[index];
}