#include <stdio.h>
#include <stdlib.h>

/* Bir dizi ürün fiyatı ve bir kullanıcıdan gelen indeks belirten bir dize verildiğinde, dizideki belirtilen indeksteki ürünün fiyatını döndür. */
int get_price_at_index(int* prices, int size, char* index_str) {
    int index = atoi(index_str); // Dizeyi tam sayıya çevir
    if (index < 0 || index >= size) { // Geçerli bir indeks kontrolü
        return -1; // Geçersiz indeks için -1 döndür
    }
    return prices[index]; // Belirtilen indeksteki fiyatı döndür
}